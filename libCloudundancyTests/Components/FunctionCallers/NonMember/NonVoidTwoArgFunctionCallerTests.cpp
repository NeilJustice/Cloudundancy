#include "pch.h"
#include "libCloudundancy/Components/FunctionCallers/NonMember/NonVoidTwoArgFunctionCaller.h"

template<typename ReturnType, typename Arg1Type, typename Arg2Type>
TEMPLATE_TESTS(NonVoidTwoArgFunctionCallerTests, ReturnType, Arg1Type, Arg2Type)
AFACT(Call_CallsNonVoidFunctionOnce_ReturnsReturnValue)
EVIDENCE

static vector<pair<Arg1Type, Arg2Type>> _functionCalls;
static ReturnType _returnedReturnValue;

static ReturnType NonVoidTwoArgFunction(Arg1Type arg1, Arg2Type arg2)
{
   _functionCalls.emplace_back(arg1, arg2);
   _returnedReturnValue = ZenUnit::Random<ReturnType>();
   return _returnedReturnValue;
}

NonVoidTwoArgFunctionCaller<ReturnType, Arg1Type, Arg2Type> _nonVoidTwoArgFunctionCaller;

CLEANUP
{
   _functionCalls.clear();
   _returnedReturnValue = ReturnType();
}

TEST(Call_CallsNonVoidFunctionOnce_ReturnsReturnValue)
{
   const Arg1Type arg1 = ZenUnit::Random<Arg1Type>();
   const Arg2Type arg2 = ZenUnit::Random<Arg2Type>();
   //
   const ReturnType returnValue = _nonVoidTwoArgFunctionCaller.Call(NonVoidTwoArgFunction, arg1, arg2);
   //
   const vector<pair<Arg1Type, Arg2Type>> expectedFunctionCalls =
   {
      { arg1, arg2 }
   };
   VECTORS_ARE_EQUAL(expectedFunctionCalls, _functionCalls);
   ARE_EQUAL(_returnedReturnValue, returnValue);
}

RUN_TEMPLATE_TESTS(NonVoidTwoArgFunctionCallerTests, char, int, int)
THEN_RUN_TEMPLATE_TESTS(NonVoidTwoArgFunctionCallerTests, int, double, unsigned)

template<typename ReturnType, typename Arg1Type, typename Arg2Type>
vector<pair<Arg1Type, Arg2Type>> NonVoidTwoArgFunctionCallerTests<ReturnType, Arg1Type, Arg2Type>::_functionCalls;

template<typename ReturnType, typename Arg1Type, typename Arg2Type>
ReturnType NonVoidTwoArgFunctionCallerTests<ReturnType, Arg1Type, Arg2Type>::_returnedReturnValue;
