#pragma once
#include "libCloudundancy/UtilityComponents/Time/CRTWatch.h"

class CRTWatchMock : public Metal::Mock<CRTWatch>
{
public:
   METALMOCK_NONVOID0_CONST(tm, TmNow)
};
