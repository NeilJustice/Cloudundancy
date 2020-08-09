#pragma once
#include "libCloudundancy/Components/Process/ProcessRunner.h"
#include "libCloudundancyTests/Components/Process/ZenUnit/ProcessResultEqualizerAndRandom.h"

class ProcessRunnerMock : public Zen::Mock<ProcessRunner>
{
public:
   ZENMOCK_NONVOID2_CONST(ProcessResult, Run, string_view, string_view)
   ZENMOCK_NONVOID2_CONST(ProcessResult, FailFastRun, string_view, string_view)
};
