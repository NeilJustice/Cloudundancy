#include "pch.h"
#include "libCloudundancy/UtilityComponents/Process/ProcessRunner.h"
#if defined __linux__ || defined __APPLE__
#include "libCloudundancy/UtilityComponents/Process/Linux/LinuxProcessRunner.h"
#elif _WIN32
#include "libCloudundancy/UtilityComponents/Process/Windows/WindowsProcessRunner.h"
#endif

ProcessRunner::ProcessRunner()
#if defined __linux__ || defined __APPLE__
   : _osSpecificProcessRunner(make_unique<LinuxProcessRunner>())
#elif _WIN32
   : _osSpecificProcessRunner(make_unique<WindowsProcessRunner>())
#endif
{
}

ProcessRunner::~ProcessRunner()
{
}

ProcessResult ProcessRunner::FailFastRun(string_view processName, string_view arguments, bool doPrintStandardOutput) const
{
   ProcessResult processResult = _osSpecificProcessRunner->FailFastRun(processName, arguments, doPrintStandardOutput);
   return processResult;
}

ProcessResult ProcessRunner::Run(string_view processName, string_view arguments) const
{
   ProcessResult processResult = _osSpecificProcessRunner->Run(processName, arguments);
   return processResult;
}
