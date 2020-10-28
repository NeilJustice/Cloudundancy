#include "pch.h"
#include "libCloudundancy/Components/Time/Watch.h"
#include "libCloudundancy/Components/Conversion/Chars.h"
#include "libCloudundancy/Components/Time/CRTWatch.h"

Watch::Watch()
   : _crtWatch(make_unique<CRTWatch>())
{
}

string Watch::SecondsToHHMMSS(unsigned seconds) const
{
   const unsigned totalHours = seconds / 3600;
   release_assert(totalHours <= 99);
   const unsigned totalMinutes = seconds / 60;
   const unsigned minutesPart = totalMinutes % 60;
   const unsigned secondsPart = seconds % 60;
   array<char, 8> hhmmssChars { 0, 0, ':', 0, 0, ':', 0, 0 };
   Chars::OneOrTwoDigitUnsignedToTwoChars(totalHours, hhmmssChars.data());
   Chars::OneOrTwoDigitUnsignedToTwoChars(minutesPart, hhmmssChars.data() + 3);
   Chars::OneOrTwoDigitUnsignedToTwoChars(secondsPart, hhmmssChars.data() + 6);
   const string hhmmssString(hhmmssChars.data(), hhmmssChars.size());
   return hhmmssString;
}

// Writes MM/DD/YYYY to outChars
string Watch::MonthDayYearToDateString(unsigned month, unsigned day, unsigned year)
{
   char dateChars[10]; // 10 == strlen("MM/DD/YYYY")
   Chars::OneOrTwoDigitUnsignedToTwoChars(month, dateChars);
   dateChars[2] = '-';
   Chars::OneOrTwoDigitUnsignedToTwoChars(day, dateChars + 3);
   dateChars[5] = '-';
   Chars::FourDigitUnsignedToFourChars(year, dateChars + 6);
   const string dateString(dateChars, sizeof(dateChars));
   return dateString;
}

string Watch::DateTimeNowHoursMinutesForFileNames() const
{
   const tm tmNow = _crtWatch->TmNow();
   // 16 == strlen("2100-01-01_00-00")
   //               0123456789012345
   array<char, 17> chars;
   Write8601Date(tmNow, chars.data());
   chars[10] = '_';
   Chars::OneOrTwoDigitUnsignedToTwoChars(static_cast<unsigned>(tmNow.tm_hour), chars.data() + 11);
   chars[13] = '-';
   Chars::OneOrTwoDigitUnsignedToTwoChars(static_cast<unsigned>(tmNow.tm_min), chars.data() + 14);
   chars[16] = 0;
   const string dateTimeNowForFileNames(chars.data());
   return dateTimeNowForFileNames;
}

unsigned Watch::SecondsSinceMidnight() const
{
   const tm nowTm = _crtWatch->TmNow();
   const int secondsSinceMidnight = nowTm.tm_hour * 60 * 60 + nowTm.tm_min * 60 + nowTm.tm_sec;
   return static_cast<unsigned>(secondsSinceMidnight);
}

int Watch::DaysBetweenDates(const date::year_month_day& yearMonthDay1, const date::year_month_day& yearMonthDay2) const
{
   const date::sys_days days2 = date::sys_days(yearMonthDay2);
   const date::sys_days days1 = date::sys_days(yearMonthDay1);
   const std::common_type_t<date::days, date::days> sysDaysDifference = days2 - days1;
   const int daysDifference = sysDaysDifference.count();
   return daysDifference;
}

void Watch::Write8601Date(const tm& tmValue, char* outChars)
{
   const unsigned year = 1900u + static_cast<unsigned>(tmValue.tm_year);
   Chars::FourDigitUnsignedToFourChars(year, outChars);
   outChars[4] = '-';
   const unsigned zeroBasedMonth = static_cast<unsigned>(tmValue.tm_mon);
   Chars::OneOrTwoDigitUnsignedToTwoChars(zeroBasedMonth + 1, outChars + 5);
   outChars[7] = '-';
   const unsigned day = static_cast<unsigned>(tmValue.tm_mday);
   Chars::OneOrTwoDigitUnsignedToTwoChars(day, outChars + 8);
}

Watch::~Watch()
{
}
