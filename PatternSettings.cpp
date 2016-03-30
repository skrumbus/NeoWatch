#include"PatternSettings.h"
#include"ColorStuff.h"
#include<Arduino.h>

PatternSettings::PatternSettings(uint8_t numColors, uint8_t numPixels, int16_t startPixel, uint16_t displayLength, uint16_t delayLength, float brightness)
{
  setNumPixels(numPixels);
  setStartPixel(startPixel);
  setDisplayLength(displayLength);
  setDelayLength(delayLength);
  setBrightness(brightness);
  numColors = numColors;
  for(int i = 0; i < MAX_PATTERN_COLORS; i++)
    colors[i] = 0;
}
float PatternSettings::getBrightness()
{
  return brightness;
}
void PatternSettings::setBrightness(float brightness)
{
  this->brightness = constrain(brightness, 0.0, 1.0);
}
uint16_t PatternSettings::getDisplayLength()
{
  return displayLength;
}
void PatternSettings::setDisplayLength(uint16_t displayLength)
{
  this->displayLength - displayLength;
}
uint16_t PatternSettings::getDelayLength()
{
  return delayLength;
}
void PatternSettings::setDelayLength(uint16_t delayLength)
{
  this->delayLength = delayLength;
}
int16_t PatternSettings::getStartPixel()
{
  return startPixel;
}
void PatternSettings::setStartPixel(int16_t startPixel)
{
  if(startPixel == 0)
    startPixel = 1;
  this->startPixel = startPixel;
}
uint8_t PatternSettings::getNumPixels()
{
  return numPixels;
}
void PatternSettings::setNumPixels(uint8_t numPixels)
{
  this->numPixels = numPixels;
}
uint32_t PatternSettings::getColor(uint8_t i)
{
  return colors[i % numColors];
}
uint8_t PatternSettings::getNumColors()
{
  return numColors;
}
void PatternSettings::addColor(uint32_t c)
{
  if(numColors < MAX_PATTERN_COLORS)
    colors[numColors++] = c;
}
void PatternSettings::setColor(uint8_t i, uint32_t c)
{
  colors[i % numColors] = c;
}
uint32_t PatternSettings::getFadedColor(uint8_t i)
{
  i = i % numPixels;
  float index = ColorStuff::betterMap(i, 0, numPixels, 0, numColors);
  return ColorStuff::mix(colors[(int)floor(index)], colors[(((int)floor(index)) + 1) % numColors], index - (float)floor(index));
}
uint8_t PatternSettings::getType()
{
  return type;
}
void PatternSettings::setType(uint8_t type)
{
  type = type % NUM_PATTERN_TYPES;
  this->type = type;
}

