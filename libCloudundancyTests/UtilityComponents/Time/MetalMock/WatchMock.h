#pragma once
#include "libCloudundancy/UtilityComponents/Time/Watch.h"

namespace Utils
{
   class WatchMock : public Metal::Mock<Watch>
   {
   public:
      METALMOCK_NONVOID0_CONST(string, DateTimeNow)
      METALMOCK_NONVOID0_CONST(string, DateTimeNowForFileNames)
   };
}