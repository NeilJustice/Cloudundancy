#pragma once
#include "libCloudundancy/UtilityComponents/Time/StopwatchFactory.h"

namespace Utils
{
   class StopwatchFactoryMock : public Metal::Mock<StopwatchFactory>
   {
   public:
      METALMOCK_NONVOID0_CONST(shared_ptr<Stopwatch>, NewStopwatch)
   };
}
