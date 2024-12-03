#include "pch.h"
#include "libCloudundancy/UtilityComponents/Asserters/Asserter.h"

namespace Utils
{
   void Asserter::ThrowIfIntsNotEqual(int expected, int actual, string_view message) const
   {
      if (actual != expected)
      {
         const string exceptionMessage = Utils::String::ConcatValues(
            "Asserter::ThrowIfIntsNotEqual(expected, actual, message) failed due to expected != actual.\n",
            " expected=", expected, '\n', "   actual=", actual, '\n', "  message=\"", message, "\"");
         throw runtime_error(exceptionMessage);
      }
   }

   void Asserter::ThrowIfSizeTsNotEqual(size_t expected, size_t actual, string_view message) const
   {
      if (actual != expected)
      {
         const string exceptionMessage = Utils::String::ConcatValues(
            "Asserter::ThrowIfSizeTsNotEqual(expected, actual, message) failed due to expected != actual.\n",
            " expected=", expected, '\n', "   actual=", actual, '\n', "  message=\"", message, "\"");
         throw runtime_error(exceptionMessage);
      }
   }
}
