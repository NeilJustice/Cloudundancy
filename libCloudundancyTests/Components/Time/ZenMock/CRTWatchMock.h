#pragma once
#include "libCloudundancy/Components/Time/CRTWatch.h"

class CRTWatchMock : public Zen::Mock<CRTWatch>
{
public:
   ZENMOCK_NONVOID0_CONST(tm, TmNow)
};
