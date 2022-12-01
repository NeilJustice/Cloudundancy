#include "pch.h"
#include "libCloudundancy/UtilityComponents/FunctionCallers/Member/VoidOneArgMemberFunctionCaller.h"

template<typename ArgType>
TEMPLATE_TESTS(VoidOneArgMemberFunctionCallerTests, ArgType)
AFACT(CallConstMemberFunction_CallsConstMemberFunction)
AFACT(CallCallNonConstMemberFunctionMemberFunction_CallsNonConstMemberFunction)
EVIDENCE

class Class
{
public:
   mutable vector<ArgType> calls;

   void ConstMemberVoidFunction(ArgType arg) const
   {
      calls.push_back(arg);
   }

   void NonConstMemberVoidFunction(ArgType arg)
   {
      calls.push_back(arg);
   }
};

TEST(CallConstMemberFunction_CallsConstMemberFunction)
{
   const Class constClassInstance{};
   Utils::VoidOneArgMemberFunctionCaller<Class, ArgType> oneArgVoidMemberFunctionCaller{};
   IS_EMPTY(constClassInstance.calls);
   //
   oneArgVoidMemberFunctionCaller.CallConstMemberFunction(
      &constClassInstance, &Class::ConstMemberVoidFunction, ArgType{ 1 });
   //
   VECTORS_ARE_EQUAL(vector<ArgType>{ 1 }, constClassInstance.calls);
   //
   oneArgVoidMemberFunctionCaller.CallConstMemberFunction(
      &constClassInstance, &Class::ConstMemberVoidFunction, ArgType{ 2 });
   //
   VECTORS_ARE_EQUAL((vector<ArgType>{ 1, 2 }), constClassInstance.calls);
}

TEST(CallCallNonConstMemberFunctionMemberFunction_CallsNonConstMemberFunction)
{
   Class nonConstClassInstance{};
   Utils::VoidOneArgMemberFunctionCaller<Class, ArgType> oneArgVoidMemberFunctionCaller{};
   IS_EMPTY(nonConstClassInstance.calls);
   //
   oneArgVoidMemberFunctionCaller.CallCallNonConstMemberFunctionMemberFunction(
      &nonConstClassInstance, &Class::NonConstMemberVoidFunction, ArgType{ 1 });
   //
   VECTORS_ARE_EQUAL(vector<ArgType>{ 1 }, nonConstClassInstance.calls);
   //
   oneArgVoidMemberFunctionCaller.CallCallNonConstMemberFunctionMemberFunction(
      &nonConstClassInstance, &Class::NonConstMemberVoidFunction, ArgType{ 2 });
   //
   VECTORS_ARE_EQUAL((vector<ArgType>{ 1, 2 }), nonConstClassInstance.calls);
}

RUN_TEMPLATE_TESTS(VoidOneArgMemberFunctionCallerTests, int)
THEN_RUN_TEMPLATE_TESTS(VoidOneArgMemberFunctionCallerTests, char)
