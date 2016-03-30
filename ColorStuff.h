#ifndef COLOR_STUFF_H
#define COLOR_STUFF_H

#include<stdint.h>

class ColorStuff
{
  public:
    static float betterMap(float x, float in_min, float in_max, float out_min, float out_max);
    static const uint32_t *rainbow;  //SIX COLOR RAINBOW, YOU HEARD IT HERE. FUCK ROY.
    static uint8_t getRed(uint32_t); //returns a value from 0-255 representing the red of the color
    static uint8_t getGreen(uint32_t); //returns a value from 0-255 representing the blue of the color
    static uint8_t getBlue(uint32_t); //returns a value from 0-255 representing the green of the color
    static uint8_t getAlpha(uint32_t); //returns a value from 0-255 representing the alpha of the color
    static uint32_t red(); //returns the color red
    static uint32_t orange(); //returns the color orange
    static uint32_t yellow(); //returns the color yellow
    static uint32_t green(); //returns the color green
    static uint32_t blue(); //returns the color blue
    static uint32_t purple(); //returns the color purple
    static uint32_t white(); //returns the color white
    static uint32_t black(); //returns the color black
    static uint32_t rainbowify(uint8_t, uint8_t = 6); //returns kth color in rainbow (i.e. 0 = red, 5 = purple, 6 = red, so on)
    static uint32_t color(uint8_t, uint8_t, uint8_t, uint8_t); //color with alpha (or white?)
    static uint32_t color(uint8_t, uint8_t, uint8_t); //color without alpha
    static uint32_t mix(uint32_t, uint32_t, float = .5); //mixes a given percentage(0 - 1) of the second color into the first and returns the resulting color
    static uint32_t darken(uint32_t, float); //returns a color x%(0 - 1) closer to pure black
    static uint32_t lighten(uint32_t, float); //returns a color x%(0 - 1) closer to pure white
    static uint32_t opposite(uint32_t); //returns the opposite color of the passed color
};

#endif
