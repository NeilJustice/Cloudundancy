#include "pch.h"
#ifdef __linux__

#include "libCloudundancy/UtilityComponents/Process/Linux/LinuxProcessRunner.h"

TESTS(LinuxProcessRunnerTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(FailFastRun_RunReturnsExitCode0_ReturnsProcessResult)
AFACT(FailFastRun_RunReturnsNon0ExitCode_WritesErrorMessage_CallsExitWithProcessExitCode)
EVIDENCE

LinuxProcessRunner _linuxProcessRunner;
// Function Callers
using _caller_Run_MockType = NonVoidTwoArgMemberFunctionCallerMock<ProcessResult, LinuxProcessRunner, string_view, string_view>;
_caller_Run_MockType* _caller_RunMock = nullptr;
// Constant Components
ConsoleMock* _consoleMock = nullptr;

STARTUP
{
   _linuxProcessRunner._caller_Run.reset(_caller_RunMock = new _caller_Run_MockType);
   _linuxProcessRunner._console.reset(_consoleMock = new ConsoleMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   LinuxProcessRunner linuxProcessRunner;
   DELETE_TO_ASSERT_NEWED(linuxProcessRunner._caller_Run);
   DELETE_TO_ASSERT_NEWED(linuxProcessRunner._console);
}

TEST(FailFastRun_RunReturnsExitCode0_ReturnsProcessResult)
{
   _consoleMock->WriteLineColorMock.Expect();
   _consoleMock->WriteLineIfMock.Expect();

   ProcessResult runReturnValue = ZenUnit::Random<ProcessResult>();
   runReturnValue.exitCode = 0;
   _caller_RunMock->CallConstMemberFunctionMock.Return(runReturnValue);

   const string processName = ZenUnit::Random<string>();
   const string arguments = ZenUnit::Random<string>();
   const bool doPrintStandardOutput = ZenUnit::Random<bool>();
   //
   const ProcessResult processResult = _linuxProcessRunner.FailFastRun(processName, arguments, doPrintStandardOutput);
   //
   const string expectedRunningProgramMessage = String::Concat("[Cloudundancy] Running program: ", processName, ' ', arguments);
   METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedRunningProgramMessage, Color::Yellow));
   METALMOCK(_consoleMock->WriteLineIfMock.CalledOnceWith(doPrintStandardOutput, processResult.standardOutputAndError));
   METALMOCK(_caller_RunMock->CallConstMemberFunctionMock.CalledOnceWith(
      &LinuxProcessRunner::Run, &_linuxProcessRunner, processName, arguments));
   ARE_EQUAL(runReturnValue, processResult);
}

TEST(FailFastRun_RunReturnsNon0ExitCode_WritesErrorMessage_CallsExitWithProcessExitCode)
{
   ProcessResult runReturnValue = ZenUnit::Random<ProcessResult>();
   runReturnValue.exitCode = ZenUnit::RandomNon0<int>();
   _caller_RunMock->CallConstMemberFunctionMock.Return(runReturnValue);

   _consoleMock->WriteLineColorMock.Expect();
   _consoleMock->WriteLineIfMock.Expect();
   _consoleMock->WriteLineAndExitMock.Expect();

   const string processName = ZenUnit::Random<string>();
   const string arguments = ZenUnit::Random<string>();
   const bool doPrintStandardOutput = ZenUnit::Random<bool>();
   //
   const ProcessResult processResult = _linuxProcessRunner.FailFastRun(processName, arguments, doPrintStandardOutput);
   //
   METALMOCK(_caller_RunMock->CallConstMemberFunctionMock.CalledOnceWith(
      &LinuxProcessRunner::Run, &_linuxProcessRunner, processName, arguments));
   const string expectedRunningProgramMessage = String::Concat("[Cloudundancy] Running program: ", processName, ' ', arguments);
   METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedRunningProgramMessage, Color::Yellow));
   METALMOCK(_consoleMock->WriteLineIfMock.CalledOnceWith(doPrintStandardOutput, processResult.standardOutputAndError));
   const string expectedProcessFailedErrorMessage = String::Concat(
      "Process \"", processName, " ", arguments, "\" failed to return exit code 0 by returning exit code ", processResult.exitCode, '.');
   METALMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith(expectedProcessFailedErrorMessage, runReturnValue.exitCode));
   ARE_EQUAL(runReturnValue, processResult);
}

RUN_TESTS(LinuxProcessRunnerTests)

#endif
