#include "pch.h"
#include "libCloudundancy/Components/Function/Member/NonVoidZeroArgMemberFunctionCaller.h"

template<typename ReturnType>
TEMPLATE_TESTS(NonVoidZeroArgMemberFunctionCallerTests, ReturnType)
AFACT(ConstCall_CallsConstMemberFunctionOnce_ReturnsReturnValue)
AFACT(NonConstCall_CallsNonConstMemberFunctionOnce_ReturnsReturnValue)
EVIDENCE

class C
{
public:
   mutable unsigned numberOfCalls = 0;
   mutable ReturnType returnValue;

   ReturnType ConstFunction() const
   {
      ++numberOfCalls;
      returnValue = ZenUnit::Random<ReturnType>();
      return returnValue;
   }

   ReturnType NonConstFunction()
   {
      ++numberOfCalls;
      returnValue = ZenUnit::Random<ReturnType>();
      return returnValue;
   }
};

NonVoidZeroArgMemberFunctionCaller<ReturnType, C> _nonVoidZeroArgMemberFunctionCaller;

TEST(ConstCall_CallsConstMemberFunctionOnce_ReturnsReturnValue)
{
   C c{};
   //
   const ReturnType returnValue1 = _nonVoidZeroArgMemberFunctionCaller.ConstCall(&c, &C::ConstFunction);
   //
   ARE_EQUAL(1, c.numberOfCalls);
   ARE_EQUAL(c.returnValue, returnValue1);


   const ReturnType returnValue2 = _nonVoidZeroArgMemberFunctionCaller.ConstCall(&c, &C::ConstFunction);
   //
   ARE_EQUAL(2, c.numberOfCalls);
   ARE_EQUAL(c.returnValue, returnValue2);
}

TEST(NonConstCall_CallsNonConstMemberFunctionOnce_ReturnsReturnValue)
{
   C c{};
   //
   const ReturnType returnValue1 = _nonVoidZeroArgMemberFunctionCaller.NonConstCall(&c, &C::NonConstFunction);
   //
   ARE_EQUAL(1, c.numberOfCalls);
   ARE_EQUAL(c.returnValue, returnValue1);


   const ReturnType returnValue2 = _nonVoidZeroArgMemberFunctionCaller.NonConstCall(&c, &C::NonConstFunction);
   //
   ARE_EQUAL(2, c.numberOfCalls);
   ARE_EQUAL(c.returnValue, returnValue2);
}

RUN_TEMPLATE_TESTS(NonVoidZeroArgMemberFunctionCallerTests, int)
THEN_RUN_TEMPLATE_TESTS(NonVoidZeroArgMemberFunctionCallerTests, double)
