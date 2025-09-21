#pragma once
class ProcessRunnerTests;

namespace Utils
{
#if defined __linux__
   class LinuxProcessRunner;
#elif _WIN32
   class WindowsProcessRunner;
#endif

   class ProcessRunner
   {
      friend class ::ProcessRunnerTests;
   private:
      // Constant Components
   #if defined __linux__
      unique_ptr<const LinuxProcessRunner> _osSpecificProcessRunner;
   #elif _WIN32
      unique_ptr<const WindowsProcessRunner> _osSpecificProcessRunner;
   #endif
   public:
      ProcessRunner();
      virtual ~ProcessRunner();
      virtual ProcessResult FailFastRun(string_view processName, string_view arguments, bool doPrintStandardOutput) const;
      virtual ProcessResult Run(string_view processName, string_view arguments) const;
   };
}
