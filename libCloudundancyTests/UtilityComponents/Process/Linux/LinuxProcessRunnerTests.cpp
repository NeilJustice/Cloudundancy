#include "pch.h"
#ifdef __linux__

#include "libCloudundancy/Components/Process/Linux/LinuxProcessRunner.h"

TESTS(LinuxProcessRunnerTests)
AFACT(Run_DoesNothing_ReturnsDefaultProcessResult)
AFACT(FailFastRun_ReturnsDefaultProcessResult)
EVIDENCE

LinuxProcessRunner _linuxProcessRunner;

TEST(Run_ReturnsDefaultProcessResult)
{
   const string processName = ZenUnit::Random<string>();
   const string arguments = ZenUnit::Random<string>();
   //
   const ProcessResult processResult = _linuxProcessRunner.Run(processName, arguments);
   //
   IS_DEFAULT_VALUE(processResult);
}

TEST(FailFastRun_ReturnsDefaultProcessResult)
{
   const string processName = ZenUnit::Random<string>();
   const string arguments = ZenUnit::Random<string>();
   //
   const ProcessResult processResult = _linuxProcessRunner.FailFastRun(processName, arguments);
   //
   IS_DEFAULT_VALUE(processResult);
}

RUN_TESTS(LinuxProcessRunnerTests)

#endif
