#pragma once
#if defined __linux__ || defined __APPLE__
class LinuxProcessRunnerTests;

namespace Utils
{
   class LinuxProcessRunner
   {
      friend class ::LinuxProcessRunnerTests;
   private:
      // Function Callers
      using _caller_Run_Type = const NonVoidTwoArgMemberFunctionCaller<ProcessResult, LinuxProcessRunner, string_view, string_view>;
      unique_ptr<const _caller_Run_Type> _caller_Run;
      // Constant Components
      unique_ptr<const Console> _console;
      unique_ptr<const ErrorCodeTranslator> _errorCodeTranslator;
   public:
      LinuxProcessRunner();
      virtual ~LinuxProcessRunner();
      virtual ProcessResult Run(string_view processName, string_view arguments) const;
      virtual ProcessResult FailFastRun(string_view processName, string_view arguments, bool doPrintStandardOutput) const;
   private:
      static unique_ptr<char*[]> MakeArgv(string_view processName, string_view arguments);
      void ThrowIfWifexitedReturnValueIsNot1(int wifexitedReturnValue) const;
      void ThrowRuntimeErrorIfPosixSpawnpReturnValueNot0(int posixSpawnpReturnValue) const;
      void ThrowRuntimeErrorIfWaitPidReturnValueDoesNotEqualPid(pid_t waitpidReturnValue, pid_t pid) const;
   };
}

#endif
