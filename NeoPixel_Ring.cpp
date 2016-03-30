#include<Adafruit_NeoPixel.h>
#include"NeoPixel_Ring.h"
#include"ColorStuff.h"

NeoPixel_Ring::NeoPixel_Ring(uint16_t n, uint8_t p, neoPixelType t)
  :Adafruit_NeoPixel(n, p, t)
{
  
}
uint8_t NeoPixel_Ring::numIterations(uint8_t s, uint8_t e)
{
  if(s > e)
    e += numPixels();
  return e - s + 1;
}
float NeoPixel_Ring::getPercentage(float initial, float minimum)
{
  return (1.0 - minimum) * initial + minimum;
}
void NeoPixel_Ring::spiral(uint32_t startColor, uint32_t endColor, uint8_t startPixel, uint8_t endPixel, float minBrightness)
{
  clear();
  startPixel = constrain(startPixel, 0, numPixels() - 1);
  endPixel = constrain(endPixel, 0, numPixels() - 1);
  minBrightness = constrain(minBrightness, 0.0, 1.0);
  uint8_t numIts = numIterations(startPixel, endPixel);
  for(uint8_t i = 0; i < numIts; i++)
  {
    float colorP = 1.0 - getPercentage((float)i / numIts);
    float brightP = getPercentage(((float)i / numIts), minBrightness);
    setPixelColor(
                   (i + startPixel) % numPixels(),
                   ColorStuff::darken(
                                        ColorStuff::mix(
                                                         startColor,
                                                         endColor, 
                                                         colorP
                                                       ),
                                        brightP
                                      )
                 );
  }
}
void NeoPixel_Ring::sparkle(uint32_t startColor, uint32_t endColor, float minBrightness)
{
  
}
void NeoPixel_Ring::glow(uint32_t startColor, uint32_t endColor, float percentage, float minBrightness)
{
  clear();
  percentage = constrain(percentage, 0.0, 1.0);
  minBrightness = constrain(minBrightness, 0.0, 1.0);
  float brightP = getPercentage(percentage, minBrightness);
  for(uint8_t i = 0; i < numPixels(); i++)
  {
    setPixelColor(i, ColorStuff::darken(ColorStuff::mix(startColor, endColor, percentage), brightP));
  }
}
void NeoPixel_Ring::flash(uint32_t color)
{
  clear();
  for(uint8_t i = 0; i < numPixels(); i++)
  {
    setPixelColor(i, color);
  }
}
void NeoPixel_Ring::marquee(uint32_t dotColor, uint32_t spaceColor, uint8_t startPixel, uint8_t spaces) //1, 2, 3, and 5 are optimal for spacing
{
  clear();
  startPixel = constrain(startPixel, 0, numPixels() - 1);
  for(uint8_t i = 0; i < numPixels(); i++)
  {
    setPixelColor((i + startPixel) % numPixels(), dotColor);
    uint8_t j = 0;
    for(; j < spaces; j++)
    {
      setPixelColor((j + i + startPixel + 1) % numPixels(), spaceColor);
    }
    i += j;
  }
}
void NeoPixel_Ring::rainbow(uint8_t startPixel, uint8_t endPixel, float minBrightness)
{
  clear();
  startPixel = constrain(startPixel, 0, numPixels() - 1);
  endPixel = constrain(endPixel, 0, numPixels() - 1);
  minBrightness = constrain(minBrightness, 0.0, 1.0);
  uint8_t numIts = numIterations(startPixel, endPixel);
  for(uint8_t i = 0; i < numIts; i++)
  {
    float brightP = getPercentage(((float)i / numIts), minBrightness);
    setPixelColor(
                   (i + startPixel) % numPixels(),
                   ColorStuff::darken(ColorStuff::rainbowify(i, numIts), brightP)
                 );
  }
}
