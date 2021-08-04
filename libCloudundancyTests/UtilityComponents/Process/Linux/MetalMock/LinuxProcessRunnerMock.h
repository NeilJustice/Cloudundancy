#pragma once
#if defined __linux__ || defined __APPLE__
#include "libCloudundancy/UtilityComponents/Process/Linux/LinuxProcessRunner.h"

namespace Utils
{
   class LinuxProcessRunnerMock : public Metal::Mock<LinuxProcessRunner>
   {
   public:
      METALMOCK_NONVOID2_CONST(ProcessResult, Run, string_view, string_view)
      METALMOCK_NONVOID3_CONST(ProcessResult, FailFastRun, string_view, string_view, bool)
   };
}

#endif
