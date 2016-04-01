#include"NeoClock.h"
#include<Arduino.h>
#include"ColorStuff.h"

NeoClock::NeoClock(uint16_t num, uint8_t pin, neoPixelType n, DateTime now, DateTime alarm, Button show, Button set, Button bt, PatternSettings pattern)
  :NeoRing(num, pin, n),
   now(now),
   alarm(alarm),
   showButton(show),
   settingButton(set),
   btButton(bt),
   pattern(pattern)
{
  setDoShowMinute(true);
  setDoShowSecond(true);
  doMix = false;
  hasAlarm = false;
  hasNotification = false;
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
void NeoClock::update(RtcDateTime t)
{
  update(DateTime(t.Second(), t.Minute(), t.Hour(), t.Day(), t.Month(), t.Year()));
}
void NeoClock::showTime()
{
  if(doMix)
  {
    mixColorToPixel(getCurrentTime().getHour() % 12, 0, 11, ColorStuff::white(), ColorStuff::white());
    if(doShowMinute)
      mixColorToPixel(getCurrentTime().getMinute(), 0, 59, ColorStuff::red(), ColorStuff::blue());
    if(doShowSecond)
      mixColorToPixel(getCurrentTime().getSecond(), 0, 59, ColorStuff::green(), ColorStuff::blue());
  }
  else
  {
    mapColorToPixel(getCurrentTime().getHour() % 12, 0, 11, ColorStuff::white(), ColorStuff::white());
    if(doShowMinute)
      mapColorToPixel(getCurrentTime().getMinute(), 0, 59, ColorStuff::red(), ColorStuff::blue());
    if(doShowSecond)
      mapColorToPixel(getCurrentTime().getSecond(), 0, 59, ColorStuff::green(), ColorStuff::red());
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
  delay(100);
  t = 0;
  while(type < 3)
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
    if(getShowButton().isValid() && getShowButton().isTapped())
    {
      switch(type)
      {
        case 0:
          d.setHour((d.getHour() + 1) % 23);
          break;
        case 1:
          d.setMinute((d.getMinute() + 1) % 60);
          break;
        case 2:
          d.setSecond((d.getSecond() + 1) % 60);
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

