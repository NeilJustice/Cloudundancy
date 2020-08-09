#include "pch.h"
#include "libCloudundancy/Components/Strings/StringUtil.h"
#include "libCloudundancy/Components/Assertion/ReleaseAssert.h"

void ThrowLogicError(
   const char* predicateExpressionText,
   const char* filePath,
   size_t lineNumber,
   const char* functionName)
{
   const string what = String::Concat(
      "release_assert(", predicateExpressionText, ") failed in ",
      functionName, "()\n", filePath, "(", lineNumber, ")");
   throw logic_error(what);
}

void ReleaseAssert(
   bool predicateExpressionResult,
   const char* predicateExpressionText,
   const char* filePath,
   size_t lineNumber,
   const char* functionName)
{
#ifdef __linux__
   if (!predicateExpressionResult)
#elif _WIN32
   if (!predicateExpressionResult)
#endif
   {
      ThrowLogicError(predicateExpressionText, filePath, lineNumber, functionName);
   }
}
