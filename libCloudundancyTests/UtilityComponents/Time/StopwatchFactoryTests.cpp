#include "pch.h"
#include "libCloudundancy/UtilityComponents/Time/StopwatchFactory.h"

TESTS(StopwatchFactoryTests)
AFACT(NewStopwatch_ReturnsNewStopwatch)
EVIDENCE

TEST(NewStopwatch_ReturnsNewStopwatch)
{
   Time::StopwatchFactory stopwatchFactory;
   //
   shared_ptr<Time::Stopwatch> stopwatch1 = stopwatchFactory.NewStopwatch();
   shared_ptr<Time::Stopwatch> stopwatch2 = stopwatchFactory.NewStopwatch();
   //
   ARE_NOT_EQUAL(stopwatch1.get(), stopwatch2.get());
}

RUN_TESTS(StopwatchFactoryTests)
