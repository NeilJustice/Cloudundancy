#include "pch.h"
#ifdef _WIN32
#include "libCloudundancy/Components/Console/Console.h"
#include "libCloudundancy/Components/FunctionCallers/Member/NonVoidTwoArgMemberFunctionCaller.h"
#include "libCloudundancy/Components/Process/Windows/WindowsProcessRunner.h"

WindowsProcessRunner::WindowsProcessRunner()
   // Function Callers
   : _caller_Run(make_unique<_caller_Run_Type>())
   // Constant Components
   , _console(make_unique<Console>())
{
}

WindowsProcessRunner::~WindowsProcessRunner()
{
}

ProcessResult WindowsProcessRunner::Run(string_view processName, string_view arguments) const
{
   SECURITY_ATTRIBUTES securityAttrs{};
   securityAttrs.nLength = sizeof(SECURITY_ATTRIBUTES);
   securityAttrs.bInheritHandle = TRUE;
   securityAttrs.lpSecurityDescriptor = NULL;
   HANDLE stdOutReadHandle{};
   HANDLE stdOutWriteHandle{};
   const BOOL createPipeSucceeded = CreatePipe(&stdOutReadHandle, &stdOutWriteHandle, &securityAttrs, 0);
   if (!createPipeSucceeded)
   {
      _console->WriteLineAndExit(
         "[Cloudundancy] Error: WindowsProcessRunner::Run(processName, arguments) failed because CreatePipe(&stdOutReadHandle, &stdOutWriteHandle, &securityAttrs, 0) returned FALSE", 1);
   }
   const size_t SpaceSize = 1;
   const size_t NullSize = 1;
   const size_t argumentsSize = arguments.empty() ? NullSize : SpaceSize + arguments.size() + NullSize;
   const size_t commandLineSize = processName.size() + argumentsSize;
   const unique_ptr<CHAR[]> commandLineChars(new CHAR[commandLineSize]);
   memcpy(commandLineChars.get(), processName.data(), processName.size());
   if (!arguments.empty())
   {
      commandLineChars[processName.size()] = ' ';
      memcpy(commandLineChars.get() + processName.size() + SpaceSize, arguments.data(), arguments.size());
   }
   commandLineChars[commandLineSize - 1] = '\0';
   STARTUPINFOA startupInfo{};
   startupInfo.hStdOutput = stdOutWriteHandle;
   startupInfo.hStdError = stdOutWriteHandle;
   startupInfo.dwFlags = STARTF_USESTDHANDLES;
   PROCESS_INFORMATION processInformation{};
   const auto beginTime = chrono::high_resolution_clock::now();
   const BOOL createProcessSucceeded = CreateProcessA(nullptr, commandLineChars.get(), nullptr, nullptr, TRUE, CREATE_NO_WINDOW, nullptr, nullptr, &startupInfo, &processInformation);
   if (!createProcessSucceeded)
   {
      const DWORD lastError = GetLastError();
      _console->WriteLineAndExit(
         "[Cloudundancy] Error: WindowsProcessRunner::Run(processName, arguments) failed because CreateProcessA(nullptr, commandLineChars.get(), nullptr, nullptr, TRUE, CREATE_NO_WINDOW, nullptr, nullptr, &startupInfo, &processInformation) returned FALSE. GetLastError()=" + to_string(lastError), 1);
   }
   const DWORD processWaitResult = WaitForSingleObject(processInformation.hProcess, INFINITE);
   auto endTime = chrono::high_resolution_clock::now();
   if (processWaitResult != 0)
   {
      const DWORD lastError = GetLastError();
      _console->WriteLineAndExit(
         "[Cloudundancy] Error: WindowsProcessRunner::Run(processName, arguments) failed because WaitForSingleObject(processInformation.hProcess, INFINITE) failed. GetLastError()=" + to_string(lastError), 1);
   }
   DWORD threadExitCode = 0;
   const BOOL didGetThreadExitCode = GetExitCodeThread(processInformation.hThread, &threadExitCode);
   release_assert(didGetThreadExitCode == TRUE);

   DWORD processExitCode = 0;
   const BOOL didGetProcessExitCode = GetExitCodeProcess(processInformation.hProcess, &processExitCode);
   release_assert(didGetProcessExitCode == TRUE);

   const BOOL didCloseProcessHandle = CloseHandle(processInformation.hProcess);
   release_assert(didCloseProcessHandle == TRUE);

   const BOOL didCloseThreadHandle = CloseHandle(processInformation.hThread);
   release_assert(didCloseThreadHandle == TRUE);

   const string standardOutputAndError = ReadPipe(stdOutReadHandle);

   const BOOL didCloseStdOutReadHandle = CloseHandle(stdOutReadHandle);
   release_assert(didCloseStdOutReadHandle == TRUE);

   const BOOL didCloseStdOutWriteHandle = CloseHandle(stdOutWriteHandle);
   release_assert(didCloseStdOutWriteHandle == TRUE);

   const unsigned elapsedMilliseconds = static_cast<unsigned>(
      chrono::duration_cast<chrono::milliseconds>(endTime - beginTime).count());
   const ProcessResult processResult(
      processName.data(),
      arguments.data(),
      static_cast<int>(processExitCode),
      standardOutputAndError,
      elapsedMilliseconds);
   return processResult;
}

ProcessResult WindowsProcessRunner::FailFastRun(string_view processName, string_view arguments) const
{
   const string runningMessage = String::Concat("[Cloudundancy] Running: \"", processName, ' ', arguments, "\"");
   _console->WriteLine(runningMessage);
   const ProcessResult processResult = _caller_Run->ConstCall(this, &WindowsProcessRunner::Run, processName, arguments);
   _console->WriteLine(processResult.standardOutputAndError);
   if (processResult.exitCode != 0)
   {
      const string processFailedErrorMessage = String::Concat(
         "Process \"", processName, ' ', arguments, "\" failed to return exit code 0 by returning exit code ", processResult.exitCode, '.');
      _console->WriteLineAndExit(processFailedErrorMessage, processResult.exitCode);
   }
   return processResult;
}

string WindowsProcessRunner::ReadPipe(HANDLE pipeHandle)
{
   DWORD numberOfCharsRead = 0;
   CHAR standardOutputBuffer[4096];
   const BOOL didReadStandardOutput = ReadFile(
      pipeHandle, standardOutputBuffer, sizeof(standardOutputBuffer), &numberOfCharsRead, nullptr);
   release_assert(didReadStandardOutput == TRUE);
   const string standardOutputAndError(standardOutputBuffer, numberOfCharsRead);
   return standardOutputAndError;
}

#endif
