#include "pch.h"
#include "libCloudundancy/Components/FunctionCallers/NonMember/VoidTwoArgFunctionCaller.h"

template<typename Arg1Type, typename Arg2Type>
TEMPLATE_TESTS(VoidTwoArgFunctionCallerTests, Arg1Type, Arg2Type)
AFACT(Call_CallsFunctionOnce)
EVIDENCE

static vector<pair<Arg1Type, Arg2Type>> _functionCalls;

static void VoidTwoArgFunction(Arg1Type arg1, Arg2Type arg2)
{
   _functionCalls.emplace_back(arg1, arg2);
}

CLEANUP
{
   _functionCalls.clear();
}

TEST(Call_CallsFunctionOnce)
{
   VoidTwoArgFunctionCaller<Arg1Type, Arg2Type> voidTwoArgFunctionCaller;

   voidTwoArgFunctionCaller.Call(VoidTwoArgFunction, Arg1Type{ 1 }, Arg2Type{ 2 });
   vector<pair<Arg1Type, Arg2Type>> expectedFunctionCalls = { { Arg1Type{ 1 }, Arg2Type{ 2 } } };
   VECTORS_ARE_EQUAL(expectedFunctionCalls, _functionCalls);

   voidTwoArgFunctionCaller.Call(VoidTwoArgFunction, Arg1Type{ 3 }, Arg2Type{ 4 });
   expectedFunctionCalls.emplace_back(Arg1Type{ 3 }, Arg2Type{ 4 });
   VECTORS_ARE_EQUAL(expectedFunctionCalls, _functionCalls);
}

RUN_TEMPLATE_TESTS(VoidTwoArgFunctionCallerTests, int, char)
THEN_RUN_TEMPLATE_TESTS(VoidTwoArgFunctionCallerTests, int, unsigned long long)

template<typename Arg1Type, typename Arg2Type>
vector<pair<Arg1Type, Arg2Type>> VoidTwoArgFunctionCallerTests<Arg1Type, Arg2Type>::_functionCalls;
