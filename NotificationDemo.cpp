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
      for(uint8_t i = 0; b.isPressed(); i = (i + 1) % ring.numPixels())
      {
        ring.rainbow(i, (i + ring.numPixels() - 1) % ring.numPixels(), 1);
        ring.show();
        for(int j = 0; j < 50 && b.isPressed(); j += 10, b.update(10), delay(10));
        wasPressed = true;
      }
      break;
    }
    case 1:
    {
      for(uint8_t i = 0; b.isPressed(); i = (i + 1) % ring.numPixels())
      {
        ring.spiral(ColorStuff::darken(ColorStuff::red(), .5), ColorStuff::darken(ColorStuff::green(), .5), i % ring.numPixels(), (i + (ring.numPixels() - 1)) % ring.numPixels(), 1);
        ring.show();
        for(uint8_t j = 0; j < 50 && b.isPressed(); j += 10, b.update(10), delay(10));
        wasPressed = true;
      }
      break;
    }
    case 2:
    {
      bool flip = false;
      for(uint8_t i = 1; b.isPressed();)
      {
        ring.glow(ColorStuff::blue(), ColorStuff::green(),(float) i / 100, 1);
        ring.show();
        delay(10);
        b.update(10);
        if(i == 100 || i == 0)
          flip = !flip;
        if(flip)
          i--;
        else
          i++;
        wasPressed = true;
      }
      break;
    }
    case 3:
    {
      for(uint8_t i = 1; b.isPressed(); i = (i + 1) % ring.numPixels())
      {
        ring.marquee(ColorStuff::black(), ColorStuff::green(), i, 2);
        ring.show();
        for(uint8_t j = 0; j < 250 && b.isPressed(); j += 10, b.update(10), delay(10));
        wasPressed = true;
      }
      break;
    }
  }
  ring.clear();
  ring.show();
  return wasPressed;
}

