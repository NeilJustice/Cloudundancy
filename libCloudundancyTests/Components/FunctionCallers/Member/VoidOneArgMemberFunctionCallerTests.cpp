#include "pch.h"
#include "libCloudundancy/Components/FunctionCallers/Member/VoidOneArgMemberFunctionCaller.h"

template<typename ArgType>
TEMPLATE_TESTS(VoidOneArgMemberFunctionCallerTests, ArgType)
AFACT(ConstCall_CallsConstMemberFunction)
AFACT(NonConstCall_CallsNonConstMemberFunction)
EVIDENCE

struct C
{
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

TEST(ConstCall_CallsConstMemberFunction)
{
   C c;
   VoidOneArgMemberFunctionCaller<C, ArgType> oneArgVoidMemberFunctionCaller;
   IS_EMPTY(c.calls);
   //
   oneArgVoidMemberFunctionCaller.ConstCall(&c, &C::ConstMemberVoidFunction, ArgType{ 1 });
   //
   VECTORS_ARE_EQUAL(vector<ArgType>{ 1 }, c.calls);
   //
   oneArgVoidMemberFunctionCaller.ConstCall(&c, &C::ConstMemberVoidFunction, ArgType{ 2 });
   //
   VECTORS_ARE_EQUAL((vector<ArgType>{ 1, 2 }), c.calls);
}

TEST(NonConstCall_CallsNonConstMemberFunction)
{
   C c;
   VoidOneArgMemberFunctionCaller<C, ArgType> oneArgVoidMemberFunctionCaller;
   IS_EMPTY(c.calls);
   //
   oneArgVoidMemberFunctionCaller.NonConstCall(&c, &C::NonConstMemberVoidFunction, ArgType{ 1 });
   //
   VECTORS_ARE_EQUAL(vector<ArgType>{ 1 }, c.calls);
   //
   oneArgVoidMemberFunctionCaller.NonConstCall(&c, &C::NonConstMemberVoidFunction, ArgType{ 2 });
   //
   VECTORS_ARE_EQUAL((vector<ArgType>{ 1, 2 }), c.calls);
}

RUN_TEMPLATE_TESTS(VoidOneArgMemberFunctionCallerTests, int)
THEN_RUN_TEMPLATE_TESTS(VoidOneArgMemberFunctionCallerTests, char)
