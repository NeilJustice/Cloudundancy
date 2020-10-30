#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgram.h"

TESTS(CloudundancySubProgramTests)
AFACT(DefaultConstructor_NewsConsole)
AFACT(Run_Returns0)
EVIDENCE

CloudundancySubProgram _cloudundancySubProgram;

TEST(DefaultConstructor_NewsConsole)
{
   CloudundancySubProgram cloudundancySubProgram;
   DELETE_TO_ASSERT_NEWED(cloudundancySubProgram._console);
}

TEST(Run_Returns0)
{
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   const int exitCode = _cloudundancySubProgram.Run(args);
   //
   IS_ZERO(exitCode);
}

RUN_TESTS(CloudundancySubProgramTests)
