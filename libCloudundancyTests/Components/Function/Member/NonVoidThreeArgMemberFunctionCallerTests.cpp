#include "pch.h"
#include "libCloudundancy/Components/Function/Member/NonVoidThreeArgMemberFunctionCaller.h"

template<typename ReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
TEMPLATE_TESTS(NonVoidThreeArgMemberFunctionCallerTests, ReturnType, Arg1Type, Arg2Type, Arg3Type)
AFACT(ConstCall_CallsNonVoidConstMemberFunctionOnce_ReturnsReturnValue)
AFACT(NonConstCall_CallsNonVoidNonConstMemberFunctionOnce_ReturnsReturnValue)
EVIDENCE

class Class
{
public:
   mutable vector<tuple<Arg1Type, Arg2Type, Arg3Type>> calls;
   mutable ReturnType returnValue = {};

   ReturnType NonVoidConstMemberFunction(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3) const
   {
      calls.emplace_back(arg1, arg2, arg3);
      returnValue = ZenUnit::Random<ReturnType>();
      return returnValue;
   }

   ReturnType NonVoidNonConstMemberFunction(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3)
   {
      calls.emplace_back(arg1, arg2, arg3);
      returnValue = ZenUnit::Random<ReturnType>();
      return returnValue;
   }
};

NonVoidThreeArgMemberFunctionCaller<
   ReturnType, Class, Arg1Type, Arg2Type, Arg3Type> _nonVoidThreeArgMemberFunctionCaller;
Arg1Type _arg1 = {};
Arg2Type _arg2 = {};
Arg3Type _arg3 = {};

STARTUP
{
   _arg1 = ZenUnit::Random<Arg1Type>();
   _arg2 = ZenUnit::Random<Arg2Type>();
   _arg3 = ZenUnit::Random<Arg3Type>();
}

TEST(ConstCall_CallsNonVoidConstMemberFunctionOnce_ReturnsReturnValue)
{
   const Class classInstance;
   //
   const ReturnType returnValue = _nonVoidThreeArgMemberFunctionCaller.ConstCall(
      &classInstance, &Class::NonVoidConstMemberFunction, _arg1, _arg2, _arg3);
   //
   const vector<tuple<Arg1Type, Arg2Type, Arg3Type>> expectedCalls =
   {
      { _arg1, _arg2, _arg3 }
   };
   VECTORS_ARE_EQUAL(expectedCalls, classInstance.calls);
   ARE_EQUAL(classInstance.returnValue, returnValue);
}

TEST(NonConstCall_CallsNonVoidNonConstMemberFunctionOnce_ReturnsReturnValue)
{
   Class classInstance;
   //
   const ReturnType returnValue = _nonVoidThreeArgMemberFunctionCaller.NonConstCall(
      &classInstance, &Class::NonVoidNonConstMemberFunction, _arg1, _arg2, _arg3);
   //
   const vector<tuple<Arg1Type, Arg2Type, Arg3Type>> expectedCalls =
   {
      { _arg1, _arg2, _arg3 }
   };
   VECTORS_ARE_EQUAL(expectedCalls, classInstance.calls);
   ARE_EQUAL(classInstance.returnValue, returnValue);
}

RUN_TEMPLATE_TESTS(NonVoidThreeArgMemberFunctionCallerTests, char, int, int, int)
THEN_RUN_TEMPLATE_TESTS(NonVoidThreeArgMemberFunctionCallerTests, int, double, unsigned, int)
