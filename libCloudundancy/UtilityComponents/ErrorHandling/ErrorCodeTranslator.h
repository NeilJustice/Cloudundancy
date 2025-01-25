#pragma once
class ErrorCodeTranslatorTests;

namespace Utils
{
   class ErrorCodeTranslator
   {
      friend class ::ErrorCodeTranslatorTests;
   public:
   #ifdef _WIN32
      using strerror_s_function_type = errno_t(*)(char*, size_t, int);
   #endif
   private:
      function<int* ()> _call_errno;
   #if defined __linux__
      std::function<char* (int, char*, size_t)> _call_strerror_r;
   #elif _WIN32
      std::function<errno_t(char*, size_t, int)> _call_strerror_s;
      std::function<DWORD()> _call_GetLastError;
   #endif
   public:
      ErrorCodeTranslator();
      virtual ~ErrorCodeTranslator() = default;
      virtual int GetErrnoValue() const;
      virtual pair<int, string> GetErrnoWithDescription() const;
      virtual string GetErrnoDescription(int errnoValue) const;
      virtual string GetSystemErrorDescription(int systemErrorValue) const;
   #ifdef _WIN32
      virtual pair<DWORD, string> GetWindowsLastErrorWithDescription() const;
      virtual string GetWindowsLastErrorDescription(DWORD windowsLastError) const;
   #endif
   };
}
