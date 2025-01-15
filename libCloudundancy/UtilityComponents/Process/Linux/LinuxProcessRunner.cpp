#include "pch.h"
#if defined __linux__ || defined __APPLE__

#include "libCloudundancy/UtilityComponents/ErrorHandling/ErrorCodeTranslator.h"
#include "libCloudundancy/UtilityComponents/Process/Linux/LinuxProcessRunner.h"
#include <spawn.h>
#include <sys/wait.h>

namespace Utils
{
   LinuxProcessRunner::LinuxProcessRunner()
      // Function Callers
      : _caller_Run(make_unique<_caller_Run_Type>())
      // Constant Components
      , _console(make_unique<Console>())
      , _errorCodeTranslator(make_unique<ErrorCodeTranslator>())
   {
   }

   LinuxProcessRunner::~LinuxProcessRunner()
   {
   }

   ProcessResult LinuxProcessRunner::Run(string_view processName, string_view arguments) const // LCOV_EXCL_LINE
   {
      const unique_ptr<char*[]> argv = MakeArgv(processName, arguments);
      pid_t pid = 0;
      const int posixSpawnpReturnValue = posix_spawnp(&pid, processName.data(), nullptr, nullptr, argv.get(), nullptr);
      ThrowRuntimeErrorIfPosixSpawnpReturnValueNot0(posixSpawnpReturnValue);
      int waitpidStatus = 0;
      pid_t waitpidReturnValue = waitpid(pid, &waitpidStatus, 0);
      ThrowRuntimeErrorIfWaitPidReturnValueDoesNotEqualPid(waitpidReturnValue, pid);
      const int wifexitedReturnValue = WIFEXITED(waitpidStatus);
      ThrowIfWifexitedReturnValueIsNot1(wifexitedReturnValue);
      ProcessResult processResult;
      processResult.processName = processName;
      processResult.arguments = arguments;
      processResult.exitCode = WEXITSTATUS(waitpidStatus);
      return processResult;
   }

   ProcessResult LinuxProcessRunner::FailFastRun(string_view processName, string_view arguments, bool /*doPrintStandardOutput*/) const
   {
      const string runningMessage = Utils::String::ConcatStrings("[Cloudundancy] Running program: ", processName, " ", arguments);
      _console->WriteLineColor(runningMessage, Color::Yellow);
      ProcessResult processResult = _caller_Run->CallConstMemberFunction(this, &LinuxProcessRunner::Run, processName, arguments);
      if (processResult.exitCode != 0)
      {
         const string processFailedErrorMessage = Utils::String::ConcatValues(
            "Process \"", processName, ' ', arguments, "\" failed with exit code ", processResult.exitCode, '.');
         _console->WriteLineAndExit(processFailedErrorMessage, processResult.exitCode);
      }
      return processResult;
   }

   // Private Functions

   unique_ptr<char*[]> LinuxProcessRunner::MakeArgv(string_view processName, string_view arguments)
   {
      const vector<string> spaceSplitArguments = Utils::String::Split(arguments, ' ');
      constexpr size_t ProcessNameArgv = 1;
      constexpr size_t TerminatingNullArgv = 1;
      unique_ptr<char*[]> argv = make_unique<char*[]>(ProcessNameArgv + spaceSplitArguments.size() + TerminatingNullArgv);
      argv[0] = const_cast<char*>(processName.data());
      for (size_t i = 1; i <= spaceSplitArguments.size(); ++i)
      {
         const string& ithArgument = spaceSplitArguments[i - 1];
         argv[i] = const_cast<char*>(ithArgument.c_str());
      }
      argv[ProcessNameArgv + spaceSplitArguments.size()] = nullptr;
      return argv;
   }

   void LinuxProcessRunner::ThrowIfWifexitedReturnValueIsNot1(int wifexitedReturnValue) const
   {
      if (wifexitedReturnValue != 1)
      {
         const pair<int, string> errnoAndErrnoDescription = _errorCodeTranslator->GetErrnoWithDescription();
         const string exceptionMessage = Utils::String::ConcatValues(
            "'WIFEXITED(waitPidStatus) did not return 1: ", errnoAndErrnoDescription.first,
            ". errno=", errnoAndErrnoDescription.first, " (", errnoAndErrnoDescription.second, ")");
         throw runtime_error(exceptionMessage);
      }
   }

   void LinuxProcessRunner::ThrowRuntimeErrorIfPosixSpawnpReturnValueNot0(int posixSpawnpReturnValue) const
   {
      if (posixSpawnpReturnValue != 0)
      {
         const pair<int, string> errnoAndErrnoDescription = _errorCodeTranslator->GetErrnoWithDescription();
         const string exceptionMessage = Utils::String::ConcatValues(
            "'posix_spawnp(&pid, processName.data(), nullptr, nullptr, argv.get(), nullptr)' returned non-0: ", posixSpawnpReturnValue,
            ". errno=", errnoAndErrnoDescription.first, " (", errnoAndErrnoDescription.second, ')');
         throw runtime_error(exceptionMessage);
      }
   }

   void LinuxProcessRunner::ThrowRuntimeErrorIfWaitPidReturnValueDoesNotEqualPid(pid_t waitpidReturnValue, pid_t pid) const
   {
      if (waitpidReturnValue != pid)
      {
         const pair<int, string> errnoAndErrnoDescription = _errorCodeTranslator->GetErrnoWithDescription();
         const string exceptionMessage = Utils::String::ConcatValues(
            "'waitpid(pid, &waitPidStatus, 0)' unexpectedly returned ", waitpidReturnValue, " which is not equal to pid ", pid,
            ". errno=", errnoAndErrnoDescription.first, " (", errnoAndErrnoDescription.second, ')');
         throw runtime_error(exceptionMessage);
      }
   }
}

#endif
