#pragma once
#ifdef _WIN32
#include "libCloudundancy/Components/Process/Windows/WindowsProcessRunner.h"

namespace Utils
{
   class WindowsProcessRunnerMock : public Metal::Mock<WindowsProcessRunner>
   {
   public:
      METALMOCK_NONVOID2_CONST(ProcessResult, Run, string_view, string_view)
      METALMOCK_NONVOID3_CONST(ProcessResult, FailFastRun, string_view, string_view, bool)
   };
}

#endif
