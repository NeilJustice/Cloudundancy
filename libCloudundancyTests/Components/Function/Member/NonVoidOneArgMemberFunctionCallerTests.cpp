#include "pch.h"
#include "libCloudundancy/Components/Function/Member/NonVoidOneArgMemberFunctionCaller.h"

template<typename ReturnType, typename ArgType>
TEMPLATE_TESTS(NonVoidOneArgMemberFunctionCallerTests, ReturnType, ArgType)
AFACT(CallConstMemberFunction_CallsConstMemberFunctionOnce_ReturnsReturnValue)
AFACT(CallNonConstMemberFunction_CallsNonConstMemberFunctionOnce_ReturnsReturnValue)
EVIDENCE

NonVoidOneArgMemberFunctionCallerTests()
{
}

class Class
{
public:
   mutable vector<ArgType> args;
   mutable ReturnType returnValue;

   ReturnType ConstMemberFunction(ArgType arg) const
   {
      args.push_back(arg);
      returnValue = ZenUnit::Random<ReturnType>();
      return returnValue;
   }

	ReturnType NonConstMemberFunction(ArgType arg)
   {
      args.push_back(arg);
      returnValue = ZenUnit::Random<ReturnType>();
      return returnValue;
   }
};

const NonVoidOneArgMemberFunctionCaller<ReturnType, Class, ArgType> _nonVoidOneArgMemberFunctionCaller;

TEST(CallConstMemberFunction_CallsConstMemberFunctionOnce_ReturnsReturnValue)
{
   const Class constInstance{};
   const ArgType arg = ZenUnit::Random<ArgType>();
   //
   const ReturnType returnValue = _nonVoidOneArgMemberFunctionCaller.CallConstMemberFunction(
      &Class::ConstMemberFunction, &constInstance, arg);
   //
   VECTORS_ARE_EQUAL(vector<ArgType>{arg}, constInstance.args);
   ARE_EQUAL(constInstance.returnValue, returnValue);
}

TEST(CallNonConstMemberFunction_CallsNonConstMemberFunctionOnce_ReturnsReturnValue)
{
   Class nonConstInstance{};
   const ArgType arg = ZenUnit::Random<ArgType>();
   //
   const ReturnType returnValue = _nonVoidOneArgMemberFunctionCaller.CallNonConstMemberFunction(
      &Class::NonConstMemberFunction, &nonConstInstance, arg);
   //
   VECTORS_ARE_EQUAL(vector<ArgType>{arg}, nonConstInstance.args);
   ARE_EQUAL(nonConstInstance.returnValue, returnValue);
}

RUN_TEMPLATE_TESTS(NonVoidOneArgMemberFunctionCallerTests, char, int)
THEN_RUN_TEMPLATE_TESTS(NonVoidOneArgMemberFunctionCallerTests, int, double)
