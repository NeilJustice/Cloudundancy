#pragma once
#ifdef __linux__
class Console;
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
public:
   LinuxProcessRunner();
   virtual ~LinuxProcessRunner();
   virtual ProcessResult Run(string_view processName, string_view arguments) const;
   virtual ProcessResult FailFastRun(string_view processName, string_view arguments, bool doPrintStandardOutput) const;
};

#endif
