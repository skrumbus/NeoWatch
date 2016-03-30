#include"NotificationDemo.h"
#include"ColorStuff.h"

bool NotificationDemo::demo(NeoPixel_Ring& ring, uint8_t type, Button b)
{
  bool wasPressed = false;
  type = type % NUM_DEMOS;
  b.update();
  switch(type)
  {
    case 0:
    {
      wasPressed = b.isPressed();
      for(uint8_t i = 0; b.isPressed(); i = (i + 1) % ring.numPixels())
      {
        ring.rainbow(i, (i + ring.numPixels() - 1) % ring.numPixels(), 0);
        ring.show();
        for(int j = 0; j < 50 && b.isPressed(); j += 10, b.update(10), delay(10));
      }
      break;
    }
    case 1:
    {
      wasPressed = b.isPressed();
      for(uint8_t i = 0; b.isPressed(); i = (i + 1) % ring.numPixels())
      {
        ring.spiral(ColorStuff::darken(ColorStuff::red(), .5), ColorStuff::darken(ColorStuff::green(), .5), i % ring.numPixels(), (i + ring.numPixels() - 1) % ring.numPixels(), 0);
        ring.show();
        for(uint8_t j = 0; j < 50 && b.isPressed(); j += 10, b.update(10), delay(10));
      }
      break;
    }
    case 2:
    {
      wasPressed = b.isPressed();
      bool flip = false;
      for(uint8_t i = 1; b.isPressed();)
      {
        ring.glow(ColorStuff::blue(), ColorStuff::green(),(float) i / 100, 0);
        ring.show();
        delay(10);
        b.update(10);
        if(i == 100 || i == 0)
          flip = !flip;
        if(flip)
          i--;
        else
          i++;
      }
      break;
    }
    case 3:
    {
      wasPressed = b.isPressed();
      for(uint8_t i = 1; b.isPressed(); i = (i + 1) % ring.numPixels())
      {
        ring.marquee(ColorStuff::black(), ColorStuff::green(), 2, 2, i);
        ring.show();
        for(uint8_t j = 0; j < 250 && b.isPressed(); j += 10, b.update(10), delay(10));
      }
      break;
    }
  }
  ring.clear();
  ring.show();
  return wasPressed;
}

