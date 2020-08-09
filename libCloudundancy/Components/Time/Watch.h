#pragma once
#include <array>
#include "libCloudundancy/Components/Time/date.h"
class CRTWatch;
class WatchTests;

class Watch
{
   friend class ::WatchTests;
private:
   unique_ptr<const CRTWatch> _crtWatch;
public:
   Watch();
   virtual ~Watch();
   virtual string DateTimeNowHoursMinutesForFileNames() const;
   virtual unsigned SecondsSinceMidnight() const;
   virtual int DaysBetweenDates(const date::year_month_day& yearMonthDay1, const date::year_month_day& yearMonthDay2) const;
   virtual string SecondsToHHMMSS(unsigned seconds) const;
private:
   static string MonthDayYearToDateString(unsigned month, unsigned day, unsigned year);
   static void Write8601Date(const tm& tmValue, char* outChars);
};
