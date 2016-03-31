#include<Adafruit_NeoPixel.h>
#include"NeoRing.h"
#include"ColorStuff.h"

NeoRing::NeoRing(uint16_t n, uint8_t p, neoPixelType t)
  : Adafruit_NeoPixel(n, p, t)
{

}
bool NeoRing::prepareReverse(int16_t& s)
{
  if (s < 0)
  {
    ++s *= -1;
    return true;
  }
  else
    return false;
}
float NeoRing::getPercentage(float initial, float minimum)
{
  return (1.0 - minimum) * initial + minimum;
}
void NeoRing::spiral(uint32_t startColor, uint32_t endColor, int16_t startPixel, uint8_t len, float fade)
{
  clear();
  bool reverse = prepareReverse(startPixel);
  startPixel = constrain(startPixel, 0, numPixels() - 1);
  len = constrain(len, 0, numPixels());
  len = (len == 0) ? numPixels() : len;
  fade = constrain(fade, 0.0, 1.0);
  for (int16_t i = (reverse ? len - 1 : 0); (reverse ? (i >= 0 && i != 255) : (i < len)); (reverse ? i-- : i++))
  {
    float colorP = 1.0 - getPercentage((float)i / len);
    float brightP = getPercentage((float)i / len, 1.0 - fade);
    setPixelColor((i + startPixel) % numPixels(), ColorStuff::darken(ColorStuff::mix(startColor, endColor, colorP), brightP));
  }
}
void NeoRing::sparkle(uint32_t startColor, uint32_t endColor, float fade)
{

}
void NeoRing::glow(uint32_t startColor, uint32_t endColor, float percentage, float fade)
{
  clear();
  percentage = constrain(percentage, 0.0, 1.0);
  fade = constrain(fade, 0.0, 1.0);
  float brightP = getPercentage(percentage, 1.0 - fade);
  for (uint8_t i = 0; i < numPixels(); i++)
    setPixelColor(i, ColorStuff::darken(ColorStuff::mix(startColor, endColor, percentage), brightP));
}
void NeoRing::flash(uint32_t color)
{
  clear();
  for (uint8_t i = 0; i < numPixels(); i++)
    setPixelColor(i, color);
}
void NeoRing::marquee(uint32_t dotColor, uint32_t spaceColor, uint8_t dots, uint8_t spaces, uint8_t startPixel) //1, 2, 3, and 5 are optimal for spacing
{
  clear();
  startPixel = constrain(startPixel, 0, numPixels() - 1);
  uint8_t j = 0;
  for (uint8_t i = 0; i < numPixels(); i += max(1, j))
  {
    j = 0;
    for (; j < dots; j++)
      setPixelColor((j + i + startPixel) % numPixels(), dotColor);
    for (; j - dots < spaces; j++)
      setPixelColor((j + i + startPixel) % numPixels(), spaceColor);
  }
}
void NeoRing::rainbow(uint8_t startPixel, uint8_t len, float fade)
{
  clear();
  len = constrain(len, 0, numPixels());
  len = (len == 0) ? numPixels() : len;
  fade = constrain(fade, 0.0, 1.0);
  for (uint8_t i = 0; i < len; i++)
  {
    float brightP = getPercentage(((float)i / len), 1.0 - fade);
    setPixelColor(
      (i + startPixel) % numPixels(),
      ColorStuff::darken(ColorStuff::fadeRainbowify(i, len), brightP)
    );
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
  if (oldColor != 0)
    newColor = ColorStuff::mix(oldColor, newColor);
  setPixelColor(floor(i), newColor);
}
