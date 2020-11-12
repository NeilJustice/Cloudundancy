#include "pch.h"
#ifdef __linux__
// #include "libCloudundancy/Components/Process/Linux/LinuxProcessRunner.h"

// TESTS(LinuxProcessRunnerTests)
// AFACT(Run_DoesNothing_ReturnsDefaultProcessResult)
// AFACT(FailFastRun_DoesNothing_ReturnsDefaultProcessResult)
// EVIDENCE

// LinuxProcessRunner _linuxProcessRunner;

// TEST(Run_DoesNothing_ReturnsDefaultProcessResult)
// {
//    const string processName = ZenUnit::Random<string>();
//    const string arguments = ZenUnit::Random<string>();
//    //
//    const ProcessResult processResult = _linuxProcessRunner.Run(processName, arguments);
//    //
//    ARE_EQUAL(ProcessResult(), processResult);
// }

// TEST(FailFastRun_DoesNothing_ReturnsDefaultProcessResult)
// {
//    const string processName = ZenUnit::Random<string>();
//    const string arguments = ZenUnit::Random<string>();
//    //
//    const ProcessResult processResult = _linuxProcessRunner.FailFastRun(processName, arguments);
//    //
//    ARE_EQUAL(ProcessResult(), processResult);
// }

// RUN_TESTS(LinuxProcessRunnerTests)

#else
namespace { char symbolToQuietMSBuildLinkerWarning4221ForDoesNotDefineAPublicSymbol; }
#endif
