#include "pch.h"
#ifdef _WIN32
#include "libCloudundancyTests/UtilityComponents/Console/MetalMock/ConsoleMock.h"
#include "libCloudundancy/UtilityComponents/Process/Windows/WindowsProcessRunner.h"
#include "libCloudundancyTests/UtilityComponents/FunctionCallers/Member/MetalMock/NonVoidTwoArgMemberFunctionCallerMock.h"

TESTS(WindowsProcessRunnerTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(FailFastRun_RunReturnsExitCode0_ReturnsProcessResult)
AFACT(FailFastRun_RunReturnsNon0ExitCode_WritesErrorMessage_CallsExitWithProcessExitCode)
EVIDENCE

Utils::WindowsProcessRunner _windowsProcessRunner;
// Function Callers
using _caller_Run_MockType = Utils::NonVoidTwoArgMemberFunctionCallerMock<Utils::ProcessResult, Utils::WindowsProcessRunner, string_view, string_view>;
_caller_Run_MockType* _caller_RunMock = nullptr;
// Constant Components
Utils::ConsoleMock* _consoleMock = nullptr;

STARTUP
{
   // Function Callers
   _windowsProcessRunner._caller_Run.reset(_caller_RunMock = new _caller_Run_MockType);
   // Constant Components
   _windowsProcessRunner._console.reset(_consoleMock = new Utils::ConsoleMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   Utils::WindowsProcessRunner windowsProcessRunner;
   // Function Callers
   DELETE_TO_ASSERT_NEWED(windowsProcessRunner._caller_Run);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(windowsProcessRunner._console);
}

TEST(FailFastRun_RunReturnsExitCode0_ReturnsProcessResult)
{
   _consoleMock->WriteLineColorMock.Expect();
   _consoleMock->WriteLineIfMock.Expect();

   Utils::ProcessResult runReturnValue = ZenUnit::Random<Utils::ProcessResult>();
   runReturnValue.exitCode = 0;
   _caller_RunMock->CallConstMemberFunctionMock.Return(runReturnValue);

   const string processName = ZenUnit::Random<string>();
   const string arguments = ZenUnit::Random<string>();
   const bool doPrintStandardOutput = ZenUnit::Random<bool>();
   //
   const Utils::ProcessResult processResult = _windowsProcessRunner.FailFastRun(processName, arguments, doPrintStandardOutput);
   //
   const string expectedRunningProgramMessage = Utils::String::ConcatStrings(
      "[Cloudundancy] Running program: ", processName, " ", arguments);
   METALMOCKTHEN(_consoleMock->WriteLineColorMock.CalledOnceWith(
      expectedRunningProgramMessage, Color::Yellow)).Then(
   METALMOCKTHEN(_caller_RunMock->CallConstMemberFunctionMock.CalledOnceWith(
      &_windowsProcessRunner, &Utils::WindowsProcessRunner::Run, processName, arguments))).Then(
   METALMOCKTHEN(_consoleMock->WriteLineIfMock.CalledOnceWith(
      doPrintStandardOutput, processResult.standardOutputAndError)));
   ARE_EQUAL(runReturnValue, processResult);
}

TEST(FailFastRun_RunReturnsNon0ExitCode_WritesErrorMessage_CallsExitWithProcessExitCode)
{
   Utils::ProcessResult runReturnValue = ZenUnit::Random<Utils::ProcessResult>();
   runReturnValue.exitCode = ZenUnit::RandomNon0<int>();
   _caller_RunMock->CallConstMemberFunctionMock.Return(runReturnValue);

   _consoleMock->WriteLineColorMock.Expect();
   _consoleMock->WriteLineIfMock.Expect();
   _consoleMock->WriteLineAndExitMock.Expect();

   const string processName = ZenUnit::Random<string>();
   const string arguments = ZenUnit::Random<string>();
   const bool doPrintStandardOutput = ZenUnit::Random<bool>();
   //
   const Utils::ProcessResult processResult = _windowsProcessRunner.FailFastRun(processName, arguments, doPrintStandardOutput);
   //
   const string expectedRunningProgramMessage = Utils::String::ConcatStrings("[Cloudundancy] Running program: ", processName, " ", arguments);
   const string expectedProcessFailedErrorMessage = Utils::String::ConcatValues(
      "Process \"", processName, " ", arguments, "\" failed with exit code ", processResult.exitCode, '.');
   METALMOCKTHEN(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedRunningProgramMessage, Color::Yellow)).Then(
   METALMOCKTHEN(_caller_RunMock->CallConstMemberFunctionMock.CalledOnceWith(
      &_windowsProcessRunner, &Utils::WindowsProcessRunner::Run, processName, arguments))).Then(
   METALMOCKTHEN(_consoleMock->WriteLineIfMock.CalledOnceWith(doPrintStandardOutput, processResult.standardOutputAndError))).Then(
   METALMOCKTHEN(_consoleMock->WriteLineAndExitMock.CalledOnceWith(expectedProcessFailedErrorMessage, runReturnValue.exitCode)));
   ARE_EQUAL(runReturnValue, processResult);
}

RUN_TESTS(WindowsProcessRunnerTests)
#endif
