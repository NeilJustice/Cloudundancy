#include "pch.h"
#include "libCloudundancy/Components/Assertion/Asserter.h"

void Asserter::ThrowIfNotEqual(size_t expected, size_t actual, string_view message) const
{
   if (actual != expected)
   {
      const string exceptionMessage = String::Concat(
         "Asserter::ThrowIfNotEqual(expected, actual, message) failed due to expected != actual.\n",
         " expected=", expected, '\n',
         "   actual=", actual, '\n',
         "  message=\"", message, "\"");
      throw runtime_error(exceptionMessage);
   }
}
