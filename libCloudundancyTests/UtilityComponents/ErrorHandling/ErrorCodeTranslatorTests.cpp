#include "pch.h"
#if defined __linux__
#include <string.h> // strerror_r
#endif
#include "libCloudundancy/StaticUtilities/GetLinuxErrno.h"
#include "libCloudundancy/UtilityComponents/ErrorHandling/ErrorCodeTranslator.h"

TESTS(ErrorCodeTranslatorTests)
#if defined __linux__ || defined __APPLE__
AFACT(GetLinuxErrno_ReturnsAddressOfErrno)
#endif
AFACT(DefaultConstructor_SetsFunctionPointers)
AFACT(GetErrnoValue_ReturnsResultOfCallingErrnoFunction)
AFACT(GetErrnoWithDescription_ReturnsErrnoValueWithDescription)

#if defined __linux__ || defined __APPLE__
AFACT(GetErrnoDescription_ReturnsTheResultOfCallingStrErrorOnTheErrnoValue)
#elif _WIN32
AFACT(GetErrnoDescription_ReturnsTheResultOfCallingStrErrorOnTheErrnoValue)
#endif

#if defined __linux__ || defined __APPLE__
AFACT(GetSystemErrorDescriptionOnLinux_SystemErrorIs32_ReturnsIntAsString)
#elif _WIN32
AFACT(GetSystemErrorDescriptionOnWindows_SystemErrorIs32_ReturnsProcessCannotAccessTheFileMessage)
#endif
AFACT(GetSystemErrorDescription_SystemErrorIsNot32_ReturnsIntAsString)
EVIDENCE

Utils::ErrorCodeTranslator _errorCodeTranslator;

#if defined __linux__ || defined __APPLE__
METALMOCK_NONVOID3_FREE(char*, strerror_r, int, char*, size_t)
#elif _WIN32
METALMOCK_NONVOID3_FREE(errno_t, strerror_s, char*, size_t, int)
METALMOCK_NONVOID0_FREE(unsigned long, GetLastError)
#endif
METALMOCK_NONVOID0_FREE(int*, _call_errno)

STARTUP
{
   _errorCodeTranslator._call_errno = BIND_0ARG_METALMOCK_OBJECT(_call_errnoMock);
#if defined __linux__ || defined __APPLE__
   _errorCodeTranslator._call_strerror_r = BIND_3ARG_METALMOCK_OBJECT(strerror_rMock);
#elif _WIN32
   _errorCodeTranslator._call_strerror_s = BIND_3ARG_METALMOCK_OBJECT(strerror_sMock);
   _errorCodeTranslator._call_GetLastError = BIND_0ARG_METALMOCK_OBJECT(GetLastErrorMock);
#endif
}

#if defined __linux__ || defined __APPLE__
TEST(GetLinuxErrno_ReturnsAddressOfErrno)
{
   const int* const linuxErrno = GetLinuxErrno();
   IS_NOT_NULLPTR(linuxErrno);
}
#endif

TEST(DefaultConstructor_SetsFunctionPointers)
{
   Utils::ErrorCodeTranslator errorCodeTranslator;
   // Function Pointers
#if defined __linux__ || defined __APPLE__
   STD_FUNCTION_TARGETS(GetLinuxErrno, errorCodeTranslator._call_errno);
   STD_FUNCTION_TARGETS(strerror_r, errorCodeTranslator._call_strerror_r);
#elif _WIN32
   STD_FUNCTION_TARGETS(_errno, errorCodeTranslator._call_errno);
   STD_FUNCTION_TARGETS_OVERLOAD(
      Utils::ErrorCodeTranslator::strerror_s_function_type,
      strerror_s, errorCodeTranslator._call_strerror_s);
   STD_FUNCTION_TARGETS(GetLastError, errorCodeTranslator._call_GetLastError);
#endif
}

