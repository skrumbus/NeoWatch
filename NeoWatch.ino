#include"NeoPixel_Ring.h"
#include"Button.h"
#include"NotificationDemo.h"
#include<Adafruit_NeoPixel.h>

//TO DO:
//IMPLEMENT PASS NEGATIVE NUMBERS AS START AND END PIXELS TO SIGNIFY REVERSE

#define NUM_PIXELS 12
#define BUTTON_PIN 3
#define PIXEL_PIN 8

NeoPixel_Ring ring = NeoPixel_Ring(NUM_PIXELS, PIXEL_PIN);
uint8_t k = 0;
Button b = Button(3, LOW);

void setup() {
  ring.begin();
  ring.setBrightness(16);
  b.begin();
  ring.clear();
  ring.show();
}

void loop() 
{
  if(NotificationDemo::demo(ring, k, b))
    k = (k + 1) % NotificationDemo::NUM_DEMOS;
  ring.clear();
  ring.show();
}
