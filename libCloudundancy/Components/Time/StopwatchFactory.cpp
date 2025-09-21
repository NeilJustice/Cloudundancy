#include "pch.h"
#include "libCloudundancy/Components/Time/Stopwatch.h"
#include "libCloudundancy/Components/Time/StopwatchFactory.h"

namespace Utils
{
   shared_ptr<Stopwatch> StopwatchFactory::NewStopwatch() const
   {
      return make_shared<Stopwatch>();
   }
}
