#include"NeoClock.h"
#include<Arduino.h>
#include"ColorStuff.h"

NeoClock::NeoClock(uint16_t num, uint8_t pin, neoPixelType n, DateTime now, DateTime alarm, Button show, Button set, Button bt, Pattern pattern)
  :NeoRing(num, pin, n),
   now(now),
   alarm(alarm),
   showButton(show),
   settingButton(set),
   btButton(bt),
   pattern(pattern)
{
  setDoShowMinute(true);
  doMix = false;
  hasAlarm = false;
  hasNotification = false;
  setMinutePrimary(0xFF0000);
  setMinuteSecondary(0xFF0000);
  setHourAm(0xFFFFFF);
  setHourPm(0xFFFFFF);
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
Pattern NeoClock::getPattern()
{
  return pattern;
}
void NeoClock::setPattern(Pattern p)
{
  pattern = p;
}
void NeoClock::update()
{
  update(getCurrentTime());
}
void NeoClock::update(DateTime t)
{
  setCurrentTime(t);
  settingButton.update();
  showButton.update();
  btButton.update();
  buttonResponse();
}
/*void NeoClock::update(RtcDateTime t)
{
  update(DateTime(t.Second(), t.Minute(), t.Hour(), t.Day(), t.Month(), t.Year()));
}*/
void NeoClock::showTime()
{
  if(doMix)
  {
    mixColorToPixel(getCurrentTime().getHour() % 12, 12, (getCurrentTime().getHour() >= 12? getHourPm() : getHourAm()), (getCurrentTime().getHour() >= 12? getHourPm() : getHourAm()));
    if(doShowMinute)
      mixColorToPixel(getCurrentTime().getMinute(), 60, getMinutePrimary(), getMinuteSecondary());
  }
  else
  {
    mapColorToPixel(getCurrentTime().getHour() % 12, 12, (getCurrentTime().getHour() >= 12? getHourPm() : getHourAm()), (getCurrentTime().getHour() >= 12? getHourPm() : getHourAm()));
    if(doShowMinute)
      mapColorToPixel(getCurrentTime().getMinute(), 60, getMinutePrimary(), getMinuteSecondary());
  }
}
void NeoClock::begin(uint8_t type)
{
  NeoRing::begin();
  btButton.begin(type);
  showButton.begin(type);
  settingButton.begin(type);
}

bool NeoClock::getDoShowMinute()
{
  return doShowMinute;
}
void NeoClock::setDoShowMinute(bool b)
{
  doShowMinute = b;
}
NeoClock& NeoClock::operator++(int)
{
  now++;
  return *this;
}
bool NeoClock::getHasAlarm()
{
  return hasAlarm;
}
void NeoClock::setHasAlarm(bool b)
{
  hasAlarm = b;
}
void NeoClock::setCurrentTime(DateTime d)
{
  now = d;
}
DateTime NeoClock::getCurrentTime()
{
  return now;
}
DateTime NeoClock::getAlarm()
{
  return alarm;
}
void NeoClock::setAlarm(DateTime d)
{
  alarm = d;
}
void NeoClock::buttonResponse()
{
  bool i, j, k;
  if(i = getShowButton().isValid() && getShowButton().isPressed())
    showTime();
  if(j = getSettingButton().isValid())
  {
    bool wasHeld = false, wasTapped = getSettingButton().isTapped();
    while(getSettingButton().isPressed() && !wasHeld)
    {
      settingButton.update(1);
      wasHeld = getSettingButton().isHeld();
    }
    if(wasHeld)
      setTime();
    else if(wasTapped)
      incrementBrightness(i);
  }
  if(k = (!i && !j && getBtButton().isValid() && getBtButton().isHeld())) //ONLY CHECK BLUETOOTH IF OTHER BUTTONS NOT PRESSED
  {
    //start bluetooth announcement
  }
}
void NeoClock::incrementBrightness(bool isAlreadyShowingSomething)
{
  uint8_t i = (MAX_BRIGHTNESS - MIN_BRIGHTNESS) / 5;
  i = constrain((getBrightness() + i) % MAX_BRIGHTNESS, MIN_BRIGHTNESS, MAX_BRIGHTNESS);
  setBrightness(i);
  if(!isAlreadyShowingSomething)
  {
    for(uint16_t j = 0; j < 3; j++)
    {
      flash(0xffffff);
      show();
      delay(150);
      clear();
      show();
      delay(150);
    }
  }
}
void NeoClock::setTime()
{
  uint8_t type = 0;
  uint16_t t = 0;
  DateTime d = now;
  while(getSettingButton().isPressed())
  {
    switch(t / 1000)
    {
      case 0:
        showTime();
        break;
      case 1:
        clear();
        break;
    }
    show();
    settingButton.update();
    t = (t + 1) % 1500;
  }
  while(type < 2)
  {
    switch(t / 1000)
    {
      case 0:
        showTime();
        break;
      case 1:
        clear();
        break;
    }
    show();
    showButton.update();
    settingButton.update();
    d.setSecond(0);
    if(getShowButton().isValid() && getShowButton().isTapped())
    {
      switch(type)
      {
        case 0:
          d.setHour((d.getHour() + 1) % 24);
          break;
        case 1:
          d.setMinute((d.getMinute() + 1) % 60);
          break;
      }
    }
    else if(getSettingButton().isValid() && getSettingButton().isTapped())
    {
      type++;
      for(uint8_t i = 0; i < 3; i++)
      {
        showTime();
        show();
        delay(150);
        clear();
        show();
        delay(150);
      }
    }
    t = (t + 1) % 1500;
    setCurrentTime(d);
    clear();
  }
}
bool NeoClock::getDoMix()
{
  return doMix;
}
void NeoClock::setDoMix(bool d)
{
  doMix = d;
}
uint32_t NeoClock::getMinutePrimary()
{
  return minPrimary;
}
void NeoClock::setMinutePrimary(uint32_t minPrimary)
{
  this->minPrimary = minPrimary;
}
uint32_t NeoClock::getMinuteSecondary()
{
  return minSecondary;
}
void NeoClock::setMinuteSecondary(uint32_t minSecondary)
{
  this->minSecondary = minSecondary;
}
uint32_t NeoClock::getHourAm()
{
  return hourAm;
}
void NeoClock::setHourAm(uint32_t hourAm)
{
  this->hourAm = hourAm;
}
uint32_t NeoClock::getHourPm()
{
  return hourPm;
}
void NeoClock::setHourPm(uint32_t hourPm)
{
  this->hourPm = hourPm;
}
