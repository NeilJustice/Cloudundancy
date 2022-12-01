#include "pch.h"
#ifdef _WIN32
#include "libCloudundancy/UtilityComponents/Process/Windows/WindowsProcessRunner.h"

namespace Utils
{
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
         const string exitMessage = Utils::String::ConcatStrings(
            "[Cloudundancy] Error: WindowsProcessRunner::Run(processName, arguments) failed because CreatePipe(&stdOutReadHandle, &stdOutWriteHandle, &securityAttrs, 0) returned FALSE\n",
            "[Cloudundancy] ExitCode: 1");
         _console->WriteLineAndExit(exitMessage, 1);
      }
      constexpr size_t SpaceSize = 1;
      constexpr size_t NullSize = 1;
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
      const BOOL createProcessSucceeded = CreateProcessA(
         nullptr, commandLineChars.get(), nullptr, nullptr, TRUE, CREATE_NO_WINDOW, nullptr, nullptr, &startupInfo, &processInformation);
      if (!createProcessSucceeded)
      {
         const DWORD lastError = GetLastError();
         const string exitMessage = Utils::String::ConcatValues(
            "[Cloudundancy] Error: WindowsProcessRunner::Run(processName, arguments) failed because CreateProcessA(nullptr, commandLineChars.get(), nullptr, nullptr, TRUE, CREATE_NO_WINDOW, nullptr, nullptr, &startupInfo, &processInformation) returned FALSE. GetLastError()=", lastError, '\n',
            "[Cloudundancy] ExitCode: 1");
         _console->WriteLineAndExit(exitMessage, 1);
      }
      const DWORD processWaitResult = WaitForSingleObject(processInformation.hProcess, INFINITE);
      auto endTime = chrono::high_resolution_clock::now();
      if (processWaitResult != 0)
      {
         const DWORD lastError = GetLastError();
         const string exitMessage = Utils::String::ConcatValues(
            "[Cloudundancy] Error: WindowsProcessRunner::Run(processName, arguments) failed because WaitForSingleObject(processInformation.hProcess, INFINITE) failed. GetLastError()=", lastError, '\n',
            "[Cloudundancy] ExitCode: 1");
         _console->WriteLineAndExit(exitMessage, 1);
      }
      DWORD threadExitCode = 0;
      const BOOL didGetThreadExitCode = GetExitCodeThread(processInformation.hThread, &threadExitCode);
      release_assert(didGetThreadExitCode == TRUE);

      DWORD processExitCode = 0;
      const BOOL didGetProcessExitCode = GetExitCodeProcess(processInformation.hProcess, &processExitCode);
      release_assert(didGetProcessExitCode == TRUE);

      const BOOL didCloseThreadHandle = CloseHandle(processInformation.hThread);
      release_assert(didCloseThreadHandle == TRUE);

      const BOOL didCloseProcessHandle = CloseHandle(processInformation.hProcess);
      release_assert(didCloseProcessHandle == TRUE);

      const string standardOutputAndError = ReadPipe(stdOutReadHandle);

      const BOOL didCloseStdOutReadHandle = CloseHandle(stdOutReadHandle);
      release_assert(didCloseStdOutReadHandle == TRUE);

      const BOOL didCloseStdOutWriteHandle = CloseHandle(stdOutWriteHandle);
      release_assert(didCloseStdOutWriteHandle == TRUE);

      const unsigned elapsedMilliseconds = static_cast<unsigned>(
         chrono::duration_cast<chrono::milliseconds>(endTime - beginTime).count());
      ProcessResult processResult(
         processName.data(), arguments.data(), static_cast<int>(processExitCode), standardOutputAndError, elapsedMilliseconds);
      return processResult;
   }

   ProcessResult WindowsProcessRunner::FailFastRun(string_view processName, string_view arguments, bool doPrintStandardOutput) const
   {
      const string runningMessage = Utils::String::ConcatStrings("[Cloudundancy] Running program: ", processName, " ", arguments);
      _console->WriteLineColor(runningMessage, Color::Yellow);
      const ProcessResult processResult = _caller_Run->CallConstMemberFunction(
         this, &WindowsProcessRunner::Run, processName, arguments);
      _console->WriteLineIf(doPrintStandardOutput, processResult.standardOutputAndError);
      if (processResult.exitCode != 0)
      {
         const string processFailedErrorMessage = Utils::String::ConcatValues(
            "Process \"", processName, ' ', arguments, "\" failed with exit code ", processResult.exitCode, '.');
         _console->WriteLineAndExit(processFailedErrorMessage, processResult.exitCode);
      }
      return processResult;
   }

   string WindowsProcessRunner::ReadPipe(HANDLE pipeHandle)
   {
      DWORD numberOfCharsRead = 0;
      CHAR standardOutputBuffer[4096]{};
      const BOOL didReadStandardOutput = ReadFile(
         pipeHandle, standardOutputBuffer, sizeof(standardOutputBuffer), &numberOfCharsRead, nullptr);
      release_assert(didReadStandardOutput == TRUE);
      string standardOutputAndError(standardOutputBuffer, numberOfCharsRead);
      return standardOutputAndError;
   }
}

#endif
