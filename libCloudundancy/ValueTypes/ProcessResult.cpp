#include "pch.h"
#include "ProcessResult.h"

namespace Utils
{
   ProcessResult::ProcessResult()
      : exitCode(0)
      , durationInMilliseconds(0)
   {
   }

   ProcessResult::ProcessResult(
      string_view processName,
      string_view arguments,
      int exitCode,
      string_view standardOutputAndError,
      unsigned durationInMilliseconds)
      : processName(processName)
      , arguments(arguments)
      , exitCode(exitCode)
      , standardOutputAndError(standardOutputAndError)
      , durationInMilliseconds(durationInMilliseconds)
   {
   }
}
