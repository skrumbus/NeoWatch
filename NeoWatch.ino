#include"NeoRing.h"
#include"NeoClock.h"
#include"Button.h"
#include"NotificationDemo.h"
#include"PatternSettings.h"
#include<Adafruit_NeoPixel.h>
#include<RtcDS3231.h>
#include<Wire.h>

//TO DO:
//IMPLEMENT PASS NEGATIVE NUMBERS AS START AND END PIXELS TO SIGNIFY REVERSE

#define NUM_PIXELS 12
#define SHOW_BUTTON_PIN 3
#define PIXEL_PIN 2

/*NeoRing ring = NeoRing(NUM_PIXELS, PIXEL_PIN);
uint8_t k = 0;
Button b = Button(3, LOW);*/

NeoClock myClock = NeoClock(NUM_PIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800, 0, Button(SHOW_BUTTON_PIN, LOW));

void setup() {
  myClock.begin();
  myClock.setBrightness(32);
  myClock.clear();
  myClock.show();
  //myClock.setDoShowSecond(false);
  /*ring.begin();
  ring.setBrightness(16);
  b.begin();
  ring.clear();
  ring.show();*/
}

void loop() 
{
  myClock.showTime(true);
  myClock.show();
  /*if(NotificationDemo::demo(ring, k, b))
    k = (k + 1) % NotificationDemo::NUM_DEMOS;
  ring.clear();
  ring.show();*/
  myClock++;
  delay(10);
}
