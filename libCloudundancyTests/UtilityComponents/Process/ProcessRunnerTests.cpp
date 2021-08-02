#include "pch.h"
#include "libCloudundancy/UtilityComponents/Process/ProcessRunner.h"
#if defined __linux__ || defined __APPLE__
#include "libCloudundancyTests/UtilityComponents/Process/Linux/MetalMock/LinuxProcessRunnerMock.h"
#elif _WIN32
#include "libCloudundancyTests/UtilityComponents/Process/Windows/MetalMock/WindowsProcessRunnerMock.h"
#endif

TESTS(ProcessRunnerTests)
AFACT(DefaultConstructor_NewsOSSpecificProcessRunner)
AFACT(Run_CallsProcessRunnerRun)
AFACT(FailFastRun_CallsProcessRunnerFailFastRun)
EVIDENCE

Utils::ProcessRunner _processRunner;
// Constant Components
#if defined __linux__ || defined __APPLE__
Utils::LinuxProcessRunnerMock* _osSpecificProcessRunnerMock = nullptr;
#elif _WIN32
Utils::WindowsProcessRunnerMock* _osSpecificProcessRunnerMock = nullptr;
#endif

STARTUP
{
   // Constant Components
#if defined __linux__ || defined __APPLE__
   _processRunner._osSpecificProcessRunner.reset(_osSpecificProcessRunnerMock = new Utils::LinuxProcessRunnerMock);
#elif _WIN32
   _processRunner._osSpecificProcessRunner.reset(_osSpecificProcessRunnerMock = new Utils::WindowsProcessRunnerMock);
#endif
}

TEST(DefaultConstructor_NewsOSSpecificProcessRunner)
{
   Utils::ProcessRunner processRunner;
   // Constant Components
   DELETE_TO_ASSERT_NEWED(processRunner._osSpecificProcessRunner);
}

TEST(Run_CallsProcessRunnerRun)
{
   const Utils::ProcessResult runReturnValue = _osSpecificProcessRunnerMock->RunMock.ReturnRandom();
   const string processName = ZenUnit::Random<string>();
   const string arguments = ZenUnit::Random<string>();
   //
   const Utils::ProcessResult processResult = _processRunner.Run(processName, arguments);
   //
   METALMOCK(_osSpecificProcessRunnerMock->RunMock.CalledOnceWith(processName, arguments));
   ARE_EQUAL(runReturnValue, processResult);
}

TEST(FailFastRun_CallsProcessRunnerFailFastRun)
{
   const Utils::ProcessResult failFastReturnValue = _osSpecificProcessRunnerMock->FailFastRunMock.ReturnRandom();
   const string processName = ZenUnit::Random<string>();
   const string arguments = ZenUnit::Random<string>();
   const bool doPrintStandardOutput = ZenUnit::Random<bool>();
   //
   const Utils::ProcessResult processResult = _processRunner.FailFastRun(processName, arguments, doPrintStandardOutput);
   //
   METALMOCK(_osSpecificProcessRunnerMock->FailFastRunMock.CalledOnceWith(processName, arguments, doPrintStandardOutput));
   ARE_EQUAL(failFastReturnValue, processResult);
}

RUN_TESTS(ProcessRunnerTests)
