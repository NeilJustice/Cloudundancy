#pragma once
#include "libCloudundancy/UtilityComponents/Environment/EnvironmentService.h"

namespace Utils
{
   class EnvironmentServiceMock : public Metal::Mock<EnvironmentService>
   {
   public:
      METALMOCK_NONVOID0_CONST(string, MachineName)
      METALMOCK_NONVOID0_CONST(string, UserName)
   };
}