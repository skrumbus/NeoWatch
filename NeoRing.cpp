#include<Adafruit_NeoPixel.h>
#include"NeoRing.h"
#include"ColorStuff.h"

NeoRing::NeoRing(uint16_t n, uint8_t p, neoPixelType t)
  : Adafruit_NeoPixel(n, p, t)
{
  isBackwards = false;
}
float NeoRing::getPercentage(float initial, float minimum)
{
  return (1.0 - minimum) * initial + minimum;
}
void NeoRing::spiral(uint32_t startColor, uint32_t endColor, uint8_t startPixel, uint8_t len, float brightness, bool reverse)
{
  reverse = ((reverse && !isBackwards) || (!reverse && isBackwards));
  startPixel = constrain(startPixel, 0, numPixels() - 1);
  len = constrain(len, 0, numPixels());
  len = (len == 0) ? numPixels() : len;
  if(reverse)
  {
    uint32_t temp = startColor;
    startColor = endColor;
    endColor = temp;
  }
  for (uint8_t i = (reverse ? len - 1 : 0); i >= 0 && i < len; (reverse ? i-- : i++))
  {
    float colorP = 1.0 - getPercentage((float)i / (len - 1) );
    setPixelColor((i + startPixel) % numPixels(), ColorStuff::darken(ColorStuff::mix(startColor, endColor, colorP), brightness));
    Serial.println((i + startPixel) % numPixels() );
  }
}
void NeoRing::sparkle(uint32_t startColor, uint32_t endColor, bool doSparkle, float brightness)
{
  for(int i = 0; i < numPixels(); i++)
  {
    uint32_t c = getPixelColor(i);
    c = ColorStuff::mix(c, endColor, .1);
    setPixelColor(i, c);
  }
  if(doSparkle)
    setPixelColor(random(numPixels()), startColor);
}
void NeoRing::glow(uint32_t startColor, uint32_t endColor, float percentage, float brightness)
{
  percentage = constrain(percentage, 0.0, 1.0);
  for (uint8_t i = 0; i < numPixels(); i++)
    setPixelColor(i, ColorStuff::mix(startColor, endColor, percentage));
}
void NeoRing::flash(uint32_t color)
{
  for (uint8_t i = 0; i < numPixels(); i++)
    setPixelColor(i, color);
}
void NeoRing::marquee(uint32_t dotColor, uint32_t spaceColor, uint8_t dots, uint8_t spaces, uint8_t startPixel, float brightness, bool reverse) //1, 2, 3, and 5 are optimal for spacing
{
  reverse = ((reverse && !isBackwards) || (!reverse && isBackwards));
  dots = constrain(dots, 0, numPixels() - 1);
  spaces = constrain(spaces, 0, numPixels() -1);
  startPixel = constrain(startPixel, 0, numPixels() - 1);
  uint8_t j = 0;
  if(reverse)
  {
    uint32_t temp = dotColor;
    dotColor = spaceColor;
    spaceColor = temp;
  }
  for (uint8_t i = (reverse ? numPixels() - 1 : 0); i >= 0 && i < numPixels(); (reverse? i -= max(1, j) : i += max(1, j)))
  {
    j = (reverse? dots - 1 : 0);
    for (; j < dots && j >= 0; (reverse? j-- : j++))
      setPixelColor((j + i + startPixel) % numPixels(), dotColor);
    for (; j < dots && j >= 0; (reverse? j-- : j++))
      setPixelColor((j + i + startPixel) % numPixels(), spaceColor);
  }
}
void NeoRing::rainbow(uint8_t startPixel, uint8_t len, float brightness, bool reverse)
{
  reverse = ((reverse && !isBackwards) || (!reverse && isBackwards));
  len = constrain(len, 0, numPixels());
  len = (len == 0) ? numPixels() : len;
  for (uint8_t i = (reverse ? len - 1 : 0); i >= 0 && i < len; (reverse ? i-- : i++))
  {
    setPixelColor((i + startPixel) % numPixels(), ColorStuff::fadeRainbowify(i, len - 1));
  }
}
void NeoRing::mapColorToPixel(int16_t value, int16_t min, int16_t max, uint32_t color1, uint32_t color2)
{
  float i = constrain(ColorStuff::betterMap(value, min, max, 0, (float)numPixels() - .01), 0, (float)numPixels() - .01);
  setPixelColor(floor(i), ColorStuff::mix(color1, color2, i - (float)floor(i)));
}
void NeoRing::mixColorToPixel(int16_t value, int16_t min, int16_t max, uint32_t color1, uint32_t color2)
{
  float i = constrain(ColorStuff::betterMap(value, min, max, 0, (float)numPixels() - .01), 0, (float)numPixels() - .01);
  uint32_t oldColor = getPixelColor(floor(i));
  uint32_t newColor = ColorStuff::mix(color1, color2, i - (float)floor(i));
  Serial.println(value);
  Serial.println(i);
  Serial.println(newColor);
  if (oldColor != 0)
    newColor = ColorStuff::mix(oldColor, newColor);
  setPixelColor(floor(i), newColor);
}
