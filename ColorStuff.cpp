#include<stdint.h>
#include<Arduino.h>
#include"ColorStuff.h"

static const uint32_t colors[] = 
{
  0xFF0000,
  0xFF7F00,
  0xFFFF00,
  0x00FF00,
  0x0000FF,
  0xFF00FF
};
const uint32_t *ColorStuff::rainbow = colors;

uint8_t ColorStuff::getRed(uint32_t color)
{
  return ( (color / 256) / 256) % 256;
}
uint8_t ColorStuff::getGreen(uint32_t color)
{
  return (color / 256) % 256;
}
uint8_t ColorStuff::getBlue(uint32_t color)
{
  return color % 256;
}
uint8_t ColorStuff::getAlpha(uint32_t color)
{
  return ( (color / 256) / 256) / 256;
}
uint32_t ColorStuff::red()
{
  return rainbow[0];
}
uint32_t ColorStuff::orange()
{
  return rainbow[1];
}
uint32_t ColorStuff::yellow()
{
  return rainbow[2];
}
uint32_t ColorStuff::green()
{
  return rainbow[3];
}
uint32_t ColorStuff::blue()
{
  return rainbow[4];
}
uint32_t ColorStuff::purple()
{
  return rainbow[5];
}
uint32_t ColorStuff::white()
{
  return 0xffffff;
}
uint32_t ColorStuff::black()
{
  return 0;
}
uint32_t ColorStuff::color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)//color with alpha (or white?)
{
  uint32_t c = alpha;
  c *= 256;
  c += red;
  c *= 256;
  c += green;
  c *= 256;
  c += blue;
  return c;
} 
uint32_t ColorStuff::color(uint8_t red, uint8_t green, uint8_t blue)  //color without alpha
{
  uint32_t c = red;
  c *= 256;
  c += green;
  c *= 256;
  c += blue;
  return c;
}
uint32_t ColorStuff::mix(uint32_t a, uint32_t b, float percentage)
{
  percentage = constrain(percentage, 0.0, 1.0);
  uint32_t newColor = 0;
  newColor = constrain((1.0 - percentage) * getAlpha(a) + percentage * getAlpha(b), 0, 255);
  newColor *= 256;
  newColor += constrain((1.0 - percentage) * getRed(a) + percentage * getRed(b), 0, 255);
  newColor *= 256;
  newColor += constrain((1.0 - percentage) * getGreen(a) + percentage * getGreen(b), 0, 255);
  newColor *= 256;
  newColor += constrain((1.0 - percentage) * getBlue(a) + percentage * getBlue(b), 0, 255);
  return newColor;
}
uint32_t ColorStuff::darken(uint32_t a, float percentage)
{
  percentage = constrain(percentage, 0.0, 1.0);
  return color(getRed(a) * percentage,
               getGreen(a) * percentage,
               getBlue(a) * percentage,
               getAlpha(a));
}
uint32_t ColorStuff::lighten(uint32_t a, float percentage)
{
  percentage = constrain(percentage, 0.0, 1.0);
  return color(getRed(a) + ((255 - getRed(a)) * percentage),
               getGreen(a) + ((255 - getGreen(a)) * percentage),
               getBlue(a) + ((255 - getBlue(a)) * percentage),
               getAlpha(a));
}
uint32_t ColorStuff::opposite(uint32_t a)
{
  return color(getRed(0xffffffff - a),
               getGreen(0xffffffff - a),
               getBlue(0xffffffff - a),
               getAlpha(a));
}
uint32_t ColorStuff::rainbowify(uint8_t i)
{
  return rainbow[i % RAINBOW_SIZE];
}
uint32_t ColorStuff::fadeRainbowify(uint8_t i, uint8_t j)
{
  float index = constrain(betterMap(i, 0.0, j, 0.0, (float)RAINBOW_SIZE - .01), 0.0, (float)RAINBOW_SIZE - .01);
  return mix(rainbow[(int)floor(index)], rainbow[(((int)floor(index)) + 1) % RAINBOW_SIZE], index - (float)floor(index));
}
float ColorStuff::betterMap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

