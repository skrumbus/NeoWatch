#include"NeoClock.h"
#include<Arduino.h>
#include"ColorStuff.h"

uint32_t NeoClock::hourToSeconds(uint8_t h)
{
  return h * 3600;
}
uint32_t NeoClock::minuteToSeconds(uint8_t m)
{
  return m * 60;
}
NeoClock::NeoClock(uint16_t num, uint8_t pin, neoPixelType n, uint32_t sec, Button show, Button set, Button bt, PatternSettings pattern)
  :NeoRing(num, pin, n)
{
  seconds = sec;
  setShowButton(show);
  setSettingButton(set);
  setBtButton(bt);
  setPattern(pattern);
  setDoShowMinute(true);
  setDoShowSecond(true);
}
NeoClock::NeoClock(uint16_t num, uint8_t pin, neoPixelType n, uint8_t hour, uint8_t min, uint8_t sec, Button show, Button set, Button bt, PatternSettings pattern)
  :NeoRing(num, pin, n)
{
  setHour(hour);
  setMinute(min);
  setSecond(sec);
  setShowButton(show);
  setSettingButton(set);
  setBtButton(bt);
  setPattern(pattern);
  setDoShowMinute(true);
  setDoShowSecond(true);
}
uint8_t NeoClock::getSecond()
{
  return seconds % 60;
}
void NeoClock::setSecond(uint8_t sec)
{
  seconds -= getSecond();
  seconds += constrain(sec, 0, 59);
}
uint8_t NeoClock::getMinute()
{
  return (seconds % 3600) / 60;
}
void NeoClock::setMinute(uint8_t min)
{
  seconds -= minuteToSeconds(getMinute());
  seconds += constrain(minuteToSeconds(min), 0, 59);
}
uint8_t NeoClock::getHour()
{
  return seconds / 3600;
}
void NeoClock::setHour(uint8_t hour)
{
  seconds -= hourToSeconds(getHour());
  seconds += constrain(hourToSeconds(hour), 0, 23);
}
Button NeoClock::getShowButton()
{
  return showButton;
}
void NeoClock::setShowButton(Button show)
{
  showButton = show;
}
Button NeoClock::getSettingButton()
{
  return settingButton;
}
void NeoClock::setSettingButton(Button set)
{
  settingButton = set;
}
Button NeoClock::getBtButton()
{
  return btButton;
}
void NeoClock::setBtButton(Button bt)
{
  btButton = bt;
}
bool NeoClock::getHasNotification()
{
  return hasNotification;
}
void NeoClock::setHasNotification(bool n)
{
  hasNotification = n;
}
PatternSettings NeoClock::getPattern()
{
  return pattern;
}
void NeoClock::setPattern(PatternSettings p)
{
  pattern = p;
}
void NeoClock::update(uint8_t hour, uint8_t minute, uint8_t second)
{
  setHour(hour);
  setMinute(minute);
  setSecond(second);
}
void NeoClock::update(RtcDS3231 clock)
{
  RtcDateTime now = clock.GetDateTime();
  update(now.Hour(), now.Minute(), now.Second());
}
void NeoClock::showTime(bool doMix)
{
  clear();
  if(doMix)
  {
    mixColorToPixel(getHour() % 12, 0, 11, ColorStuff::white(), ColorStuff::white());
    if(doShowMinute)
      mixColorToPixel(getMinute(), 0, 59, ColorStuff::red(), ColorStuff::purple());
    if(doShowSecond)
      mixColorToPixel(getSecond(), 0, 59, ColorStuff::green(), ColorStuff::blue());
  }
  else
  {
    mapColorToPixel(getHour() % 12, 0, 11, ColorStuff::white(), ColorStuff::white());
    if(doShowMinute)
      mapColorToPixel(getMinute(), 0, 59, ColorStuff::red(), ColorStuff::blue());
    if(doShowSecond)
      mapColorToPixel(getSecond(), 0, 59, ColorStuff::green(), ColorStuff::red());
  }
}
void NeoClock::begin(uint8_t type)
{
  NeoRing::begin();
  btButton.begin(type);
  showButton.begin(type);
  settingButton.begin(type);
}

bool NeoClock::getDoShowSecond()
{
  return doShowSecond;
}
void NeoClock::setDoShowSecond(bool b)
{
  doShowSecond = b;
}
bool NeoClock::getDoShowMinute()
{
  return doShowMinute;
}
void NeoClock::setDoShowMinute(bool b)
{
  doShowMinute = b;
}
NeoClock NeoClock::operator++(int)
{
  seconds = (seconds + 1) % 86400;
}

