#pragma once
#if defined __linux__ || defined __APPLE__
class Console;
class ErrorCodeTranslator;
class LinuxProcessRunnerTests;
template<typename ReturnType, typename ClassType, typename Arg1Type, typename Arg2Type>
class NonVoidTwoArgMemberFunctionCaller;

class LinuxProcessRunner
{
   friend class LinuxProcessRunnerTests;
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
   unique_ptr<char*[]> MakeArgv(string_view processName, string_view arguments) const;
   void ThrowRuntimeErrorIfPosixSpawnpReturnValueNot0(int posixSpawnpReturnValue) const;
   void ThrowRuntimeErrorIfWaitPidReturnValueDoesNotEqualPid(pid_t waitpidReturnValue, pid_t pid) const;
};

#endif
