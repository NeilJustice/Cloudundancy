#include "pch.h"
#ifdef _WIN32
#include "libCloudundancyTests/UtilityComponents/Console/MetalMock/ConsoleMock.h"
#include "libCloudundancy/UtilityComponents/Process/Windows/WindowsProcessRunner.h"
#include "libCloudundancyTests/UtilityComponents/FunctionCallers/MemberFunctions/MetalMock/NonVoidTwoArgMemberFunctionCallerMock.h"

TESTS(WindowsProcessRunnerTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(FailFastRun_RunReturnsExitCode0_ReturnsProcessResult)
AFACT(FailFastRun_RunReturnsNon0ExitCode_WritesErrorMessage_CallsExitWithProcessExitCode)
EVIDENCE

WindowsProcessRunner _windowsProcessRunner;
// Function Callers
using _caller_Run_MockType = NonVoidTwoArgMemberFunctionCallerMock<
   ProcessResult, WindowsProcessRunner, string_view, string_view>;
_caller_Run_MockType* _caller_RunMock = nullptr;
// Constant Components
ConsoleMock* _consoleMock = nullptr;

STARTUP
{
   _windowsProcessRunner._caller_Run.reset(_caller_RunMock = new _caller_Run_MockType);
   _windowsProcessRunner._console.reset(_consoleMock = new ConsoleMock);
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
   _consoleMock->WriteLineIfMock.Expect();
   _consoleMock->WriteLineIfMock.Expect();

   ProcessResult runReturnValue = ZenUnit::Random<ProcessResult>();
   runReturnValue.exitCode = 0;
   _caller_RunMock->ConstCallMock.Return(runReturnValue);

   const string processName = ZenUnit::Random<string>();
   const string arguments = ZenUnit::Random<string>();
   const bool doPrintStandardOutput = ZenUnit::Random<bool>();
   //
   const ProcessResult processResult = _windowsProcessRunner.FailFastRun(processName, arguments, doPrintStandardOutput);
   //
   const string expectedRunningProgramMessage = String::Concat("[Cloudundancy] Running program: ", processName, ' ', arguments);
   METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(expectedRunningProgramMessage));
   METALMOCK(_consoleMock->WriteLineIfMock.CalledOnceWith(doPrintStandardOutput, processResult.standardOutputAndError));
   METALMOCK(_caller_RunMock->ConstCallMock.CalledOnceWith(
      &WindowsProcessRunner::Run, &_windowsProcessRunner, processName, arguments));
   ARE_EQUAL(runReturnValue, processResult);
}

TEST(FailFastRun_RunReturnsNon0ExitCode_WritesErrorMessage_CallsExitWithProcessExitCode)
{
   ProcessResult runReturnValue = ZenUnit::Random<ProcessResult>();
   runReturnValue.exitCode = ZenUnit::RandomNon0<int>();
   _caller_RunMock->ConstCallMock.Return(runReturnValue);

   _consoleMock->WriteLineMock.Expect();
   _consoleMock->WriteLineIfMock.Expect();
   _consoleMock->WriteLineAndExitMock.Expect();

   const string processName = ZenUnit::Random<string>();
   const string arguments = ZenUnit::Random<string>();
   const bool doPrintStandardOutput = ZenUnit::Random<bool>();
   //
   const ProcessResult processResult = _windowsProcessRunner.FailFastRun(processName, arguments, doPrintStandardOutput);
   //
   METALMOCK(_caller_RunMock->ConstCallMock.CalledOnceWith(
      &WindowsProcessRunner::Run, &_windowsProcessRunner, processName, arguments));
   const string expectedRunningProgramMessage = String::Concat("[Cloudundancy] Running program: ", processName, ' ', arguments);
   METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(expectedRunningProgramMessage));
   METALMOCK(_consoleMock->WriteLineIfMock.CalledOnceWith(doPrintStandardOutput, processResult.standardOutputAndError));
   const string expectedProcessFailedErrorMessage = String::Concat(
      "Process \"", processName, " ", arguments, "\" failed to return exit code 0 by returning exit code ", processResult.exitCode, '.');
   METALMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith(expectedProcessFailedErrorMessage, runReturnValue.exitCode));
   ARE_EQUAL(runReturnValue, processResult);
}

RUN_TESTS(WindowsProcessRunnerTests)
#endif
