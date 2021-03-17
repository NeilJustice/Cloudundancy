#include "pch.h"
#include "libCloudundancy/UtilityComponents/Assertion/Asserter.h"

void Asserter::ThrowIfIntsNotEqual(int expected, int actual, string_view message) const
{
   if (actual != expected)
   {
      const string exceptionMessage = String::Concat(
         "Asserter::ThrowIfIntsNotEqual(expected, actual, message) failed due to expected != actual.\n",
         " expected=", expected, '\n', "   actual=", actual, '\n', "  message=\"", message, "\"");
      throw runtime_error(exceptionMessage);
   }
}

void Asserter::ThrowIfSizeTsNotEqual(size_t expected, size_t actual, string_view message) const
{
   if (actual != expected)
   {
      const string exceptionMessage = String::Concat(
         "Asserter::ThrowIfSizeTsNotEqual(expected, actual, message) failed due to expected != actual.\n",
         " expected=", expected, '\n', "   actual=", actual, '\n', "  message=\"", message, "\"");
      throw runtime_error(exceptionMessage);
   }
}
