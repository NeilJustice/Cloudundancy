#include "pch.h"
#include "libCloudundancy/Components/FunctionCallers/NonMember/VoidZeroArgFunctionCaller.h"

TESTS(VoidZeroArgFunctionCallerTests)
AFACT(Call_CallsFunctionOnce)
EVIDENCE

static unsigned _numberOfFunctionCalls;

static void VoidZeroArgFunction()
{
   ++_numberOfFunctionCalls;
}

CLEANUP
{
   _numberOfFunctionCalls = 0;
}

TEST(Call_CallsFunctionOnce)
{
   VoidZeroArgFunctionCaller voidZeroArgFunctionCaller;

   voidZeroArgFunctionCaller.Call(VoidZeroArgFunction);
   ARE_EQUAL(1, _numberOfFunctionCalls);

   voidZeroArgFunctionCaller.Call(VoidZeroArgFunction);
   ARE_EQUAL(2, _numberOfFunctionCalls);
}

RUN_TESTS(VoidZeroArgFunctionCallerTests)

unsigned VoidZeroArgFunctionCallerTests::_numberOfFunctionCalls = 0;
