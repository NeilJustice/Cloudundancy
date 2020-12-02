#include "pch.h"
#include "libCloudundancy/UtilityComponents/FunctionCallers/MemberFunctions/VoidTwoArgMemberFunctionCaller.h"

template<typename Arg1Type, typename Arg2Type>
TEMPLATE_TESTS(VoidTwoArgMemberFunctionCallerTests, Arg1Type, Arg2Type)
AFACT(ConstCall_CallsConstMemberFunctionOnce)
AFACT(NonConstCall_CallsNonConstMemberFunctionOnce)
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

TEST(ConstCall_CallsConstMemberFunctionOnce)
{
   const Class constClassInstance;
   VoidTwoArgMemberFunctionCaller<Class, Arg1Type, Arg2Type> voidTwoArgMemberFunctionCaller;
   //
   voidTwoArgMemberFunctionCaller.ConstCall(&Class::ConstMemberFunction, &constClassInstance, Arg1Type{ 1 }, Arg2Type{ 2 });
   //
   vector<pair<Arg1Type, Arg2Type>> expectedFunctionCallArguments = { { Arg1Type{ 1 }, Arg2Type{ 2 } } };
   VECTORS_ARE_EQUAL(expectedFunctionCallArguments, constClassInstance.functionCallArguments);


   voidTwoArgMemberFunctionCaller.ConstCall(&Class::ConstMemberFunction, &constClassInstance, Arg1Type{ 3 }, Arg2Type{ 4 });
   //
   expectedFunctionCallArguments.emplace_back(Arg1Type{ 3 }, Arg2Type{ 4 });
   VECTORS_ARE_EQUAL(expectedFunctionCallArguments, constClassInstance.functionCallArguments);
}

TEST(NonConstCall_CallsNonConstMemberFunctionOnce)
{
   Class classInstance;
   VoidTwoArgMemberFunctionCaller<Class, Arg1Type, Arg2Type> voidTwoArgMemberFunctionCaller;
   //
   voidTwoArgMemberFunctionCaller.NonConstCall(&Class::NonConstMemberFunction, &classInstance, Arg1Type{ 1 }, Arg2Type{ 2 });
   //
   vector<pair<Arg1Type, Arg2Type>> expectedFunctionCallArguments = { { Arg1Type{ 1 }, Arg2Type{ 2 } } };
   VECTORS_ARE_EQUAL(expectedFunctionCallArguments, classInstance.functionCallArguments);


   voidTwoArgMemberFunctionCaller.NonConstCall(&Class::NonConstMemberFunction, &classInstance, Arg1Type{ 3 }, Arg2Type{ 4 });
   //
   expectedFunctionCallArguments.emplace_back(Arg1Type{ 3 }, Arg2Type{ 4 });
   VECTORS_ARE_EQUAL(expectedFunctionCallArguments, classInstance.functionCallArguments);
}

RUN_TEMPLATE_TESTS(VoidTwoArgMemberFunctionCallerTests, int, char)
THEN_RUN_TEMPLATE_TESTS(VoidTwoArgMemberFunctionCallerTests, int, unsigned long long)
