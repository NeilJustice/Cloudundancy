#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgram.h"

TESTS(CloudundancySubProgramTests)
AFACT(DefaultConstructorAndRun_DoesNothing)
EVIDENCE

TEST(DefaultConstructorAndRun_DoesNothing)
{
   CloudundancySubProgram cloudundancySubProgram;
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   DOES_NOT_THROW(cloudundancySubProgram.Run(args));
}

RUN_TESTS(CloudundancySubProgramTests)