TEST(GetErrnoValue_ReturnsResultOfCallingErrnoFunction)
{
   int errnoValue = ZenUnit::Random<int>();
   _call_errnoMock.Return(&errnoValue);
   //
   const int returnedErrnoValue = _errorCodeTranslator.GetErrnoValue();
   //
   METALMOCK(_call_errnoMock.CalledOnce());
   ARE_EQUAL(errnoValue, returnedErrnoValue);
}

TEST(GetErrnoWithDescription_ReturnsErrnoValueWithDescription)
{
   class ErrorCodeTranslatorSelfMocked : public Metal::Mock<Utils::ErrorCodeTranslator>
   {
   public:
      METALMOCK_NONVOID0_FREE(int*, _call_errno)
         ErrorCodeTranslatorSelfMocked()
      {
         _call_errno = BIND_0ARG_METALMOCK_OBJECT(_call_errnoMock);
      }
      METALMOCK_NONVOID1_CONST(string, GetErrnoDescription, int)
   } errorCodeTranslatorSelfMocked;

   int errnoValue = ZenUnit::Random<int>();
   errorCodeTranslatorSelfMocked._call_errnoMock.Return(&errnoValue);
   const string errnoDescription = errorCodeTranslatorSelfMocked.GetErrnoDescriptionMock.ReturnRandom();
   //
   const pair<int, string> errnoWithDescription = errorCodeTranslatorSelfMocked.GetErrnoWithDescription();
   //
   METALMOCKTHEN(errorCodeTranslatorSelfMocked._call_errnoMock.CalledOnce()).Then(
   METALMOCKTHEN(errorCodeTranslatorSelfMocked.GetErrnoDescriptionMock.CalledOnceWith(errnoValue)));
   const pair<int, string> expectedErrnoWithDescription(errnoValue, errnoDescription);
   ARE_EQUAL(expectedErrnoWithDescription, errnoWithDescription);
}

#if _WIN32

class ErrorCodeTranslatorSelfMocked : public Metal::Mock<Utils::ErrorCodeTranslator>
{
public:
   METALMOCK_NONVOID0_FREE(DWORD, _call_GetLastError)
      ErrorCodeTranslatorSelfMocked()
   {
      _call_GetLastError = BIND_0ARG_METALMOCK_OBJECT(_call_GetLastErrorMock);
   }
   METALMOCK_NONVOID1_CONST(string, GetWindowsLastErrorDescription, DWORD)
} _errorCodeTranslatorSelfMocked;

TEST(GetWindowsLastErrorWithDescription_GetLastErrorReturns0_Returns0AndEmptyString)
{
   _errorCodeTranslatorSelfMocked._call_GetLastErrorMock.Return(0ul);
   //
   const pair<DWORD, string> windowsLastErrorWithDescription =
      _errorCodeTranslatorSelfMocked.GetWindowsLastErrorWithDescription();
   //
   METALMOCK(_errorCodeTranslatorSelfMocked._call_GetLastErrorMock.CalledOnce());
   const pair<DWORD, string> expectedWindowsLastErrorWithDescription(0ul, "");
   ARE_EQUAL(expectedWindowsLastErrorWithDescription, windowsLastErrorWithDescription);
}

TEST(GetWindowsLastErrorWithDescription_GetLastErrorReturnsNon0_ReturnsLastErrorAndErrorDescription)
{
   const DWORD windowsLastError = ZenUnit::RandomNon0<DWORD>();
   _errorCodeTranslatorSelfMocked._call_GetLastErrorMock.Return(windowsLastError);

   const string windowsLastErrorDescription =
      _errorCodeTranslatorSelfMocked.GetWindowsLastErrorDescriptionMock.ReturnRandom();
   //
   const pair<DWORD, string> windowsLastErrorWithDescription =
      _errorCodeTranslatorSelfMocked.GetWindowsLastErrorWithDescription();
   //
   METALMOCKTHEN(_errorCodeTranslatorSelfMocked._call_GetLastErrorMock.CalledOnce()).Then(
   METALMOCKTHEN(_errorCodeTranslatorSelfMocked.GetWindowsLastErrorDescriptionMock.CalledOnceWith(windowsLastError)));
   const pair<DWORD, string> expectedWindowsLastErrorWithDescription(windowsLastError, windowsLastErrorDescription);
   ARE_EQUAL(expectedWindowsLastErrorWithDescription, windowsLastErrorWithDescription);
}

