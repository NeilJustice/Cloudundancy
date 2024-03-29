#pragma once
#ifdef _WIN32
class Console;
template<typename ReturnType, typename ClassType, typename Arg1Type, typename Arg2Type>
class NonVoidTwoArgMemberFunctionCaller;
class WindowsProcessRunnerTests;

namespace Utils
{
   class WindowsProcessRunner
   {
      friend class WindowsProcessRunnerTests;
   private:
      // Function Callers
      using _caller_Run_Type = const NonVoidTwoArgMemberFunctionCaller<ProcessResult, WindowsProcessRunner, string_view, string_view>;
      unique_ptr<const _caller_Run_Type> _caller_Run;
      // Constant Components
      unique_ptr<const Console> _console;
   public:
      WindowsProcessRunner();
      virtual ~WindowsProcessRunner();
      virtual ProcessResult Run(string_view processName, string_view arguments) const;
      virtual ProcessResult FailFastRun(string_view processName, string_view arguments, bool doPrintStandardOutput) const;
   private:
      static string ReadPipe(HANDLE pipeHandle);
   };
}

#endif
