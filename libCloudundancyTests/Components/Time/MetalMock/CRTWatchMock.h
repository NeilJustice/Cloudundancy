#pragma once
#include "libCloudundancy/Components/Time/CRTWatch.h"

namespace Utils
{
   class CRTWatchMock : public Metal::Mock<CRTWatch>
   {
   public:
      METALMOCK_NONVOID0_CONST(tm, TmNow)
   };
}
