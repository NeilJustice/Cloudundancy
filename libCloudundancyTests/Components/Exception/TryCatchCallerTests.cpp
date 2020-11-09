#include "pch.h"
#include "libCloudundancy/StaticUtilities/Exception.h"
#include "libCloudundancy/Components/Exception/TryCatchCaller.h"

template<typename ArgumentType, typename ExceptionType>
TEMPLATE_TESTS(TryCatchCallerTests, ArgumentType, ExceptionType)
AFACT(TryCatchCall_CallsFunctionWhichDoesNotThrow_ReturnsFunctionReturnValue)
AFACT(TryCatchCall_CallsFunctionWhichThrowsException_CallsExceptionHandler_ReturnsExceptionHandlerReturnValue)
EVIDENCE

class Class
{
public:
   bool doThrow;
   vector<ArgumentType> calls;
   int exitCode;

   string exceptionWhat;
   vector<pair<string, ArgumentType>> exceptionHandlerCalls;
   int exceptionHandlerExitCode;

   Class()
      : doThrow(false)
   {
      exitCode = ZenUnit::Random<int>();
      exceptionWhat = ZenUnit::Random<string>();
      exceptionHandlerExitCode = ZenUnit::Random<int>();
   }

   int MemberFunction(ArgumentType argument)
   {
      calls.push_back(argument);
      if (doThrow)
      {
         throw ExceptionType(exceptionWhat.c_str());
      }
      return exitCode;
   }

   int ExceptionHandler(const exception& ex, ArgumentType argument)
   {
      const string exceptionGetExceptionClassNameAndMessage = Exception::GetExceptionClassNameAndMessage(&ex);
      exceptionHandlerCalls.emplace_back(exceptionGetExceptionClassNameAndMessage, argument);
      return exceptionHandlerExitCode;
   }
};

Class classInstance;
TryCatchCaller<Class, ArgumentType> _tryCatchCaller;

TEST(TryCatchCall_CallsFunctionWhichDoesNotThrow_ReturnsFunctionReturnValue)
{
   const ArgumentType argument = ZenUnit::Random<ArgumentType>();
   classInstance.doThrow = false;
   //
   const int exitCode = _tryCatchCaller.TryCatchCall(
      &classInstance, &Class::MemberFunction, argument, &Class::ExceptionHandler);
   //
   VECTORS_ARE_EQUAL({ argument }, classInstance.calls);
   ARE_EQUAL(classInstance.exitCode, exitCode);
}

TEST(TryCatchCall_CallsFunctionWhichThrowsException_CallsExceptionHandler_ReturnsExceptionHandlerReturnValue)
{
   const ArgumentType argument = ZenUnit::Random<ArgumentType>();
   classInstance.doThrow = true;
   //
   const int exitCode = _tryCatchCaller.TryCatchCall(
      &classInstance, &Class::MemberFunction, argument, &Class::ExceptionHandler);
   //
   VECTORS_ARE_EQUAL({ argument }, classInstance.calls);
   ExceptionType ex(classInstance.exceptionWhat.c_str());
   const string exceptionGetExceptionClassNameAndMessage = Exception::GetExceptionClassNameAndMessage(&ex);
   vector<pair<string, ArgumentType>> expectedExceptionHandlerCalls =
   {
      { exceptionGetExceptionClassNameAndMessage, argument }
   };
   VECTORS_ARE_EQUAL(expectedExceptionHandlerCalls, classInstance.exceptionHandlerCalls);
   ARE_EQUAL(classInstance.exceptionHandlerExitCode, exitCode);
}

RUN_TEMPLATE_TESTS(TryCatchCallerTests, int, invalid_argument)
THEN_RUN_TEMPLATE_TESTS(TryCatchCallerTests, string, runtime_error)
