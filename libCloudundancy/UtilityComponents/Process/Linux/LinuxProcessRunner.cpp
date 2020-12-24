#include "pch.h"
#ifdef __linux__

#include "libCloudundancy/UtilityComponents/Process/Linux/LinuxProcessRunner.h"
#include <spawn.h>
#include <sys/wait.h>

LinuxProcessRunner::LinuxProcessRunner()
   // Function Callers
   : _caller_Run(make_unique<_caller_Run_Type>())
   // Constant Components
   , _console(make_unique<Console>())
{
}

LinuxProcessRunner::~LinuxProcessRunner()
{
}

ProcessResult LinuxProcessRunner::Run(string_view processName, string_view arguments) const // LCOV_EXCL_LINE
{
   const vector<string> spaceSplitArguments = String::Split(arguments, ' ');
   constexpr size_t ProcessNameArgv = 1;
   constexpr size_t TerminatingNullArgv = 1;
   unique_ptr<char*[]> argv = make_unique<char*[]>(ProcessNameArgv + spaceSplitArguments.size() + TerminatingNullArgv);
   argv[0] = const_cast<char*>(processName.data());
   for (size_t i = 1; i < spaceSplitArguments.size(); ++i)
   {
      const string& ithArgument = spaceSplitArguments[i];
      argv[1] = const_cast<char*>(ithArgument.c_str());
   }
   argv[ProcessNameArgv + spaceSplitArguments.size()] = nullptr;
   pid_t pid;
   const int posixSpawnpReturnValue = posix_spawnp(&pid, processName.data(), nullptr, nullptr, argv.get(), nullptr);
   if (posixSpawnpReturnValue != 0)
   {
      const int errnoValue = errno;
      const char* const readableErrno = strerror(errnoValue);
      const string exceptionMessage = String::Concat(
         "Error: 'posix_spawnp(&pid, processName.data(), nullptr, nullptr, argv.get(), nullptr)' returned non-0: ", posixSpawnpReturnValue,
         ". errno=", errnoValue, " (", readableErrno, ")");
      throw runtime_error(exceptionMessage);
   }
   int waitpidStatus;
	pid_t waitpidReturnValue = waitpid(pid, &waitpidStatus, 0);
	if (waitpidReturnValue != pid)
	{
      const int errnoValue = errno;
      const char* const readableErrno = strerror(errnoValue);
      const string exceptionMessage = String::Concat(
         "Error: 'waitpid(pid, &waitPidStatus, 0)' unexpectedly returned ", waitpidReturnValue,
         " which is not equal to pid ", pid, ". errno=", errnoValue, " strerror(errno)=", readableErrno);
      throw runtime_error(exceptionMessage);
   }
   const int wifexitedReturnValue = WIFEXITED(waitpidStatus);
   if (wifexitedReturnValue == 1)
   {
      ProcessResult processResult;
      processResult.processName = processName;
      processResult.arguments = arguments;
      processResult.exitCode = WEXITSTATUS(waitpidStatus);
      return processResult;
   }
   else
   {
      const int errnoValue = errno;
      const char* const readableErrno = strerror(errnoValue);
      const string exceptionMessage = String::Concat(
         "Error: 'WIFEXITED(waitPidStatus) did not return 1: ", wifexitedReturnValue, ". errno=", errnoValue, " (", readableErrno, ")");
      throw runtime_error(exceptionMessage);
   }
}

ProcessResult LinuxProcessRunner::FailFastRun(string_view processName, string_view arguments, bool /*doPrintStandardOutput*/) const
{
   const string runningMessage = String::Concat("[Cloudundancy] Running program: ", processName, ' ', arguments);
   _console->WriteLineColor(runningMessage, Color::Yellow);
   const ProcessResult processResult = _caller_Run->CallConstMemberFunction(
      &LinuxProcessRunner::Run, this, processName, arguments);
   if (processResult.exitCode != 0)
   {
      const string processFailedErrorMessage = String::Concat(
         "Process \"", processName, ' ', arguments, "\" failed to return exit code 0 by returning exit code ", processResult.exitCode, '.');
      _console->WriteLineAndExit(processFailedErrorMessage, processResult.exitCode);
   }
   return processResult;
}

#endif
