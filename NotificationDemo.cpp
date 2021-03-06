#include"NotificationDemo.h"
#include"ColorStuff.h"

bool NotificationDemo::demo(NeoRing& ring, uint8_t type, Button& b)
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
        ring.rainbow(i, ring.numPixels());
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
        ring.spiral(ColorStuff::red(), ColorStuff::green(), i % ring.numPixels(), ring.numPixels());
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
        ring.glow(ColorStuff::blue(), ColorStuff::green(), (float) i / 100);
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
        ring.marquee(ColorStuff::red(), ColorStuff::green(), 2, 2, i);
        ring.show();
        for(uint8_t j = 0; j < 250 && b.isPressed(); j += 10, b.update(10), delay(10));
      }
      break;
    }
    case 4:
    {
      wasPressed = b.isPressed();
      ring.flash(ColorStuff::blue());
      while(b.isPressed())
      {
        ring.sparkle(ColorStuff::red(), ColorStuff::blue(), random(5) == 0);
        ring.show();
        //for(uint8_t j = 0; j < 100 && b.isPressed(); j += 10, b.update(10), delay(10));
        b.update();
      }
      break;
    }
  }
  ring.clear();
  ring.show();
  return wasPressed;
}

