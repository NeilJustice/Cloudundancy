#pragma once
#include "libCloudundancy/Components/Time/date.h"
class WatchTests;

class CRTWatch;

class Watch
{
   friend class ::WatchTests;
private:
   unique_ptr<const CRTWatch> _crtWatch;
public:
   Watch();
   Watch(const Watch&) = delete;
   Watch& operator=(const Watch&) = delete;
   virtual ~Watch();
   virtual string DateTodayString() const;
   virtual string DateTimeNow() const;
   virtual string DateTimeNowHoursMinutesForFileNames() const;
   virtual array<char, 20> FastDateTimeNow() const;
   virtual unsigned SecondsSinceMidnight() const;
   static string YearMonthDayToDateString(const date::year_month_day& yearMonthDay);
private:
   static string MonthDayYearToDateString(size_t month, size_t day, size_t year);
   static void Write8601Date(const tm& tmValue, char* outChars);
};
