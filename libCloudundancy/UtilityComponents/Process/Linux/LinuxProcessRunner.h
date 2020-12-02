#pragma once
#ifdef __linux__

class Console;
template<typename ReturnType, typename ClassType, typename Arg1Type, typename Arg2Type>
class NonVoidTwoArgMemberFunctionCaller;

class LinuxProcessRunner
{
public:
   virtual ~LinuxProcessRunner();
   virtual ProcessResult Run(string_view processName, string_view arguments) const;
   virtual ProcessResult FailFastRun(string_view processName, string_view arguments, bool doPrintStandardOutput) const;
};

#endif
