#include "pch.h"
#include "libCloudundancy/UtilityComponents/Time/Stopwatch.h"
#include "libCloudundancy/UtilityComponents/Time/StopwatchFactory.h"

namespace Utils
{
   shared_ptr<Stopwatch> StopwatchFactory::NewStopwatch() const
   {
      return make_shared<Stopwatch>();
   }
}
