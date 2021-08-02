#include "pch.h"
#include "libCloudundancy/UtilityComponents/ErrorHandling/ErrorCodeTranslator.h"
#include "libCloudundancy/StaticUtilities/GetLinuxErrno.h"

namespace Utils
{
   ErrorCodeTranslator::ErrorCodeTranslator()
   #if defined __linux__ || defined __APPLE__
      : _call_errno(GetLinuxErrno)
      , _call_strerror_r(strerror_r)
   #elif _WIN32
      : _call_errno(_errno)
      , _call_strerror_s(static_cast<strerror_s_function_type>(strerror_s))
      , _call_GetLastError(GetLastError)
   #endif
   {
   }

   int ErrorCodeTranslator::GetErrnoValue() const
   {
      const int errnoValue = *_call_errno();
      return errnoValue;
   }

   pair<int, string> ErrorCodeTranslator::GetErrnoWithDescription() const
   {
      const int errnoValue = *_call_errno();
      const string errnoDescription = GetErrnoDescription(errnoValue);
      pair<int, string> errnoWithDescription(errnoValue, errnoDescription);
      return errnoWithDescription;
   }

   #ifdef _WIN32

   pair<DWORD, string> ErrorCodeTranslator::GetWindowsLastErrorWithDescription() const
   {
      const DWORD windowsLastError = _call_GetLastError();
      if (windowsLastError == 0)
      {
         return make_pair(0ul, ""s);
      }
      const string windowsLastErrorDescription = GetWindowsLastErrorDescription(windowsLastError);
      pair<DWORD, string> windowsLastErrorAndDescription = make_pair(windowsLastError, windowsLastErrorDescription);
      return windowsLastErrorAndDescription;
   }

   string ErrorCodeTranslator::GetWindowsLastErrorDescription(DWORD windowsLastError) const
   {
      string windowsLastErrorDescription;
      char windowsLastErrorDescriptionChars[256]{};
      const DWORD numberOfMessageCharacters = FormatMessageA(
         FORMAT_MESSAGE_FROM_SYSTEM,
         nullptr,
         windowsLastError,
         0,
         windowsLastErrorDescriptionChars,
         sizeof(windowsLastErrorDescriptionChars),
         nullptr);
      windowsLastErrorDescription.assign(
         windowsLastErrorDescriptionChars, windowsLastErrorDescriptionChars + numberOfMessageCharacters);
      return windowsLastErrorDescription;
   }
   #endif

   constexpr size_t MaximumErrnoDescriptionLength = 64ULL;

   #if defined __linux__ || defined __APPLE__

   string ErrorCodeTranslator::GetErrnoDescription(int errnoValue) const
   {
      char* errnoDescriptionChars = static_cast<char*>(alloca(MaximumErrnoDescriptionLength));
      errnoDescriptionChars = _call_strerror_r(errnoValue, errnoDescriptionChars, MaximumErrnoDescriptionLength);
      string errnoDescription(errnoDescriptionChars);
      return errnoDescription;
   }

   #elif _WIN32

   string ErrorCodeTranslator::GetErrnoDescription(int errnoValue) const
   {
      array<char, MaximumErrnoDescriptionLength> errnoDescriptionChars{};
      const errno_t strErrorSReturnValue = _call_strerror_s(errnoDescriptionChars.data(), MaximumErrnoDescriptionLength, errnoValue);
      release_assert(strErrorSReturnValue == 0);
      string errnoDescription(errnoDescriptionChars.data());
      return errnoDescription;
   }

   #endif

   string ErrorCodeTranslator::GetSystemErrorDescription(int systemErrorValue) const
   {
   #if _WIN32
      switch (systemErrorValue)
      {
      case ERROR_SHARING_VIOLATION:
         return "The process cannot access the file because it is being used by another process.";
      }
   #endif
      return to_string(systemErrorValue);
   }
}
