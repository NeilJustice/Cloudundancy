#pragma once
#include "libCloudundancy/Components/Time/Watch.h"

class WatchMock : public Metal::Mock<Watch>
{
public:
   METALMOCK_NONVOID0_CONST(string, DateTodayString)

   METALMOCK_NONVOID0_CONST(string, DateTimeNow)

   METALMOCK_NONVOID0_CONST(string, DateTimeNowHoursMinutesForFileNames)

   using C20 = array<char, 20>;
   METALMOCK_NONVOID0_CONST(C20, FastDateTimeNow)

   METALMOCK_NONVOID0_CONST(unsigned, SecondsSinceMidnight)
};
