#ifndef DATE_TIME_H
#define DATE_TIME_H

#include<stdint.h>

class DateTime
{
  protected:
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t day;
    uint8_t month;
    uint16_t year;
    uint8_t daysInMonth(uint8_t, uint16_t);
  public:
    DateTime(uint8_t s = 0, uint8_t m = 0, uint8_t h = 0, uint8_t d = 1, uint8_t M = 1, uint16_t y = 1);
    uint8_t getSecond();
    void setSecond(uint8_t);
    uint8_t getMinute();
    void setMinute(uint8_t);
    uint8_t getHour();
    void setHour(uint8_t);
    uint8_t getDay();
    void setDay(uint8_t);
    uint8_t getMonth();
    void setMonth(uint8_t);
    uint16_t getYear();
    void setYear(uint16_t);   
    DateTime& operator++(int);
};

#endif
