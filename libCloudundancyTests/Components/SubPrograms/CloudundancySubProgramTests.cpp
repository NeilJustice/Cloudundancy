#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgram.h"

TESTS(CloudundancySubProgramTests)
AFACT(DefaultConstructor_SetsFieldsToDefaultValues)
AFACT(Initialize_DoesSo)
AFACT(Run_Returns0)
EVIDENCE

CloudundancySubProgram _cloudundancySubProgram;

TEST(DefaultConstructor_SetsFieldsToDefaultValues)
{
   CloudundancySubProgram cloudundancySubProgram;
   // Constant Components
   DELETE_TO_ASSERT_NEWED(cloudundancySubProgram.p_console);
   // Mutable Fields
   IS_DEFAULT_VALUE(cloudundancySubProgram.p_args);
}

TEST(Initialize_DoesSo)
{
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   _cloudundancySubProgram.Initialize(args);
   //
   ARE_EQUAL(args, _cloudundancySubProgram.p_args);
}

TEST(Run_Returns0)
{
   const int exitCode = _cloudundancySubProgram.Run();
   IS_ZERO(exitCode);
}

RUN_TESTS(CloudundancySubProgramTests)
