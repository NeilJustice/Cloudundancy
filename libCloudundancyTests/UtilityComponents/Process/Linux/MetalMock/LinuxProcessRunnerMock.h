#pragma once
#ifdef __linux__
#include "libCloudundancy/Components/Process/Linux/LinuxProcessRunner.h"
#include "libCloudundancyTests/Components/Process/ZenUnit/ProcessResultEqualizerAndRandom.h"

class LinuxProcessRunnerMock : public Metal::Mock<LinuxProcessRunner>
{
public:
   METALMOCK_NONVOID2_CONST(ProcessResult, Run, string_view, string_view)
   METALMOCK_NONVOID3_CONST(ProcessResult, FailFastRun, string_view, string_view, bool)
};

#endif
