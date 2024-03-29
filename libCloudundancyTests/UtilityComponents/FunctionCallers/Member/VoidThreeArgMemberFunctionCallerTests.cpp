#include "pch.h"
#include "libCloudundancy/UtilityComponents/FunctionCallers/Member/VoidThreeArgMemberFunctionCaller.h"

template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
TEMPLATE_TESTS(VoidThreeArgMemberFunctionCallerTests, Arg1Type, Arg2Type, Arg3Type)
AFACT(CallConstMemberFunction_CallsConstMemberFunctionOnce)
AFACT(CallNonConstMemberFunction_CallsNonConstMemberFunctionOnce)
EVIDENCE

class Class
{
public:
   mutable vector<tuple<Arg1Type, Arg2Type, Arg3Type>> calls;

   void ConstMemberFunction(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3) const
   {
      calls.emplace_back(arg1, arg2, arg3);
   }

   void NonConstMemberFunction(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3)
   {
      calls.emplace_back(arg1, arg2, arg3);
   }
};

TEST(CallConstMemberFunction_CallsConstMemberFunctionOnce)
{
   const Class constClassInstance{};
   Utils::VoidThreeArgMemberFunctionCaller<Class, Arg1Type, Arg2Type, Arg3Type> voidThreeArgMemberFunctionCaller;
   //
   voidThreeArgMemberFunctionCaller.CallConstMemberFunction(
      &constClassInstance, &Class::ConstMemberFunction, Arg1Type{ 1 }, Arg2Type{ 2 }, Arg3Type{ 3 });
   //
   vector<tuple<Arg1Type, Arg2Type, Arg3Type>> expectedCalls = { { Arg1Type{ 1 }, Arg2Type{ 2 }, Arg3Type{ 3 } } };
   VECTORS_ARE_EQUAL(expectedCalls, constClassInstance.calls);


   voidThreeArgMemberFunctionCaller.CallConstMemberFunction(
      &constClassInstance, &Class::ConstMemberFunction, Arg1Type{ 3 }, Arg2Type{ 4 }, Arg3Type{ 5 });
   //
   expectedCalls.emplace_back(Arg1Type{ 3 }, Arg2Type{ 4 }, Arg3Type{ 5 });
   VECTORS_ARE_EQUAL(expectedCalls, constClassInstance.calls);
}

TEST(CallNonConstMemberFunction_CallsNonConstMemberFunctionOnce)
{
   Class nonConstClassInstance{};
   Utils::VoidThreeArgMemberFunctionCaller<Class, Arg1Type, Arg2Type, Arg3Type> voidThreeArgMemberFunctionCaller;
   //
   voidThreeArgMemberFunctionCaller.CallNonConstMemberFunction(
      &nonConstClassInstance, &Class::NonConstMemberFunction, Arg1Type{ 1 }, Arg2Type{ 2 }, Arg3Type{ 3 });
   //
   vector<tuple<Arg1Type, Arg2Type, Arg3Type>> expectedCalls = { { Arg1Type{ 1 }, Arg2Type{ 2 }, Arg3Type{ 3 } } };
   VECTORS_ARE_EQUAL(expectedCalls, nonConstClassInstance.calls);


   voidThreeArgMemberFunctionCaller.CallNonConstMemberFunction(
      &nonConstClassInstance, &Class::NonConstMemberFunction, Arg1Type{ 3 }, Arg2Type{ 4 }, Arg3Type{ 5 });
   //
   expectedCalls.emplace_back(Arg1Type{ 3 }, Arg2Type{ 4 }, Arg3Type{ 5 });
   VECTORS_ARE_EQUAL(expectedCalls, nonConstClassInstance.calls);
}

RUN_TEMPLATE_TESTS(VoidThreeArgMemberFunctionCallerTests, int, char, unsigned)
THEN_RUN_TEMPLATE_TESTS(VoidThreeArgMemberFunctionCallerTests, int, unsigned long long, char)
