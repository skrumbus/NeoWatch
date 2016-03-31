#ifndef NEO_CLOCK
#define NEO_CLOCK

#include"NeoRing.h"
#include"Button.h"
#include"PatternSettings.h"
#include <RtcDS3231.h>

class NeoClock
  :public NeoRing
{
  private:
    uint32_t seconds;
    Button showButton;
    Button settingButton;
    Button btButton;
    PatternSettings pattern;
    bool hasNotification;
    uint32_t hourToSeconds(uint8_t);
    uint32_t minuteToSeconds(uint8_t);
    bool doShowSecond, doShowMinute;
  public:
    NeoClock(uint16_t, uint8_t = 6, neoPixelType = NEO_GRB + NEO_KHZ800, uint32_t = 0, Button show = Button(), Button set = Button(), Button bt = Button(), PatternSettings = PatternSettings());
    NeoClock(uint16_t, uint8_t, neoPixelType, uint8_t, uint8_t, uint8_t, Button show = Button(), Button set = Button(), Button bt = Button(), PatternSettings = PatternSettings());
    uint8_t getSecond();
    void setSecond(uint8_t);
    uint8_t getMinute();
    void setMinute(uint8_t);
    uint8_t getHour();
    void setHour(uint8_t);
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
    void update(uint8_t, uint8_t, uint8_t);
    void update(RtcDS3231);
    void showTime(bool = false);
    void begin(uint8_t = INPUT_PULLUP);
    NeoClock operator++(int);
};

#endif
