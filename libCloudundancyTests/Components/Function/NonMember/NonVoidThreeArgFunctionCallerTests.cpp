#include "pch.h"
#include "libCloudundancy/Components/Function/NonMember/NonVoidThreeArgFunctionCaller.h"

template<typename ReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
TEMPLATE_TESTS(NonVoidThreeArgFunctionCallerTests, ReturnType, Arg1Type, Arg2Type, Arg3Type)
AFACT(Call_CallsNonVoidFunctionOnce_ReturnsReturnValue)
EVIDENCE

static vector<tuple<Arg1Type, Arg2Type, Arg3Type>> _functionCalls;
static ReturnType _returnedReturnValue;

static ReturnType NonVoidThreeArgFunction(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3)
{
   _functionCalls.emplace_back(arg1, arg2, arg3);
   _returnedReturnValue = ZenUnit::Random<ReturnType>();
   return _returnedReturnValue;
}

NonVoidThreeArgFunctionCaller<ReturnType, Arg1Type, Arg2Type, Arg3Type> _nonVoidThreeArgFunctionCaller;

CLEANUP
{
   _functionCalls.clear();
   _returnedReturnValue = ReturnType();
}

TEST(Call_CallsNonVoidFunctionOnce_ReturnsReturnValue)
{
   const Arg1Type arg1 = ZenUnit::Random<Arg1Type>();
   const Arg2Type arg2 = ZenUnit::Random<Arg2Type>();
   const Arg3Type arg3 = ZenUnit::Random<Arg3Type>();
   //
   const ReturnType returnValue = _nonVoidThreeArgFunctionCaller.Call(NonVoidThreeArgFunction, arg1, arg2, arg3);
   //
   const vector<tuple<Arg1Type, Arg2Type, Arg3Type>> expectedFunctionCalls =
   {
      { arg1, arg2, arg3 }
   };
   VECTORS_ARE_EQUAL(expectedFunctionCalls, _functionCalls);
   ARE_EQUAL(_returnedReturnValue, returnValue);
}

RUN_TEMPLATE_TESTS(NonVoidThreeArgFunctionCallerTests, char, int, int, int)
THEN_RUN_TEMPLATE_TESTS(NonVoidThreeArgFunctionCallerTests, int, double, unsigned, int)

template<typename ReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
vector<tuple<Arg1Type, Arg2Type, Arg3Type>> NonVoidThreeArgFunctionCallerTests<ReturnType, Arg1Type, Arg2Type, Arg3Type>::_functionCalls;

template<typename ReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
ReturnType NonVoidThreeArgFunctionCallerTests<ReturnType, Arg1Type, Arg2Type, Arg3Type>::_returnedReturnValue;
