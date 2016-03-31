#ifndef BUTTON_H
#define BUTTON_H

#include<stdint.h>
#include<Arduino.h>

class Button
{
  private:
    uint8_t pin;
    uint8_t onState;
    uint8_t state;
    uint16_t hold, holdTime;
  public:
    Button();
    Button(uint8_t pin, uint8_t onState, uint16_t holdTime = 3000);
    uint8_t getState();
    bool isReleased();
    bool isTapped();
    bool isPressed();
    bool isHeld();
    void update(uint16_t = 0);
    void setHoldTime(uint16_t);
    uint16_t getHoldTime();
    void begin(uint8_t = INPUT_PULLUP);
};

#endif
