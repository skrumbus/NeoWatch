#include"DateTime.h"
#include"Arduino.h"

uint8_t DateTime::getSecond()
{
  return second;
}
void DateTime::setSecond(uint8_t sec)
{
  this->second = constrain(sec, 0, 59);
}
uint8_t DateTime::getMinute()
{
  return minute;
}
void DateTime::setMinute(uint8_t min)
{
  this->minute = constrain(min, 0, 59);
}
uint8_t DateTime::getHour()
{
  return hour;
}
void DateTime::setHour(uint8_t hour)
{
  this->hour = constrain(hour, 0, 23);
}
uint8_t DateTime::getDay()
{
  return day;
}
void DateTime::setDay(uint8_t day)
{
  this->day = constrain(day, 1, daysInMonth(getMonth(), getYear()));
}
uint8_t DateTime::getMonth()
{
  return month;
}
void DateTime::setMonth(uint8_t month)
{
  this->month = constrain(month, 1, 12);
}
uint16_t DateTime::getYear()
{
  return year;
}
void DateTime::setYear(uint16_t year)
{
  if(year > 0)
    this->year = year;
  else
    this->year = 1;
}
DateTime::DateTime(uint8_t second, uint8_t minute, uint8_t hour, uint8_t day, uint8_t month, uint16_t year)
{
  setSecond(second);
  setMinute(minute);
  setHour(hour);
  setDay(day);
  setMonth(month);
  setYear(year);
}
DateTime& DateTime::operator++(int)
{
  if(++second == 60)
  {
    if(++minute == 60)
    {
      if(++hour == 24)
      {
        if(++day == daysInMonth(getMonth(), getYear()))
        {
          if(++month == 12)
          {
            ++year;
            month = 1;
          }
          day = 1;
        }
        hour = 0;
      }
      minute = 0;
    }
    second = 0;
  }
  return *this;
}
uint8_t DateTime::daysInMonth(uint8_t month, uint16_t year)
{
  switch(month)
  {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 12:
      return 31;
    case 4:
    case 6:
    case 9:
    case 11:
      return 30;
    case 2:
      if(getYear() % 4 == 0)
        return 29;
      else
        return 28;
    default:
      return 0;
  }
}

