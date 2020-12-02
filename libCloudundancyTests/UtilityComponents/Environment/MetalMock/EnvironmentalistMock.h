#pragma once
#include "libCloudundancy/UtilityComponents/Environment/Environmentalist.h"

class EnvironmentalistMock : public Metal::Mock<Environmentalist>
{
public:
   METALMOCK_NONVOID0_CONST(string, MachineName)
   METALMOCK_NONVOID0_CONST(string, UserName)
};
