#pragma once
#include "libCloudundancy/Components/Time/Stopwatch.h"

class StopwatchMock : public Zen::Mock<Stopwatch>
{
public:
   METALMOCK_VOID0(Start)
   METALMOCK_NONVOID0(unsigned, StopAndGetElapsedMilliseconds)
   METALMOCK_NONVOID0(long long, StopAndGetElapsedMicroseconds)
   METALMOCK_NONVOID0(string, StopAndGetElapsedSeconds)
};
