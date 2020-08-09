#pragma once
#ifdef __linux__
#include "libCloudundancy/Components/Process/Linux/LinuxProcessRunner.h"
#include "libCloudundancyTests/Components/Process/ZenUnit/ProcessResultEqualizerAndRandom.h"

class LinuxProcessRunnerMock : public Zen::Mock<LinuxProcessRunner>
{
public:
   ZENMOCK_NONVOID2_CONST(ProcessResult, Run, string_view, string_view)
   ZENMOCK_NONVOID2_CONST(ProcessResult, FailFastRun, string_view, string_view)
};

#endif
