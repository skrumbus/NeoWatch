#ifndef NEO_CLOCK
#define NEO_CLOCK

#define MAX_BRIGHTNESS 48
#define MIN_BRIGHTNESS 8

#include"NeoRing.h"
#include"Button.h"
#include"PatternSettings.h"
#include"DateTime.h"
#include <RtcDS3231.h>

class NeoClock
  :public NeoRing
{
  private:
    DateTime now, alarm;
    Button showButton;
    Button settingButton;
    Button btButton;
    PatternSettings pattern;
    bool hasNotification;
    bool doShowSecond, doShowMinute;
    bool hasAlarm;
    void buttonResponse();
    void incrementBrightness(bool);
  public:
    NeoClock(uint16_t, uint8_t = 6, neoPixelType = NEO_GRB + NEO_KHZ800, DateTime = DateTime(), DateTime = DateTime(), Button show = Button(), Button set = Button(), Button bt = Button(), PatternSettings = PatternSettings());
    Button getShowButton();
    void setShowButton(Button);
    Button getSettingButton();
    void setSettingButton(Button);
    Button getBtButton();
    void setBtButton(Button);
    bool getHasNotification();
    void setHasNotification(bool);
    bool getDoShowSecond();
    void setDoShowSecond(bool);
    bool getDoShowMinute();
    void setDoShowMinute(bool);
    PatternSettings getPattern();
    void setPattern(PatternSettings);
    void update();
    void update(DateTime);
    void update(RtcDateTime);
    void showTime(bool = false);
    void begin(uint8_t = INPUT_PULLUP);
    NeoClock& operator++(int);
    DateTime getCurrentTime();
    void setCurrentTime(DateTime);
    DateTime getAlarm();
    void setAlarm(DateTime);
    bool getHasAlarm();
    void setHasAlarm(bool);
    void setTime();
};

#endif
