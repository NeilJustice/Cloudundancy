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

ProcessResult LinuxProcessRunner::Run(string_view processName, string_view /*arguments*/) const // LCOV_EXCL_LINE
{
   char* argv[6];
   argv[0] = const_cast<char*>(processName.data());
   argv[1] = nullptr;
   // argv[1] = "a";
   // argv[2] = "-r";
   // argv[3] = "-mx9";
   // argv[4] = "7ZipFile\\HomeDirectory.7z";
   // argv[5] = nullptr;

   pid_t processPid;
   const int posixSpawnpReturnValue = posix_spawnp(&processPid, processName.data(), nullptr, nullptr, argv, nullptr);
   if (posixSpawnpReturnValue != 0)
   {

   }
   int waitPidStatus;
	pid_t waitpidReturnValue = waitpid(processPid, &waitPidStatus, 0);
	if (waitpidReturnValue != processPid)
	{
      const int errnoValue = errno;
      const char* const readableErrno = strerror(errnoValue);
      const string exceptionMessage = String::Concat(
         "Error: waitpid(processPid, &waitPidStatus, 0) unexpectedly returned ", waitpidReturnValue,
         " which is not equal to sevenZipPid ", processPid, ". errno=", errnoValue, " strerror(errno)=", readableErrno, '\n');
		throw runtime_error(exceptionMessage);
   }
   const int wifexitedReturnValue = WIFEXITED(waitPidStatus);
   if (wifexitedReturnValue == 1)
   {
      ProcessResult processResult{};
      return processResult;
   }
   else
   {
      throw runtime_error("WIFEXITED(waitPidStatus) did not return 1");
   }
}

ProcessResult LinuxProcessRunner::FailFastRun(string_view processName, string_view arguments, bool doPrintStandardOutput) const
{
   const string runningMessage = String::Concat("[Cloudundancy] Running program: ", processName, ' ', arguments);
   _console->WriteLineColor(runningMessage, Color::Yellow);
   const ProcessResult processResult = _caller_Run->CallConstMemberFunction(
      &LinuxProcessRunner::Run, this, processName, arguments);
   _console->WriteLineIf(doPrintStandardOutput, processResult.standardOutputAndError);
   if (processResult.exitCode != 0)
   {
      const string processFailedErrorMessage = String::Concat(
         "Process \"", processName, ' ', arguments, "\" failed to return exit code 0 by returning exit code ", processResult.exitCode, '.');
      _console->WriteLineAndExit(processFailedErrorMessage, processResult.exitCode);
   }
   return processResult;
}

#endif