#endif

#if defined __linux__ || defined __APPLE__

struct strerror_r_CallHistory
{
   size_t numberOfCalls = 0ULL;
   char* returnValue = nullptr;
   int errnoValueArgument = 0;
   char* outErrnoDescriptionCharsArgument = nullptr;
   string outErrnoDescriptionCharsReturnValue;
   size_t outErrnoDescriptionCharsSizeArgument = 0ULL;

   char* RecordFunctionCall(int errnoValue, char* outErrnoDescriptionChars, size_t outErrnoDescriptionCharsSize)
   {
      ++numberOfCalls;
      errnoValueArgument = errnoValue;
      outErrnoDescriptionCharsArgument = outErrnoDescriptionChars;
      strncpy(outErrnoDescriptionChars, outErrnoDescriptionCharsReturnValue.c_str(), outErrnoDescriptionCharsReturnValue.size());
      outErrnoDescriptionCharsSizeArgument = outErrnoDescriptionCharsSize;
      return returnValue;
   }

   void AssertCalledOnceWith(int expectedErrnoValue, size_t expectedOutErrnoDescriptionCharsSize) const
   {
      ARE_EQUAL(1ULL, numberOfCalls);
      ARE_EQUAL(expectedErrnoValue, errnoValueArgument);
      IS_NOT_NULLPTR(outErrnoDescriptionCharsArgument);
      ARE_EQUAL(expectedOutErrnoDescriptionCharsSize, outErrnoDescriptionCharsSizeArgument);
   }
} _strerror_r_CallHistory;

char* strerror_r_CallInstead(int errnoValue, char* outErrnoDescriptionChars, size_t outErrnoDescriptionCharsSize)
{
   ++_strerror_r_CallHistory.numberOfCalls;
   _strerror_r_CallHistory.errnoValueArgument = errnoValue;
   _strerror_r_CallHistory.outErrnoDescriptionCharsArgument = outErrnoDescriptionChars;
   strncpy(
      outErrnoDescriptionChars,
      _strerror_r_CallHistory.outErrnoDescriptionCharsReturnValue.c_str(),
      _strerror_r_CallHistory.outErrnoDescriptionCharsReturnValue.size());
   _strerror_r_CallHistory.outErrnoDescriptionCharsSizeArgument = outErrnoDescriptionCharsSize;
   return _strerror_r_CallHistory.returnValue;
}

