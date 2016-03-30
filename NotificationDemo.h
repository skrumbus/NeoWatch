#ifndef NOTIFICATION_DEMO_H
#define NOTIFICATION_DEMO_H

#include"NeoPixel_Ring.h"
#include"Button.h"

class NotificationDemo
{
  public:
    const static uint8_t NUM_DEMOS = 4;
    static bool demo(NeoPixel_Ring&, uint8_t, Button);
};

#endif
