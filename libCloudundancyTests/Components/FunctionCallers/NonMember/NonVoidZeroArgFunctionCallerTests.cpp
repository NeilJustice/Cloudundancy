#include "pch.h"
#include "libCloudundancy/Components/FunctionCallers/NonMember/NonVoidZeroArgFunctionCaller.h"

template<typename ReturnType>
TEMPLATE_TESTS(NonVoidZeroArgFunctionCallerTests, ReturnType)
AFACT(Call_CallsFunctionOnce_ReturnsReturnValue)
EVIDENCE

static unsigned _numberOfFunctionCalls;
static ReturnType _returnedReturnValue;

static ReturnType NonVoidZeroArgFunction()
{
   ++_numberOfFunctionCalls;
   _returnedReturnValue = ZenUnit::Random<ReturnType>();
   return _returnedReturnValue;
}

CLEANUP
{
   _numberOfFunctionCalls = 0;
   _returnedReturnValue = ReturnType();
}

NonVoidZeroArgFunctionCaller<ReturnType> _nonVoidZeroArgFunctionCaller;

TEST(Call_CallsFunctionOnce_ReturnsReturnValue)
{
   const ReturnType returnValue1 = _nonVoidZeroArgFunctionCaller.Call(NonVoidZeroArgFunction);
   ARE_EQUAL(1, _numberOfFunctionCalls);
   ARE_EQUAL(_returnedReturnValue, returnValue1);

   const ReturnType returnValue2 = _nonVoidZeroArgFunctionCaller.Call(NonVoidZeroArgFunction);
   ARE_EQUAL(2, _numberOfFunctionCalls);
   ARE_EQUAL(_returnedReturnValue, returnValue2);
}

RUN_TEMPLATE_TESTS(NonVoidZeroArgFunctionCallerTests, int)
THEN_RUN_TEMPLATE_TESTS(NonVoidZeroArgFunctionCallerTests, double)

template<typename ReturnType>
unsigned NonVoidZeroArgFunctionCallerTests<ReturnType>::_numberOfFunctionCalls;

template<typename ReturnType>
ReturnType NonVoidZeroArgFunctionCallerTests<ReturnType>::_returnedReturnValue;
