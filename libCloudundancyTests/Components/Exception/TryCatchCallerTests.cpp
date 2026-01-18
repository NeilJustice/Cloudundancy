#include "pch.h"
#include "libCloudundancy/Components/Exception/TryCatchCaller.h"

template<typename ArgumentType, typename ExceptionType>
TEMPLATE_TESTS(TryCatchCallerTests, ArgumentType, ExceptionType)
AFACT(TryCatchCallNonConstMemberFunction_CallsMemberFunctionWhichDoesNotThrow_ReturnsFunctionReturnValue)
AFACT(TryCatchCallNonConstMemberFunction_CallsMemberFunctionWhichThrowsException_CallsExceptionHandler_ReturnsExceptionHandlerReturnValue)
AFACT(TryCatchCallConstMemberFunction_CallsMemberFunctionWhichDoesNotThrow_DoesNotCallExceptionHandler)
AFACT(TryCatchCallConstMemberFunction_CallsMemberFunctionWhichThrows_CallsExceptionHandler)
EVIDENCE

class Class
{
public:
   mutable bool doThrowException = false;
   mutable vector<ArgumentType> calls;
   int exitCode;

   string exceptionMessage;
   mutable vector<pair<string, ArgumentType>> exceptionHandlerCalls;
   int exceptionHandlerExitCode;

   Class()
      : exitCode(ZenUnit::Random<int>())
      , exceptionMessage(ZenUnit::Random<string>())
      , exceptionHandlerExitCode(ZenUnit::Random<int>())
   {
   }

   int NonConstMemberFunction(ArgumentType argument)
   {
      calls.push_back(argument);
      if (doThrowException)
      {
         throw ExceptionType(exceptionMessage.c_str());
      }
      return exitCode;
   }

   void ConstMemberFunction(ArgumentType argument) const
   {
      calls.push_back(argument);
      if (doThrowException)
      {
         throw ExceptionType(exceptionMessage.c_str());
      }
   }

   int IntReturningConstMemberFunctionExceptionHandler(const exception& ex, ArgumentType argument) const
   {
      const string exceptionExceptionClassNameAndMessage = Type::GetExceptionClassNameAndMessage(&ex);
      exceptionHandlerCalls.emplace_back(exceptionExceptionClassNameAndMessage, argument);
      return exceptionHandlerExitCode;
   }

   void VoidConstMemberFunctionExceptionHandler(const exception& ex, ArgumentType argument) const
   {
      const string exceptionExceptionClassNameAndMessage = Type::GetExceptionClassNameAndMessage(&ex);
      exceptionHandlerCalls.emplace_back(exceptionExceptionClassNameAndMessage, argument);
   }
};

Class nonConstClassInstance;
const Class constClassInstance;
Utils::TryCatchCaller<Class, ArgumentType> _tryCatchCaller;

TEST(TryCatchCallNonConstMemberFunction_CallsMemberFunctionWhichDoesNotThrow_ReturnsFunctionReturnValue)
{
   const ArgumentType argument = ZenUnit::Random<ArgumentType>();
   nonConstClassInstance.doThrowException = false;
   //
   const int exitCode = _tryCatchCaller.TryCatchCallNonConstMemberFunction(
      &nonConstClassInstance, &Class::NonConstMemberFunction, argument, &Class::IntReturningConstMemberFunctionExceptionHandler);
   //
   VECTORS_ARE_EQUAL({ argument }, nonConstClassInstance.calls);
   ARE_EQUAL(nonConstClassInstance.exitCode, exitCode);
}

TEST(TryCatchCallNonConstMemberFunction_CallsMemberFunctionWhichThrowsException_CallsExceptionHandler_ReturnsExceptionHandlerReturnValue)
{
   const ArgumentType argument = ZenUnit::Random<ArgumentType>();
   nonConstClassInstance.doThrowException = true;
   //
   const int exitCode = _tryCatchCaller.TryCatchCallNonConstMemberFunction(
      &nonConstClassInstance, &Class::NonConstMemberFunction, argument, &Class::IntReturningConstMemberFunctionExceptionHandler);
   //
   VECTORS_ARE_EQUAL({ argument }, nonConstClassInstance.calls);
   ExceptionType ex(nonConstClassInstance.exceptionMessage.c_str());
   const string exceptionGetExceptionClassNameAndMessage = Type::GetExceptionClassNameAndMessage(&ex);
   vector<pair<string, ArgumentType>> expectedExceptionHandlerCalls =
   {
      { exceptionGetExceptionClassNameAndMessage, argument }
   };
   VECTORS_ARE_EQUAL(expectedExceptionHandlerCalls, nonConstClassInstance.exceptionHandlerCalls);
   ARE_EQUAL(nonConstClassInstance.exceptionHandlerExitCode, exitCode);
}

TEST(TryCatchCallConstMemberFunction_CallsMemberFunctionWhichDoesNotThrow_DoesNotCallExceptionHandler)
{
   const ArgumentType argument = ZenUnit::Random<ArgumentType>();
   nonConstClassInstance.doThrowException = false;
   //
   _tryCatchCaller.TryCatchCallConstMemberFunction(
      &constClassInstance, &Class::ConstMemberFunction, argument, &Class::VoidConstMemberFunctionExceptionHandler);
   //
   VECTORS_ARE_EQUAL({argument}, constClassInstance.calls);
}

TEST(TryCatchCallConstMemberFunction_CallsMemberFunctionWhichThrows_CallsExceptionHandler)
{
   const ArgumentType argument = ZenUnit::Random<ArgumentType>();
   constClassInstance.doThrowException = true;
   //
   _tryCatchCaller.TryCatchCallConstMemberFunction(
      &constClassInstance, &Class::ConstMemberFunction, argument, &Class::VoidConstMemberFunctionExceptionHandler);
   //
   VECTORS_ARE_EQUAL({argument}, constClassInstance.calls);
   ExceptionType ex(constClassInstance.exceptionMessage.c_str());
   const string exceptionGetExceptionClassNameAndMessage = Type::GetExceptionClassNameAndMessage(&ex);
   vector<pair<string, ArgumentType>> expectedExceptionHandlerCalls =
   {
      { exceptionGetExceptionClassNameAndMessage, argument }
   };
   VECTORS_ARE_EQUAL(expectedExceptionHandlerCalls, constClassInstance.exceptionHandlerCalls);
}

RUN_TEMPLATE_TESTS(TryCatchCallerTests, int, invalid_argument)
THEN_RUN_TEMPLATE_TESTS(TryCatchCallerTests, string, runtime_error)
