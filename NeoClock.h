#ifndef NEO_CLOCK
#define NEO_CLOCK

#define MAX_BRIGHTNESS 48
#define MIN_BRIGHTNESS 8

#include"NeoRing.h"
#include"Button.h"
#include"Pattern.h"
#include"DateTime.h"
//#include <RtcDS3231.h>

class NeoClock
  :public NeoRing
{
  private:
    DateTime now, alarm;
    Button showButton;
    Button settingButton;
    Button btButton;
    Pattern pattern;
    bool hasNotification;
    bool  doShowMinute;
    bool hasAlarm;
    bool doMix;
    uint32_t minPrimary, minSecondary, hourAm, hourPm;
    void buttonResponse();
    void incrementBrightness(bool);
    void setTime();
  public:
    NeoClock(uint16_t, uint8_t = 6, neoPixelType = NEO_GRB + NEO_KHZ800, DateTime = DateTime(), DateTime = DateTime(), Button show = Button(), Button set = Button(), Button bt = Button(), Pattern = Pattern());
    Button getShowButton();
    void setShowButton(Button);
    Button getSettingButton();
    void setSettingButton(Button);
    Button getBtButton();
    void setBtButton(Button);
    bool getHasNotification();
    void setHasNotification(bool);
    bool getDoShowMinute();
    void setDoShowMinute(bool);
    Pattern getPattern();
    void setPattern(Pattern);
    void update();
    void update(DateTime);
//    void update(RtcDateTime);
    void showTime();
    void begin(uint8_t = INPUT_PULLUP);
    NeoClock& operator++(int);
    DateTime getCurrentTime();
    void setCurrentTime(DateTime);
    DateTime getAlarm();
    void setAlarm(DateTime);
    bool getHasAlarm();
    void setHasAlarm(bool);
    bool getDoMix();
    void setDoMix(bool);
    uint32_t getMinutePrimary();
    void setMinutePrimary(uint32_t);
    uint32_t getMinuteSecondary();
    void setMinuteSecondary(uint32_t);
    uint32_t getHourAm();
    void setHourAm(uint32_t);
    uint32_t getHourPm();
    void setHourPm(uint32_t);
};

#endif
