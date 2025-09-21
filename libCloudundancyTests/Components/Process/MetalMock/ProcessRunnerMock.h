#pragma once
#include "libCloudundancy/Components/Process/ProcessRunner.h"

namespace Utils
{
   class ProcessRunnerMock : public Metal::Mock<ProcessRunner>
   {
   public:
      METALMOCK_NONVOID2_CONST(ProcessResult, Run, string_view, string_view)
      METALMOCK_NONVOID3_CONST(ProcessResult, FailFastRun, string_view, string_view, bool)
   };
}