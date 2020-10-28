#include "pch.h"
#include "libCloudundancy/Components/FunctionCallers/Member/NonVoidTwoArgMemberFunctionCaller.h"

template<typename ReturnType, typename Arg1Type, typename Arg2Type>
TEMPLATE_TESTS(NonVoidTwoArgMemberFunctionCallerTests, ReturnType, Arg1Type, Arg2Type)
AFACT(ConstCall_CallsNonVoidConstMemberFunctionOnce_ReturnsReturnValue)
AFACT(NonConstCall_CallsNonVoidNonConstMemberFunctionOnce_ReturnsReturnValue)
EVIDENCE

class Class
{
public:
   mutable vector<pair<Arg1Type, Arg2Type>> calls;
   mutable ReturnType returnValue = {};

   ReturnType NonVoidConstMemberFunction(Arg1Type arg1, Arg2Type arg2) const
   {
      calls.emplace_back(arg1, arg2);
      returnValue = ZenUnit::Random<ReturnType>();
      return returnValue;
   }

   ReturnType NonVoidNonConstMemberFunction(Arg1Type arg1, Arg2Type arg2)
   {
      calls.emplace_back(arg1, arg2);
      returnValue = ZenUnit::Random<ReturnType>();
      return returnValue;
   }
};

NonVoidTwoArgMemberFunctionCaller<
   ReturnType, Class, Arg1Type, Arg2Type> _nonVoidTwoArgMemberFunctionCaller;
Arg1Type _arg1 = {};
Arg2Type _arg2 = {};

STARTUP
{
   _arg1 = ZenUnit::Random<Arg1Type>();
   _arg2 = ZenUnit::Random<Arg2Type>();
}

TEST(ConstCall_CallsNonVoidConstMemberFunctionOnce_ReturnsReturnValue)
{
   const Class classInstance;
   //
   const ReturnType returnValue = _nonVoidTwoArgMemberFunctionCaller.ConstCall(
      &classInstance, &Class::NonVoidConstMemberFunction, _arg1, _arg2);
   //
   const vector<pair<Arg1Type, Arg2Type>> expectedCalls =
   {
      { _arg1, _arg2 }
   };
   VECTORS_ARE_EQUAL(expectedCalls, classInstance.calls);
   ARE_EQUAL(classInstance.returnValue, returnValue);
}

TEST(NonConstCall_CallsNonVoidNonConstMemberFunctionOnce_ReturnsReturnValue)
{
   Class classInstance;
   //
   const ReturnType returnValue = _nonVoidTwoArgMemberFunctionCaller.NonConstCall(
      &classInstance, &Class::NonVoidNonConstMemberFunction, _arg1, _arg2);
   //
   const vector<pair<Arg1Type, Arg2Type>> expectedCalls =
   {
      { _arg1, _arg2 }
   };
   VECTORS_ARE_EQUAL(expectedCalls, classInstance.calls);
   ARE_EQUAL(classInstance.returnValue, returnValue);
}

RUN_TEMPLATE_TESTS(NonVoidTwoArgMemberFunctionCallerTests, char, int, int)
THEN_RUN_TEMPLATE_TESTS(NonVoidTwoArgMemberFunctionCallerTests, int, double, unsigned)
