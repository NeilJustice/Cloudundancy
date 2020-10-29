#include "pch.h"
#include "libCloudundancy/Components/Time/CRTWatch.h"
#include "libCloudundancy/Components/Time/Watch.h"
#include "libCloudundancy/Utilities/Chars.h"

Watch::Watch()
   : _crtWatch(new CRTWatch)
{
}

string Watch::DateTodayString() const
{
   const tm tmNow = _crtWatch->TmNow();
   const unsigned month = static_cast<unsigned>(tmNow.tm_mon + 1);
   const unsigned day = static_cast<unsigned>(tmNow.tm_mday);
   const unsigned year = static_cast<unsigned>(1900 + tmNow.tm_year);
   const string dateString = MonthDayYearToDateString(month, day, year);
   return dateString;
}

string Watch::YearMonthDayToDateString(const date::year_month_day& yearMonthDay)
{
   const unsigned month = static_cast<unsigned>(yearMonthDay.month());
   const unsigned day = static_cast<unsigned>(yearMonthDay.day());
   const unsigned year = static_cast<unsigned>(static_cast<int>(yearMonthDay.year()));
   const string dateString = MonthDayYearToDateString(month, day, year);
   return dateString;
}

// Writes MM/DD/YYYY to outChars
string Watch::MonthDayYearToDateString(size_t month, size_t day, size_t year)
{
   char dateChars[10]; // 10 == strlen("MM/DD/YYYY")
   Chars::OneOrTwoDigitSizeTToTwoChars(month, dateChars);
   dateChars[2] = '-';
   Chars::OneOrTwoDigitSizeTToTwoChars(day, dateChars + 3);
   dateChars[5] = '-';
   Chars::FourDigitSizeTToFourChars(year, dateChars + 6);
   const string dateString(dateChars, sizeof(dateChars));
   return dateString;
}

string Watch::DateTimeNow() const
{
   return string(FastDateTimeNow().data());
}

string Watch::DateTimeNowHoursMinutesForFileNames() const
{
   const tm tmNow = _crtWatch->TmNow();
   // 16 == strlen("2100-01-01 00:00")
   //               0123456789012345
   array<char, 17> chars;
   Write8601Date(tmNow, chars.data());
   chars[10] = '_';
   Chars::OneOrTwoDigitSizeTToTwoChars(static_cast<size_t>(tmNow.tm_hour), chars.data() + 11);
   chars[13] = '-';
   Chars::OneOrTwoDigitSizeTToTwoChars(static_cast<size_t>(tmNow.tm_min), chars.data() + 14);
   chars[16] = 0;
   const string dateTimeNowForFileNames(chars.data());
   return dateTimeNowForFileNames;
}

array<char, 20> Watch::FastDateTimeNow() const
{
   const tm tmNow = _crtWatch->TmNow();
   // 19 == strlen("2100-01-01 00:00:00")
   //               0123456789012345678
   array<char, 20> iso8601DateTime;
   Write8601Date(tmNow, iso8601DateTime.data());
   iso8601DateTime[10] = ' ';
   Chars::OneOrTwoDigitSizeTToTwoChars(static_cast<size_t>(tmNow.tm_hour), iso8601DateTime.data() + 11);
   iso8601DateTime[13] = ':';
   Chars::OneOrTwoDigitSizeTToTwoChars(static_cast<size_t>(tmNow.tm_min), iso8601DateTime.data() + 14);
   iso8601DateTime[16] = ':';
   Chars::OneOrTwoDigitSizeTToTwoChars(static_cast<size_t>(tmNow.tm_sec), iso8601DateTime.data() + 17);
   iso8601DateTime[19] = 0;
   return iso8601DateTime;
}

unsigned Watch::SecondsSinceMidnight() const
{
   const tm nowTm = _crtWatch->TmNow();
   const int secondsSinceMidnight = nowTm.tm_hour * 60 * 60 + nowTm.tm_min * 60 + nowTm.tm_sec;
   return static_cast<unsigned>(secondsSinceMidnight);
}

void Watch::Write8601Date(const tm& tmValue, char* outChars)
{
   const unsigned year = 1900u + static_cast<unsigned>(tmValue.tm_year);
   Chars::FourDigitSizeTToFourChars(year, outChars);
   outChars[4] = '-';
   const size_t zeroBasedMonth = static_cast<size_t>(tmValue.tm_mon);
   Chars::OneOrTwoDigitSizeTToTwoChars(zeroBasedMonth + 1, outChars + 5);
   outChars[7] = '-';
   const size_t day = static_cast<size_t>(tmValue.tm_mday);
   Chars::OneOrTwoDigitSizeTToTwoChars(day, outChars + 8);
}

Watch::~Watch()
{
}
