#pragma once
#ifdef _WIN32
#include "libCloudundancy/UtilityComponents/Process/Windows/WindowsProcessRunner.h"

class WindowsProcessRunnerMock : public Metal::Mock<WindowsProcessRunner>
{
public:
   METALMOCK_NONVOID2_CONST(ProcessResult, Run, string_view, string_view)
   METALMOCK_NONVOID2_CONST(ProcessResult, FailFastRun, string_view, string_view)
};

#endif
