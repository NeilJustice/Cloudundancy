#pragma once
#include "libCloudundancy/Components/Process/ProcessRunner.h"
#include "libCloudundancyTests/Components/Process/ZenUnit/ProcessResultEqualizerAndRandom.h"

class ProcessRunnerMock : public Metal::Mock<ProcessRunner>
{
public:
   METALMOCK_NONVOID2_CONST(ProcessResult, Run, string_view, string_view)
   METALMOCK_NONVOID2_CONST(ProcessResult, FailFastRun, string_view, string_view)
};
