#ifndef NEOPIXEL_RING_H
#define NEOPIXEL_RING_H

#include<Adafruit_NeoPixel.h>

class NeoPixel_Ring
  :public Adafruit_NeoPixel
{
  private:
    uint8_t numIterations(uint8_t, uint8_t);
    float getPercentage(float, float = 0.0);
    bool prepareReverse(uint8_t&, uint8_t&);
  public:
    NeoPixel_Ring(uint16_t, uint8_t = 6, neoPixelType = NEO_GRB + NEO_KHZ800);
    void spiral(uint32_t, uint32_t, uint8_t, uint8_t, float = 0.0); //spiral with two colors fade to x
    void sparkle(uint32_t, uint32_t, float = 0.0); //sparkle with two colors
    void glow(uint32_t, uint32_t, float, float = 0.0); //glow with two colors fade to x
    void flash(uint32_t); //flash a color
    void marquee(uint32_t, uint32_t, uint8_t = 1, uint8_t = 1, uint8_t = 0); //marquee with two colors
    void rainbow(uint8_t, uint8_t, float = 0.0); //rainbow from pixel to pixel fade to x
};
#endif
