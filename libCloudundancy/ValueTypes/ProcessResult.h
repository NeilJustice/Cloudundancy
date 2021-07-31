#pragma once

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

#ifdef _WIN32
   #ifdef _DEBUG
      static_assert(sizeof(ProcessResult) == 136);
   #else
      static_assert(sizeof(ProcessResult) == 112);
   #endif
#else
   static_assert(sizeof(ProcessResult) == 112);
#endif
