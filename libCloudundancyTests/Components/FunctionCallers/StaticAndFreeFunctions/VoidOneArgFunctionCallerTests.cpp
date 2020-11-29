#include "pch.h"
#include "libCloudundancy/Components/FunctionCallers/StaticAndFreeFunctions/VoidOneArgFunctionCaller.h"

template<typename ArgType>
TEMPLATE_TESTS(VoidOneArgFunctionCallerTests, ArgType)
AFACT(Call_CallsFunctionOnce)
EVIDENCE

static vector<ArgType> functionCalls;

static void VoidOneArgFunction(ArgType arg)
{
   functionCalls.push_back(arg);
}

CLEANUP
{
   functionCalls.clear();
}

TEST(Call_CallsFunctionOnce)
{
   VoidOneArgFunctionCaller<ArgType> voidOneArgFunctionCaller;

   voidOneArgFunctionCaller.Call(VoidOneArgFunction, ArgType{ 1 });
   VECTORS_ARE_EQUAL(vector<ArgType>{ 1 }, functionCalls);

   voidOneArgFunctionCaller.Call(VoidOneArgFunction, ArgType{ 2 });
   VECTORS_ARE_EQUAL((vector<ArgType>{ 1, 2 }), functionCalls);
}

RUN_TEMPLATE_TESTS(VoidOneArgFunctionCallerTests, int)
THEN_RUN_TEMPLATE_TESTS(VoidOneArgFunctionCallerTests, char)

template<typename ArgType>
vector<ArgType> VoidOneArgFunctionCallerTests<ArgType>::functionCalls;
