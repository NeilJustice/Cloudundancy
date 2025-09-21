#pragma once
#include "libCloudundancy/Components/Console/ConsoleColorer.h"

namespace Utils
{
   class ConsoleColorerMock : public Metal::Mock<ConsoleColorer>
   {
   public:
      METALMOCK_NONVOID1(bool, SetTextColor, Utils::Color)
      METALMOCK_VOID1_CONST(UnsetTextColor, bool)
   };
}