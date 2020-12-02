#pragma once
#include "libCloudundancy/UtilityComponents/Time/Stopwatch.h"

class StopwatchMock : public Metal::Mock<Stopwatch>
{
public:
   METALMOCK_VOID0(Start)
   METALMOCK_NONVOID0(unsigned, StopAndGetElapsedMilliseconds)
   METALMOCK_NONVOID0(long long, StopAndGetElapsedMicroseconds)
   METALMOCK_NONVOID0(string, StopAndGetElapsedSeconds)
};
