#include "pch.h"
#include "libCloudundancy/Components/FunctionCallers/Member/VoidZeroArgMemberFunctionCaller.h"

TESTS(VoidZeroArgMemberFunctionCallerTests)
AFACT(CallConstMemberFunction_CallsConstMemberFunction)
AFACT(CallCallNonConstMemberFunctionMemberFunction_CallsNonConstMemberFunction)
EVIDENCE

class Class
{
public:
   mutable size_t numberOfCalls = 0;

   void ConstMemberVoidFunction() const
   {
      ++numberOfCalls;
   }

   void NonConstMemberVoidFunction()
   {
      ++numberOfCalls;
   }
};

TEST(CallConstMemberFunction_CallsConstMemberFunction)
{
   const Class constClassInstance{};
   Utils::VoidZeroArgMemberFunctionCaller<Class> oneArgVoidMemberFunctionCaller{};
   //
   oneArgVoidMemberFunctionCaller.CallConstMemberFunction(
      &constClassInstance, &Class::ConstMemberVoidFunction);
   //
   ARE_EQUAL(1, constClassInstance.numberOfCalls);
   //
   oneArgVoidMemberFunctionCaller.CallConstMemberFunction(
      &constClassInstance, &Class::ConstMemberVoidFunction);
   //
   ARE_EQUAL(2, constClassInstance.numberOfCalls);
}

TEST(CallCallNonConstMemberFunctionMemberFunction_CallsNonConstMemberFunction)
{
   Class nonConstClassInstance{};
   Utils::VoidZeroArgMemberFunctionCaller<Class> oneArgVoidMemberFunctionCaller{};
   //
   oneArgVoidMemberFunctionCaller.CallCallNonConstMemberFunctionMemberFunction(
      &nonConstClassInstance, &Class::NonConstMemberVoidFunction);
   //
   ARE_EQUAL(1, nonConstClassInstance.numberOfCalls);
   //
   oneArgVoidMemberFunctionCaller.CallCallNonConstMemberFunctionMemberFunction(
      &nonConstClassInstance, &Class::NonConstMemberVoidFunction);
   //
   ARE_EQUAL(2, nonConstClassInstance.numberOfCalls);
}

RUN_TESTS(VoidZeroArgMemberFunctionCallerTests)
