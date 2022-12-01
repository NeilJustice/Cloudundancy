#include "pch.h"
#include "libCloudundancy/UtilityComponents/FunctionCallers/Member/VoidTwoArgMemberFunctionCaller.h"

template<typename Arg1Type, typename Arg2Type>
TEMPLATE_TESTS(VoidTwoArgMemberFunctionCallerTests, Arg1Type, Arg2Type)
AFACT(CallConstMemberFunction_CallsConstMemberFunctionOnce)
AFACT(CallNonConstMemberFunction_CallsNonConstMemberFunctionOnce)
EVIDENCE

class Class
{
public:
   mutable vector<pair<Arg1Type, Arg2Type>> functionCallArguments;

   void ConstMemberFunction(Arg1Type arg1, Arg2Type arg2) const
   {
      functionCallArguments.emplace_back(arg1, arg2);
   }

   void NonConstMemberFunction(Arg1Type arg1, Arg2Type arg2)
   {
      functionCallArguments.emplace_back(arg1, arg2);
   }
};

TEST(CallConstMemberFunction_CallsConstMemberFunctionOnce)
{
   const Class constClassInstance{};
   Utils::VoidTwoArgMemberFunctionCaller<Class, Arg1Type, Arg2Type> voidTwoArgMemberFunctionCaller;
   //
   voidTwoArgMemberFunctionCaller.CallConstMemberFunction(
      &constClassInstance, &Class::ConstMemberFunction, Arg1Type{ 1 }, Arg2Type{ 2 });
   //
   vector<pair<Arg1Type, Arg2Type>> expectedFunctionCallArguments = { { Arg1Type{ 1 }, Arg2Type{ 2 } } };
   VECTORS_ARE_EQUAL(expectedFunctionCallArguments, constClassInstance.functionCallArguments);


   voidTwoArgMemberFunctionCaller.CallConstMemberFunction(
      &constClassInstance, &Class::ConstMemberFunction, Arg1Type{ 3 }, Arg2Type{ 4 });
   //
   expectedFunctionCallArguments.emplace_back(Arg1Type{ 3 }, Arg2Type{ 4 });
   VECTORS_ARE_EQUAL(expectedFunctionCallArguments, constClassInstance.functionCallArguments);
}

TEST(CallNonConstMemberFunction_CallsNonConstMemberFunctionOnce)
{
   Class nonConstClassInstance{};
   Utils::VoidTwoArgMemberFunctionCaller<Class, Arg1Type, Arg2Type> voidTwoArgMemberFunctionCaller;
   //
   voidTwoArgMemberFunctionCaller.CallNonConstMemberFunction(
      &nonConstClassInstance, &Class::NonConstMemberFunction, Arg1Type{ 1 }, Arg2Type{ 2 });
   //
   vector<pair<Arg1Type, Arg2Type>> expectedFunctionCallArguments = { { Arg1Type{ 1 }, Arg2Type{ 2 } } };
   VECTORS_ARE_EQUAL(expectedFunctionCallArguments, nonConstClassInstance.functionCallArguments);


   voidTwoArgMemberFunctionCaller.CallNonConstMemberFunction(
      &nonConstClassInstance, &Class::NonConstMemberFunction, Arg1Type{ 3 }, Arg2Type{ 4 });
   //
   expectedFunctionCallArguments.emplace_back(Arg1Type{ 3 }, Arg2Type{ 4 });
   VECTORS_ARE_EQUAL(expectedFunctionCallArguments, nonConstClassInstance.functionCallArguments);
}

RUN_TEMPLATE_TESTS(VoidTwoArgMemberFunctionCallerTests, int, char)
THEN_RUN_TEMPLATE_TESTS(VoidTwoArgMemberFunctionCallerTests, int, unsigned long long)
