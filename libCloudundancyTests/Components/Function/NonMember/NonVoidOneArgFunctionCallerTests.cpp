#include "pch.h"
#include "libCloudundancy/Components/Function/NonMember/NonVoidOneArgFunctionCaller.h"

template<typename ReturnType, typename ArgType>
TEMPLATE_TESTS(NonVoidOneArgFunctionCallerTests, ReturnType, ArgType)
AFACT(Call_CallsFunctionOnce_ReturnsReturnValue)
EVIDENCE

NonVoidOneArgFunctionCallerTests()
{
}

static vector<ArgType> _functionCalls;
static ReturnType _returnedReturnValue;

static ReturnType NonVoidOneArgFunction(ArgType arg)
{
   _functionCalls.push_back(arg);
   _returnedReturnValue = ZenUnit::Random<ReturnType>();
   return _returnedReturnValue;
}

const NonVoidOneArgFunctionCaller<ReturnType, ArgType> _nonVoidOneArgFunctionCaller;

CLEANUP
{
   _functionCalls.clear();
   _returnedReturnValue = ReturnType();
}

TEST(Call_CallsFunctionOnce_ReturnsReturnValue)
{
   const ArgType arg = ZenUnit::Random<ArgType>();
   //
   const ReturnType returnValue = _nonVoidOneArgFunctionCaller.Call(NonVoidOneArgFunction, arg);
   //
   VECTORS_ARE_EQUAL(_functionCalls, vector<ArgType>{arg});
   ARE_EQUAL(_returnedReturnValue, returnValue);
}

RUN_TEMPLATE_TESTS(NonVoidOneArgFunctionCallerTests, char, int)
THEN_RUN_TEMPLATE_TESTS(NonVoidOneArgFunctionCallerTests, int, double)

template<typename ReturnType, typename ArgType>
vector<ArgType> NonVoidOneArgFunctionCallerTests<ReturnType, ArgType>::_functionCalls;

template<typename ReturnType, typename ArgType>
ReturnType NonVoidOneArgFunctionCallerTests<ReturnType, ArgType>::_returnedReturnValue;
