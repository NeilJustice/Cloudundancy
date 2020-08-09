#include "pch.h"
#include "libCloudundancy/Components/Iteration/Repeatedly.h"

TESTS(RepeatedlyTests)
AFACT(Call_ZeroIterations_DoesNotCallFunction)
AFACT(Call_OneIteration_CallsFunctionOnce)
AFACT(Call_TwoIterations_CallsFunctionTwice)
EVIDENCE

TEST(Call_ZeroIterations_DoesNotCallFunction)
{
   Repeatedly::Call(0, []{ throw runtime_error(""); });
}

TEST(Call_OneIteration_CallsFunctionOnce)
{
   unsigned numberOfCalls = 0;
   //
   Repeatedly::Call(1, [&] { ++numberOfCalls; });
   //
   ARE_EQUAL(1, numberOfCalls);
}

TEST(Call_TwoIterations_CallsFunctionTwice)
{
   unsigned numberOfCalls = 0;
   //
   Repeatedly::Call(2, [&] { ++numberOfCalls; });
   //
   ARE_EQUAL(2, numberOfCalls);
}

RUN_TESTS(RepeatedlyTests)
