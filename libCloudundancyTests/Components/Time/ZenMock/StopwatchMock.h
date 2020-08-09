#pragma once
#include "libCloudundancy/Components/Time/Stopwatch.h"

class StopwatchMock : public Zen::Mock<Stopwatch>
{
public:
   ZENMOCK_VOID0(Start)
   ZENMOCK_NONVOID0(unsigned, StopAndGetElapsedMilliseconds)
   ZENMOCK_NONVOID0(long long, StopAndGetElapsedMicroseconds)
   ZENMOCK_NONVOID0(string, StopAndGetElapsedSeconds)
};
