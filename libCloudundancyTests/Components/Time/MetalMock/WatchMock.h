#pragma once
#include "libCloudundancy/Components/Time/Watch.h"

class WatchMock : public Metal::Mock<Watch>
{
public:
   METALMOCK_NONVOID0_CONST(string, DateTimeNow)
   METALMOCK_NONVOID0_CONST(string, DateTimeNowForFileNames)
};
