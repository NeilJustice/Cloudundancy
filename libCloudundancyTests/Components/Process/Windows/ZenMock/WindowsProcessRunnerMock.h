#pragma once
#ifdef _WIN32
#include "libCloudundancy/Components/Process/Windows/WindowsProcessRunner.h"
#include "libCloudundancyTests/Components/Process/ZenUnit/ProcessResultEqualizerAndRandom.h"

class WindowsProcessRunnerMock : public Zen::Mock<WindowsProcessRunner>
{
public:
   ZENMOCK_NONVOID2_CONST(ProcessResult, Run, string_view, string_view)
   ZENMOCK_NONVOID2_CONST(ProcessResult, FailFastRun, string_view, string_view)
};

#endif
