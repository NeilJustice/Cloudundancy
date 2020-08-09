#pragma once
#include "libCloudundancy/Components/Time/Watch.h"

class WatchMock : public Zen::Mock<Watch>
{
public:
	METALMOCK_NONVOID0_CONST(string, DateTimeNowHoursMinutesForFileNames)
   METALMOCK_NONVOID0_CONST(unsigned, SecondsSinceMidnight)
   METALMOCK_NONVOID2_CONST(int, DaysBetweenDates, const date::year_month_day&, const date::year_month_day&)
   METALMOCK_NONVOID1_CONST(string, SecondsToHHMMSS, unsigned)
};