TEST(GetErrnoDescription_ReturnsTheResultOfCallingStrErrorOnTheErrnoValue)
{
   const string errnoDescriptionChars = ZenUnit::Random<string>();
   _strerror_r_CallHistory.returnValue = const_cast<char*>(errnoDescriptionChars.c_str());
   _strerror_r_CallHistory.outErrnoDescriptionCharsReturnValue = ZenUnit::Random<string>();
   strerror_rMock.CallInstead(std::bind(&ErrorCodeTranslatorTests::strerror_r_CallInstead,
      this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
   const int errnoValue = ZenUnit::Random<int>();
   //
   const string errnoDescription = _errorCodeTranslator.GetErrnoDescription(errnoValue);
   //
   _strerror_r_CallHistory.AssertCalledOnceWith(errnoValue, 64ULL);
   ARE_EQUAL(_strerror_r_CallHistory.returnValue, errnoDescription);
}

#elif _WIN32

struct strerror_s_CallHistory
{
   size_t numberOfCalls = 0ULL;
   char* outErrnoDescriptionCharsArgument = nullptr;
   string outErrnoDescriptionCharsReturnValue;
   size_t outErrnoDescriptionCharsSizeArgument = 0ULL;
   int errnoValueArgument = 0;
   errno_t returnValue = 0;

   errno_t RecordFunctionCall(char* outErrnoDescriptionChars, size_t outErrnoDescriptionCharsSize, int errnoValue)
   {
      ++numberOfCalls;
      outErrnoDescriptionCharsArgument = outErrnoDescriptionChars;
      constexpr size_t maximumErrnoDescriptionLength = 64;
      const errno_t strcpyReturnValue = strcpy_s(
         outErrnoDescriptionChars,
         maximumErrnoDescriptionLength,
         outErrnoDescriptionCharsReturnValue.c_str());
      release_assert(strcpyReturnValue == 0);
      outErrnoDescriptionCharsSizeArgument = outErrnoDescriptionCharsSize;
      errnoValueArgument = errnoValue;
      return returnValue;
   }

   void AssertCalledOnceWith(size_t expectedOutErrnoDescriptionCharsSize, int expectedErrnoValue)
   {
      ARE_EQUAL(1ULL, numberOfCalls);
      IS_NOT_NULLPTR(outErrnoDescriptionCharsArgument);
      ARE_EQUAL(expectedOutErrnoDescriptionCharsSize, outErrnoDescriptionCharsSizeArgument);
      ARE_EQUAL(expectedErrnoValue, errnoValueArgument);
   }
} _strerror_s_CallHistory;

errno_t _strerror_s_CallInstead(char* outErrnoDescriptionChars, size_t outErrnoDescriptionCharsSize, int errnoValue)
{
   const errno_t returnValue = _strerror_s_CallHistory.RecordFunctionCall(
      outErrnoDescriptionChars, outErrnoDescriptionCharsSize, errnoValue);
   return returnValue;
}

TEST(GetErrnoDescription_ReturnsTheResultOfCallingStrErrorOnTheErrnoValue)
{
   _strerror_s_CallHistory.outErrnoDescriptionCharsReturnValue = ZenUnit::Random<string>();
   strerror_sMock.CallInstead(std::bind(&ErrorCodeTranslatorTests::_strerror_s_CallInstead,
      this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
   const int errnoValue = ZenUnit::Random<int>();
   //
   const string errnoDescription = _errorCodeTranslator.GetErrnoDescription(errnoValue);
   //
   _strerror_s_CallHistory.AssertCalledOnceWith(64ull, errnoValue);
   ARE_EQUAL(_strerror_s_CallHistory.outErrnoDescriptionCharsReturnValue, errnoDescription);
}

#endif

#if defined __linux__ || defined __APPLE__

TEST(GetSystemErrorDescriptionOnLinux_SystemErrorIs32_ReturnsIntAsString)
{
   const string systemErrorDescription = _errorCodeTranslator.GetSystemErrorDescription(32);
   //
   const string expectedSystemErrorDescription = to_string(32);
   ARE_EQUAL(expectedSystemErrorDescription, systemErrorDescription);
}

#elif _WIN32

TEST(GetSystemErrorDescriptionOnWindows_SystemErrorIs32_ReturnsProcessCannotAccessTheFileMessage)
{
   const string systemErrorDescription = _errorCodeTranslator.GetSystemErrorDescription(ERROR_SHARING_VIOLATION);
   ARE_EQUAL("The process cannot access the file because it is being used by another process.", systemErrorDescription);
}

#endif

TEST(GetSystemErrorDescription_SystemErrorIsNot32_ReturnsIntAsString)
{
   const int systemErrorValue = ZenUnit::RandomBetween<int>(0, 31);
   //
   const string systemErrorDescription = _errorCodeTranslator.GetSystemErrorDescription(systemErrorValue);
   //
   const string expectedSystemErrorDescription = to_string(systemErrorValue);
   ARE_EQUAL(expectedSystemErrorDescription, systemErrorDescription);
}

RUN_TESTS(ErrorCodeTranslatorTests)
