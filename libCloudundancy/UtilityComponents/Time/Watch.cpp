#include "pch.h"
#include "libCloudundancy/UtilityComponents/Time/Watch.h"

Watch::Watch() noexcept
   : _crtWatch(make_unique<CRTWatch>())
{
}

Watch::~Watch()
{
}

// Returns the current local time in format "YYYY-MM-DD 00:00:00"
std::string Watch::DateTimeNow() const
{
   const tm tmNow = TMNow();
   char dateTimeNowChars[32]{};
   strftime(dateTimeNowChars, sizeof(dateTimeNowChars), "%F %r", &tmNow);
   std::string dateTimeNowString(dateTimeNowChars);
   return dateTimeNowString;
}

// Returns the current local time in format "YYYY-MM-DD 00:00:00 TimeZone"
string Watch::DateTimeNowForFileNames() const
{
   const tm tmNow = _crtWatch->TmNow();
   // 16 == strlen("2100-01-01T00-00-00")
   //               0123456789012345678
   array<char, 19> chars;
   Write8601Date(tmNow, chars.data());
   chars[10] = 'T';
   Chars::OneOrTwoDigitSizeTToTwoChars(static_cast<size_t>(tmNow.tm_hour), chars.data() + 11);
   chars[13] = '-';
   Chars::OneOrTwoDigitSizeTToTwoChars(static_cast<size_t>(tmNow.tm_min), chars.data() + 14);
   chars[16] = '-';
   Chars::OneOrTwoDigitSizeTToTwoChars(static_cast<size_t>(tmNow.tm_sec), chars.data() + 17);
   string dateTimeNowForFileNames(chars.data(), chars.size());
   return dateTimeNowForFileNames;
}

// Private Functions

tm Watch::TMNow() const
{
   const std::chrono::time_point<std::chrono::system_clock> nowTimePoint = std::chrono::system_clock::now();
#if defined __linux__ || defined __APPLE__
   tm* tmNow = nullptr;
   long nowTimeT = std::chrono::system_clock::to_time_t(nowTimePoint);
   tmNow = localtime(&nowTimeT);
   return *tmNow;
#elif defined _WIN32
   const __time64_t nowTimeT = std::chrono::system_clock::to_time_t(nowTimePoint);
   tm tmNow{};
   const errno_t localtimeResult = localtime_s(&tmNow, &nowTimeT);
   release_assert(localtimeResult == 0);
   return tmNow;
#endif
}

void Watch::Write8601Date(const tm& tmValue, char* outChars)
{
   const unsigned year = 1900U + static_cast<unsigned>(tmValue.tm_year);
   Chars::FourDigitSizeTToFourChars(year, outChars);
   outChars[4] = '-';
   const size_t zeroBasedMonth = static_cast<size_t>(tmValue.tm_mon);
   Chars::OneOrTwoDigitSizeTToTwoChars(zeroBasedMonth + 1, outChars + 5);
   outChars[7] = '-';
   const size_t day = static_cast<size_t>(tmValue.tm_mday);
   Chars::OneOrTwoDigitSizeTToTwoChars(day, outChars + 8);
}
