#pragma once
#include "libCloudundancy/Components/Time/Watch.h"

class WatchMock : public Zen::Mock<Watch>
{
public:
	ZENMOCK_NONVOID0_CONST(string, DateTimeNowHoursMinutesForFileNames)
   ZENMOCK_NONVOID0_CONST(unsigned, SecondsSinceMidnight)
   ZENMOCK_NONVOID2_CONST(int, DaysBetweenDates, const date::year_month_day&, const date::year_month_day&)
   ZENMOCK_NONVOID1_CONST(string, SecondsToHHMMSS, unsigned)
};
