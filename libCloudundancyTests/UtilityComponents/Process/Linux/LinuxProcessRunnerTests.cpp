#include "pch.h"
#if defined __linux__ || defined __APPLE__

#include "libCloudundancy/UtilityComponents/Process/Linux/LinuxProcessRunner.h"
#include "libCloudundancyTests/Components/ErrorHandling/MetalMock/ErrorCodeTranslatorMock.h"

TESTS(LinuxProcessRunnerTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(Run_RunsProcessWithArguments_ReturnsProcessResult__whoamiTestCase)
AFACT(FailFastRun_RunReturnsExitCode0_ReturnsProcessResult)
AFACT(FailFastRun_RunReturnsNon0ExitCode_WritesErrorMessageAndExitsProgramWithProcessExitCode)
// Private Functions
AFACT(ThrowRuntimeErrorIfPosixSpawnpReturnValueNot0_PosixSpawnpReturnValueIs0_DoesNothing)
AFACT(ThrowRuntimeErrorIfPosixSpawnpReturnValueNot0_PosixSpawnpReturnValueIsNot0_ThrowsRuntimeError)
AFACT(ThrowRuntimeErrorIfWaitPidReturnValueDoesNotEqualPid_WaitPidReturnValueEqualsPid_DoesNothing)
AFACT(ThrowRuntimeErrorIfWaitPidReturnValueDoesNotEqualPid_WaitPidReturnValueDoesNotEqualPid_ThrowsRuntimeError)
EVIDENCE

LinuxProcessRunner _linuxProcessRunner;
// Function Callers
using _caller_Run_MockType = NonVoidTwoArgMemberFunctionCallerMock<ProcessResult, LinuxProcessRunner, string_view, string_view>;
_caller_Run_MockType* _caller_RunMock = nullptr;
// Constant Components
ConsoleMock* _consoleMock = nullptr;
ErrorCodeTranslatorMock* _errorCodeTranslatorMock = nullptr;

STARTUP
{
   // Function Callers
   _linuxProcessRunner._caller_Run.reset(_caller_RunMock = new _caller_Run_MockType);
   // Constant Components
   _linuxProcessRunner._console.reset(_consoleMock = new ConsoleMock);
   _linuxProcessRunner._errorCodeTranslator.reset(_errorCodeTranslatorMock = new ErrorCodeTranslatorMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   LinuxProcessRunner linuxProcessRunner;
   // Function Callers
   DELETE_TO_ASSERT_NEWED(linuxProcessRunner._caller_Run);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(linuxProcessRunner._console);
   DELETE_TO_ASSERT_NEWED(linuxProcessRunner._errorCodeTranslator);
}

TEST(Run_RunsProcessWithArguments_ReturnsProcessResult__whoamiTestCase)
{
   const ProcessResult processResult = _linuxProcessRunner.Run("whoami", "");
   //
   ARE_EQUAL("whoami", processResult.processName);
   ARE_EQUAL("", processResult.arguments);
   ARE_EQUAL(0, processResult.exitCode);
}

TEST(FailFastRun_RunReturnsExitCode0_ReturnsProcessResult)
{
   _consoleMock->WriteLineColorMock.Expect();

   ProcessResult runReturnValue = ZenUnit::Random<ProcessResult>();
   runReturnValue.exitCode = 0;
   _caller_RunMock->CallConstMemberFunctionMock.Return(runReturnValue);

   const string processName = ZenUnit::Random<string>();
   const string arguments = ZenUnit::Random<string>();
   //
   const ProcessResult processResult = _linuxProcessRunner.FailFastRun(processName, arguments, ZenUnit::Random<bool>());
   //
   const string expectedRunningProgramMessage = String::ConcatStrings("[Cloudundancy] Running program: ", processName, " ", arguments);
   METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedRunningProgramMessage, Color::Yellow));
   METALMOCK(_caller_RunMock->CallConstMemberFunctionMock.CalledOnceWith(
      &LinuxProcessRunner::Run, &_linuxProcessRunner, processName, arguments));
   ARE_EQUAL(runReturnValue, processResult);
}

TEST(FailFastRun_RunReturnsNon0ExitCode_WritesErrorMessageAndExitsProgramWithProcessExitCode)
{
   ProcessResult runReturnValue = ZenUnit::Random<ProcessResult>();
   runReturnValue.exitCode = ZenUnit::RandomNon0<int>();
   _caller_RunMock->CallConstMemberFunctionMock.Return(runReturnValue);

   _consoleMock->WriteLineColorMock.Expect();
   _consoleMock->WriteLineAndExitMock.Expect();

   const string processName = ZenUnit::Random<string>();
   const string arguments = ZenUnit::Random<string>();
   //
   const ProcessResult processResult = _linuxProcessRunner.FailFastRun(processName, arguments, ZenUnit::Random<bool>());
   //
   METALMOCK(_caller_RunMock->CallConstMemberFunctionMock.CalledOnceWith(
      &LinuxProcessRunner::Run, &_linuxProcessRunner, processName, arguments));
   const string expectedRunningProgramMessage = String::ConcatStrings("[Cloudundancy] Running program: ", processName, " ", arguments);
   METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedRunningProgramMessage, Color::Yellow));
   const string expectedProcessFailedErrorMessage = String::ConcatValues(
      "Process \"", processName, " ", arguments, "\" failed with exit code ", processResult.exitCode, '.');
   METALMOCK(_consoleMock->WriteLineAndExitMock.CalledOnceWith(expectedProcessFailedErrorMessage, runReturnValue.exitCode));
   ARE_EQUAL(runReturnValue, processResult);
}

// Private Functions

TEST(ThrowRuntimeErrorIfPosixSpawnpReturnValueNot0_PosixSpawnpReturnValueIs0_DoesNothing)
{
   _linuxProcessRunner.ThrowRuntimeErrorIfPosixSpawnpReturnValueNot0(0);
}

TEST(ThrowRuntimeErrorIfPosixSpawnpReturnValueNot0_PosixSpawnpReturnValueIsNot0_ThrowsRuntimeError)
{

}

TEST(ThrowRuntimeErrorIfWaitPidReturnValueDoesNotEqualPid_WaitPidReturnValueEqualsPid_DoesNothing)
{
   const pid_t waitpidReturnValue = ZenUnit::Random<pid_t>();
   const pid_t pid = waitpidReturnValue;
   //
   _linuxProcessRunner.ThrowRuntimeErrorIfWaitPidReturnValueDoesNotEqualPid(waitpidReturnValue, pid);
}

TEST(ThrowRuntimeErrorIfWaitPidReturnValueDoesNotEqualPid_WaitPidReturnValueDoesNotEqualPid_ThrowsRuntimeError)
{

}

RUN_TESTS(LinuxProcessRunnerTests)

#endif
