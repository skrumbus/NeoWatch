#include"Button.h"

Button::Button()
{
  this->pin = 0;
  this->onState = 0;
  setHoldTime(65535);
  state = 255;
}
Button::Button(uint8_t pin, uint8_t onState, uint16_t holdTime)
{
  this->pin = pin;
  this->onState = onState;
  setHoldTime(holdTime);
  state = 0;
}
uint8_t Button::getState()
{
  return state;
}
bool Button::isReleased()
{
  return state == 0;
}
bool Button::isTapped()
{
  return getState() == 1;
}
bool Button::isPressed()
{
  return (getState() == 1 || getState() == 2 || getState() == 3);
}
bool Button::isHeld()
{
  return getState() == 2;
}
void Button::update(uint16_t t)
{
  if(digitalRead(pin) == onState)
  {
    state = (state == 1 || state == 3? 3 : 1);
    hold += t;
    if(hold >= holdTime)
      state = 2;
  }
  else
    state = hold = 0;
}
void Button::setHoldTime(uint16_t holdTime)
{
  this->holdTime = holdTime;
}
uint16_t Button::getHoldTime()
{
  return holdTime;
}
void Button::begin(uint8_t type)
{
  pinMode(pin, type);
}
bool Button::isValid()
{
  return ((onState == HIGH || onState == LOW) &&
          (state == 0 || state == 1 || state == 2 || state == 3));
}

