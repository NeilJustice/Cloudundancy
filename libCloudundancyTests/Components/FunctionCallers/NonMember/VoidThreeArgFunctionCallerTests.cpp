#include "pch.h"
#include "libCloudundancy/Components/FunctionCallers/NonMember/VoidThreeArgFunctionCaller.h"

template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
TEMPLATE_TESTS(VoidThreeArgFunctionCallerTests, Arg1Type, Arg2Type, Arg3Type)
AFACT(Call_CallsFunctionOnce)
EVIDENCE

static vector<tuple<Arg1Type, Arg2Type, Arg3Type>> _functionCalls;

static void VoidThreeArgFunction(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3)
{
   _functionCalls.emplace_back(arg1, arg2, arg3);
}

CLEANUP
{
   _functionCalls.clear();
}

TEST(Call_CallsFunctionOnce)
{
   VoidThreeArgFunctionCaller<Arg1Type, Arg2Type, Arg3Type> voidThreeArgFunctionCaller;

   voidThreeArgFunctionCaller.Call(VoidThreeArgFunction, Arg1Type{ 1 }, Arg2Type{ 2 }, Arg3Type{ 3 });
   vector<tuple<Arg1Type, Arg2Type, Arg3Type>> expectedCalls = { { Arg1Type{ 1 }, Arg2Type{ 2 }, Arg3Type{ 3 } } };
   VECTORS_ARE_EQUAL(expectedCalls, _functionCalls);

   voidThreeArgFunctionCaller.Call(VoidThreeArgFunction, Arg1Type{ 3 }, Arg2Type{ 4 }, Arg3Type{ 5 });
   expectedCalls.emplace_back(Arg1Type{ 3 }, Arg2Type{ 4 }, Arg3Type{ 5 });
   VECTORS_ARE_EQUAL(expectedCalls, _functionCalls);
}

RUN_TEMPLATE_TESTS(VoidThreeArgFunctionCallerTests, int, char, unsigned)
THEN_RUN_TEMPLATE_TESTS(VoidThreeArgFunctionCallerTests, int, unsigned long long, char)

template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
vector<tuple<Arg1Type, Arg2Type, Arg3Type>> VoidThreeArgFunctionCallerTests<Arg1Type, Arg2Type, Arg3Type>::_functionCalls;
