#include "pch.h"
#include "libCloudundancy/Components/Time/StopwatchFactory.h"

TESTS(StopwatchFactoryTests)
AFACT(NewStopwatch_ReturnsNewStopwatch)
EVIDENCE

TEST(NewStopwatch_ReturnsNewStopwatch)
{
   Utils::StopwatchFactory stopwatchFactory;
   //
   shared_ptr<Utils::Stopwatch> stopwatch1 = stopwatchFactory.NewStopwatch();
   shared_ptr<Utils::Stopwatch> stopwatch2 = stopwatchFactory.NewStopwatch();
   //
   ARE_NOT_EQUAL(stopwatch1.get(), stopwatch2.get());
}

RUN_TESTS(StopwatchFactoryTests)
