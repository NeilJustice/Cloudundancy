#pragma once
#ifdef __linux__
#include "libCloudundancy/Components/Process/ProcessResult.h"
#include "libCloudundancy/Components/Process/ProcessRunner.h"

class Console;
template<typename ReturnType, typename ClassType, typename Arg1Type, typename Arg2Type>
class NonVoidTwoArgMemberFunctionCaller;

class LinuxProcessRunner
{
public:
   virtual ~LinuxProcessRunner();
   virtual ProcessResult Run(string_view processName, string_view arguments) const;
   virtual ProcessResult FailFastRun(string_view processName, string_view arguments) const;
};

#endif
