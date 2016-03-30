#ifndef PATTERN_SETTINGS_H
#define PATTERN_SETTINGS_H

#include<stdint.h>

#define MAX_PATTERN_COLORS 2
#define NUM_PATTERN_TYPES 5

class PatternSettings
{
  private:
    uint8_t type;
    float brightness;
    uint16_t displayLength, delayLength;
    int16_t startPixel;
    uint8_t numPixels;
    uint32_t colors[MAX_PATTERN_COLORS];
    uint8_t numColors;
  public:
    PatternSettings(uint8_t numColors, uint8_t numPixels, int16_t startPixel = 0, uint16_t displayLength = 0, uint16_t delayLength = 0, float b = 1.0);
    float getBrightness();
    void setBrightness(float);
    uint16_t getDisplayLength();
    void setDisplayLength(uint16_t);
    uint16_t getDelayLength();
    void setDelayLength(uint16_t);
    int16_t getStartPixel();
    void setStartPixel(int16_t);
    uint8_t getNumPixels();
    void setNumPixels(uint8_t);
    uint8_t getNumColors();
    void addColor(uint32_t);
    void setColor(uint8_t, uint32_t);
    uint32_t getColor(uint8_t);
    uint32_t getFadedColor(uint8_t);
    uint8_t getType();
    void setType(uint8_t);
};

#endif
