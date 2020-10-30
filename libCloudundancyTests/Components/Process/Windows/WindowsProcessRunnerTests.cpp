#include "pch.h"
#ifdef _WIN32
#include "libCloudundancyTests/Components/Console/MetalMock/ConsoleMock.h"
#include "libCloudundancy/Components/Process/Windows/WindowsProcessRunner.h"
#include "libCloudundancyTests/Components/Process/ZenUnit/ProcessResultEqualizerAndRandom.h"
#include "libCloudundancyTests/Components/FunctionCallers/Member/MetalMock/NonVoidTwoArgMemberFunctionCallerMock.h"

TESTS(WindowsProcessRunnerTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(FailFastRun_RunReturnsExitCode0_ReturnsProcessResult)
FACTS(FailFastRun_RunReturnsNon0ExitCode_WritesErrorMessage_CallsExitWithProcessExitCode)
EVIDENCE

WindowsProcessRunner _windowsProcessRunner;
// Function Callers
METALMOCK_VOID1_FREE(exit, int)
using _caller_Run_MockType = NonVoidTwoArgMemberFunctionCallerMock<
   ProcessResult, WindowsProcessRunner, string_view, string_view>;
_caller_Run_MockType* _caller_RunMock = nullptr;
// Constant Components
ConsoleMock* _consoleMock = nullptr;

STARTUP
{
   _windowsProcessRunner._caller_Run.reset(_caller_RunMock = new _caller_Run_MockType);
   _windowsProcessRunner._console.reset(_consoleMock = new ConsoleMock);
   _windowsProcessRunner._call_exit = BIND_1ARG_METALMOCK_OBJECT(exitMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   WindowsProcessRunner windowsProcessRunner;
   DELETE_TO_ASSERT_NEWED(windowsProcessRunner._caller_Run);
   DELETE_TO_ASSERT_NEWED(windowsProcessRunner._console);
}

TEST(FailFastRun_RunReturnsExitCode0_ReturnsProcessResult)
{
   _consoleMock->WriteLineMock.Expect();

   ProcessResult runReturnValue = ZenUnit::Random<ProcessResult>();
   runReturnValue.exitCode = 0;
   _caller_RunMock->ConstCallMock.Return(runReturnValue);

   const string processName = ZenUnit::Random<string>();
   const string arguments = ZenUnit::Random<string>();
   //
   const ProcessResult processResult = _windowsProcessRunner.FailFastRun(processName, arguments);
   //
   METALMOCK(_consoleMock->WriteLineMock.CalledAsFollows(
   {
      string_view(String::Concat("[Cloudundancy] Running: \"", processName, ' ', arguments, "\"")),
      string_view(runReturnValue.standardOutputAndError)
   }));
   METALMOCK(_caller_RunMock->ConstCallMock.CalledOnceWith(&_windowsProcessRunner, &WindowsProcessRunner::Run, processName, arguments));
   ARE_EQUAL(runReturnValue, processResult);
}

TEST1X1(FailFastRun_RunReturnsNon0ExitCode_WritesErrorMessage_CallsExitWithProcessExitCode,
   int exitCode,
   -1,
   1,
   999)
{
   ProcessResult runReturnValue = ZenUnit::Random<ProcessResult>();
   runReturnValue.exitCode = exitCode;
   _caller_RunMock->ConstCallMock.Return(runReturnValue);

   _consoleMock->WriteLineMock.Expect();

   exitMock.Expect();

   const string processName = ZenUnit::Random<string>();
   const string arguments = ZenUnit::Random<string>();
   //
   const ProcessResult processResult = _windowsProcessRunner.FailFastRun(processName, arguments);
   //
   METALMOCK(_caller_RunMock->ConstCallMock.CalledOnceWith(&_windowsProcessRunner, &WindowsProcessRunner::Run, processName, arguments));
   const string expectedProcessFailedErrorMessage = String::Concat(
      "Process \"", processName, " ", arguments, "\" failed to return exit code 0 by returning exit code ", processResult.exitCode, '.');
   METALMOCK(_consoleMock->WriteLineMock.CalledAsFollows(
   {
      string_view(String::Concat("[Cloudundancy] Running: \"", processName, ' ', arguments, "\"")),
      string_view(runReturnValue.standardOutputAndError),
      string_view(expectedProcessFailedErrorMessage)
   }));
   METALMOCK(exitMock.CalledOnceWith(exitCode));
   ARE_EQUAL(runReturnValue, processResult);
}

RUN_TESTS(WindowsProcessRunnerTests)
#endif
