#pragma once
#include "libCloudundancy/UtilityComponents/Console/ConsoleColorer.h"

class ConsoleColorerMock : public Metal::Mock<ConsoleColorer>
{
public:
   METALMOCK_NONVOID1(bool, SetColor, Color)
   METALMOCK_VOID1_CONST(UnsetColor, bool)
};
