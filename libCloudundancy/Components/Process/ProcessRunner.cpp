#include "pch.h"
#include "libCloudundancy/Components/Process/ProcessRunner.h"
#if defined __linux__
#include "libCloudundancy/Components/Process/Linux/LinuxProcessRunner.h"
#elif _WIN32
#include "libCloudundancy/Components/Process/Windows/WindowsProcessRunner.h"
#endif

namespace Utils
{
   ProcessRunner::ProcessRunner()
      // Constant Components
   #if defined __linux__
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
}
