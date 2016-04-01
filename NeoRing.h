#ifndef NEO_RING
#define NEO_RING

#include<Adafruit_NeoPixel.h>

class NeoRing
  :public Adafruit_NeoPixel
{
  protected:
    bool isBackwards;
    uint8_t numIterations(uint8_t, uint8_t);
    float getPercentage(float, float = 0.0);
  public:
    NeoRing(uint16_t = 65535, uint8_t = 6, neoPixelType = NEO_GRB + NEO_KHZ800);
    void spiral(uint32_t, uint32_t, uint8_t = 0, uint8_t = 0, float = 1.0, bool = false); //spiral with two colors fade to x
    void sparkle(uint32_t, uint32_t, bool = true, float = 1.0); //sparkle with two colors
    void glow(uint32_t, uint32_t, float, float = 1.0); //glow with two colors fade to x
    void flash(uint32_t); //flash a color
    void marquee(uint32_t, uint32_t, uint8_t = 1, uint8_t = 1, uint8_t = 0, float = 1.0, bool = false); //marquee with two colors
    void rainbow(uint8_t, uint8_t, float = 1.0, bool = false); //rainbow from pixel to pixel fade to x
    void mapColorToPixel(int16_t, int16_t, int16_t, uint32_t, uint32_t);
    void mixColorToPixel(int16_t, int16_t, int16_t, uint32_t, uint32_t);
    bool getIsBackwards();
    void setIsBackwards(bool);
};
#endif
