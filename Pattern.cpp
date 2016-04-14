#include"Pattern.h"
#include"ColorStuff.h"
#include<Arduino.h>

Pattern::Pattern()
{
  setNumPixels(0);
  setStartPixel(0);
  setDisplayLength(0);
  setDelayLength(0);
  setBrightness(0);
  numColors = 0;
  for(int i = 0; i < MAX_PATTERN_COLORS; i++)
    colors[i] = 0;
}
Pattern::Pattern(uint8_t numColors, uint8_t numPixels, int16_t startPixel, uint16_t displayLength, uint16_t delayLength, float brightness)
{
  setNumPixels(numPixels);
  setStartPixel(startPixel);
  setDisplayLength(displayLength);
  setDelayLength(delayLength);
  setBrightness(brightness);
  numColors = constrain(numColors, 0, MAX_PATTERN_COLORS);
  for(int i = 0; i < MAX_PATTERN_COLORS; i++)
    colors[i] = 0;
}
float Pattern::getBrightness()
{
  return brightness;
}
void Pattern::setBrightness(float brightness)
{
  this->brightness = constrain(brightness, 0.0, 1.0);
}
uint16_t Pattern::getDisplayLength()
{
  return displayLength;
}
void Pattern::setDisplayLength(uint16_t displayLength)
{
  this->displayLength - displayLength;
}
uint16_t Pattern::getDelayLength()
{
  return delayLength;
}
void Pattern::setDelayLength(uint16_t delayLength)
{
  this->delayLength = delayLength;
}
int16_t Pattern::getStartPixel()
{
  return startPixel;
}
void Pattern::setStartPixel(int16_t startPixel)
{
  if(startPixel == 0)
    startPixel = 1;
  this->startPixel = startPixel;
}
uint8_t Pattern::getNumPixels()
{
  return numPixels;
}
void Pattern::setNumPixels(uint8_t numPixels)
{
  this->numPixels = numPixels;
}
uint32_t Pattern::getColor(uint8_t i)
{
  return colors[i % numColors];
}
uint8_t Pattern::getNumColors()
{
  return numColors;
}
void Pattern::addColor(uint32_t c)
{
  if(numColors < MAX_PATTERN_COLORS)
    colors[numColors++] = c;
}
void Pattern::setColor(uint8_t i, uint32_t c)
{
  colors[i % numColors] = c;
}
uint32_t Pattern::getFadedColor(uint8_t i)
{
  i = i % numPixels;
  float index = ColorStuff::betterMap(i, 0, numPixels, 0, numColors);
  return ColorStuff::mix(colors[(int)floor(index)], colors[(((int)floor(index)) + 1) % numColors], index - (float)floor(index));
}
uint8_t Pattern::getType()
{
  return type;
}
void Pattern::setType(uint8_t type)
{
  type = type % NUM_PATTERN_TYPES;
  this->type = type;
}

