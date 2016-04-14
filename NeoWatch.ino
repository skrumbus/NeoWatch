
#include"NeoRing.h"
#include"NeoClock.h"
#include"Button.h"
#include"NotificationDemo.h"
#include"PatternSettings.h"
#include<Adafruit_NeoPixel.h>
//#include<RtcDS3231.h>
//#include<Wire.h>

//TO DO:
//IMPLEMENT PASS NEGATIVE NUMBERS AS START AND END PIXELS TO SIGNIFY REVERSE

#define NUM_PIXELS 12
#define SHOW_BUTTON_PIN 12
#define SETTING_BUTTON_PIN 10
#define PIXEL_PIN 9
#define UNUSED_PIN 11
#define DEMO_PIN 5

/*NeoRing ring = NeoRing(NUM_PIXELS, PIXEL_PIN);
uint8_t k = 0;
Button b = Button(3, LOW);*/
uint8_t k = 0;
Button show = Button(SHOW_BUTTON_PIN, LOW);
Button set = Button(SETTING_BUTTON_PIN, LOW);
Button demo = Button(DEMO_PIN, LOW);
uint32_t color = 0xff0000;

NeoClock myClock = NeoClock(NUM_PIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800, DateTime(), DateTime(), show, set);
void setup() 
{
  randomSeed(analogRead(UNUSED_PIN));
  myClock.begin();
  myClock.setBrightness(48);
  myClock.clear();
  myClock.show();
  demo.begin();
}

void loop() 
{
  myClock.clear();
  myClock++;
  demo.update();
  if(demo.isPressed())
  {
    if(NotificationDemo::demo(myClock, k, demo))
      k = (k + 1) % NotificationDemo::NUM_DEMOS;
  }
  else
  {
    for(int i = 0; i < 1000 && !demo.isPressed(); i += 10)
    {
      myClock.clear();
      demo.update();
      delay(10);
      myClock.update();
      myClock.show();
    }
  }
  /*myClock.sparkle(0xff0000, 0xff00ff, random(3) == 0);
  delay(100);
  myClock.show();*/
  /*myClock.clear();
  myClock++.showTime();
  myClock.show();
  delay(1000);
  /*myClock.spiral(0xff0000, 0x000000, 4, myClock.numPixels(), 1.0, true);
  myClock.show();
  delay(1000);
  myClock.clear();
  myClock.spiral(0xff0000, 0x000000, 4, myClock.numPixels());
  myClock.show();
  delay(1000);
  myClock.clear();*/
  
}
