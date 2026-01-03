#pragma once

namespace Utils
{
   struct ProcessResult
   {
      string processName;
      string arguments;
      int exitCode;
      string standardOutputAndError;
      unsigned durationInMilliseconds;

      ProcessResult();
      ProcessResult(
         string_view processName,
         string_view arguments,
         int exitCode,
         string_view standardOutputAndError,
         unsigned durationInMilliseconds);
   };
}

#ifdef _WIN32
   #ifdef _DEBUG
      static_assert(sizeof(Utils::ProcessResult) == 136);
   #else
      static_assert(sizeof(Utils::ProcessResult) == 112);
   #endif
#elifdef __linux__
   #ifdef _LIBCPP_VERSION
      static_assert(sizeof(Utils::ProcessResult) == 88);
   #else
      static_assert(sizeof(Utils::ProcessResult) == 112);
   #endif
#endif
