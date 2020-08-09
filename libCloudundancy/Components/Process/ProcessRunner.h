#pragma once
#include "libCloudundancy/Components/Process/ProcessResult.h"
class ProcessRunnerTests;

#ifdef __linux__
class LinuxProcessRunner;
#elif _WIN32
class WindowsProcessRunner;
#endif

class ProcessRunner
{
   friend class ::ProcessRunnerTests;
private:
#ifdef __linux__
   unique_ptr<const LinuxProcessRunner> _osSpecificProcessRunner;
#elif _WIN32
   unique_ptr<const WindowsProcessRunner> _osSpecificProcessRunner;
#endif
public:
   ProcessRunner();
   virtual ~ProcessRunner();
   virtual ProcessResult Run(string_view processName, string_view arguments) const;
   virtual ProcessResult FailFastRun(string_view processName, string_view arguments) const;
};
