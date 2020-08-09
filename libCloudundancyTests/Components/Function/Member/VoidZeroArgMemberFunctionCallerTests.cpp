#include "pch.h"
#include "libCloudundancy/Components/Function/Member/VoidZeroArgMemberFunctionCaller.h"

TESTS(VoidZeroArgMemberFunctionCallerTests)
AFACT(ConstCall_CallsConstMemberFunction)
AFACT(NonConstCall_CallsNonConstMemberFunction)
EVIDENCE

struct ConstClass
{
   mutable unsigned numberOfCalls = 0;

   void ConstMemberVoidFunction() const
   {
      ++numberOfCalls;
   }
};

struct NonConstClass
{
   unsigned numberOfCalls = 0;

   void NonConstMemberVoidFunction()
   {
      ++numberOfCalls;
   }
};

TEST(ConstCall_CallsConstMemberFunction)
{
   ConstClass c;
   VoidZeroArgMemberFunctionCaller<ConstClass> voidZeroArgMemberFunctionCaller;
   ARE_EQUAL(0, c.numberOfCalls);
   //
   voidZeroArgMemberFunctionCaller.ConstCall(&c, &ConstClass::ConstMemberVoidFunction);
   //
   ARE_EQUAL(1, c.numberOfCalls);
   //
   voidZeroArgMemberFunctionCaller.ConstCall(&c, &ConstClass::ConstMemberVoidFunction);
   //
   ARE_EQUAL(2, c.numberOfCalls);
}

TEST(NonConstCall_CallsNonConstMemberFunction)
{
   NonConstClass c;
   VoidZeroArgMemberFunctionCaller<NonConstClass> voidZeroArgMemberFunctionCaller;
   ARE_EQUAL(0, c.numberOfCalls);
   //
   voidZeroArgMemberFunctionCaller.NonConstCall(&c, &NonConstClass::NonConstMemberVoidFunction);
   //
   ARE_EQUAL(1, c.numberOfCalls);
   //
   voidZeroArgMemberFunctionCaller.NonConstCall(&c, &NonConstClass::NonConstMemberVoidFunction);
   //
   ARE_EQUAL(2, c.numberOfCalls);
}

RUN_TESTS(VoidZeroArgMemberFunctionCallerTests)
