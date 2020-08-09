#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgram.h"

TESTS(CloudundancySubProgramTests)
AFACT(Run_DoesNothing)
EVIDENCE

TEST(Run_DoesNothing)
{
   CloudundancySubProgram cloudundancySubProgram;
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   cloudundancySubProgram.Run(args);
}

RUN_TESTS(CloudundancySubProgramTests)
