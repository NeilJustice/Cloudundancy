#include "pch.h"
#include "ProcessResult.h"

ProcessResult::ProcessResult()
   : exitCode(0)
   , milliseconds(0)
{
}

ProcessResult::ProcessResult(
   string_view processName,
   string_view arguments,
   int exitCode,
   string_view standardOutputAndError,
   unsigned milliseconds)
   : processName(processName)
   , arguments(arguments)
   , exitCode(exitCode)
   , standardOutputAndError(standardOutputAndError)
   , milliseconds(milliseconds)
{
}
