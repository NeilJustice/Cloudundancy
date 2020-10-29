#include "pch.h"
#include "libCloudundancy/Components/FunctionCallers/Member/VoidOneArgMemberFunctionCaller.h"

template<typename ArgType>
TEMPLATE_TESTS(VoidOneArgMemberFunctionCallerTests, ArgType)
AFACT(ConstCall_CallsConstMemberFunction)
AFACT(NonConstCall_CallsNonConstMemberFunction)
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

TEST(ConstCall_CallsConstMemberFunction)
{
   Class c;
   VoidOneArgMemberFunctionCaller<Class, ArgType> oneArgVoidMemberFunctionCaller;
   IS_EMPTY(c.calls);
   //
   oneArgVoidMemberFunctionCaller.ConstCall(&c, &Class::ConstMemberVoidFunction, ArgType{ 1 });
   //
   VECTORS_ARE_EQUAL(vector<ArgType>{ 1 }, c.calls);
   //
   oneArgVoidMemberFunctionCaller.ConstCall(&c, &Class::ConstMemberVoidFunction, ArgType{ 2 });
   //
   VECTORS_ARE_EQUAL((vector<ArgType>{ 1, 2 }), c.calls);
}

TEST(NonConstCall_CallsNonConstMemberFunction)
{
   Class c;
   VoidOneArgMemberFunctionCaller<Class, ArgType> oneArgVoidMemberFunctionCaller;
   IS_EMPTY(c.calls);
   //
   oneArgVoidMemberFunctionCaller.NonConstCall(&c, &Class::NonConstMemberVoidFunction, ArgType{ 1 });
   //
   VECTORS_ARE_EQUAL(vector<ArgType>{ 1 }, c.calls);
   //
   oneArgVoidMemberFunctionCaller.NonConstCall(&c, &Class::NonConstMemberVoidFunction, ArgType{ 2 });
   //
   VECTORS_ARE_EQUAL((vector<ArgType>{ 1, 2 }), c.calls);
}

RUN_TEMPLATE_TESTS(VoidOneArgMemberFunctionCallerTests, int)
THEN_RUN_TEMPLATE_TESTS(VoidOneArgMemberFunctionCallerTests, char)
