#include "pch.h"
#include "libCloudundancy/Components/Exception/Exception.h"

TESTS(ExceptionTests)
AFACT(GetClassNameAndMessage_ReturnsExceptionClassNameColonSpaceExceptionMessage__DefaultExceptionTestCase)
AFACT(GetClassNameAndMessage_ReturnsExceptionClassNameColonSpaceExceptionMessage__RuntimeErrorTestCase)
EVIDENCE

TEST(GetClassNameAndMessage_ReturnsExceptionClassNameColonSpaceExceptionMessage__DefaultExceptionTestCase)
{
   const exception ex;
#ifdef __linux__
   ARE_EQUAL("std::exception: std::exception", Exception::GetExceptionClassNameAndMessage(&ex));
#elif _WIN32
   ARE_EQUAL("std::exception: Unknown exception", Exception::GetExceptionClassNameAndMessage(&ex));
#endif
}

TEST(GetClassNameAndMessage_ReturnsExceptionClassNameColonSpaceExceptionMessage__RuntimeErrorTestCase)
{
   const string exceptionMessage = ZenUnit::Random<string>();
   const runtime_error runtimeError(exceptionMessage);
   //
   const string exceptionClassNameAndMessage = Exception::GetExceptionClassNameAndMessage(&runtimeError);
   //
   const string expectedReturnValue = "std::runtime_error: " + exceptionMessage;
	ARE_EQUAL(expectedReturnValue, exceptionClassNameAndMessage);
}

RUN_TESTS(ExceptionTests)
