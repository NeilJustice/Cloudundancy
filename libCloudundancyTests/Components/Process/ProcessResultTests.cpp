#include "pch.h"
#include "libCloudundancy/Components/Process/ProcessResult.h"
#include "libCloudundancyTests/Components/Process/ZenUnit/ProcessResultEqualizerAndRandom.h"

TESTS(ProcessResultTests)
AFACT(Ctor_SetsFieldsTo0)
AFACT(FiveArgCtor_SetsFields)
AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
EVIDENCE

TEST(Ctor_SetsFieldsTo0)
{
   const ProcessResult defaultProcessResult;
   ProcessResult expectedDefaultProcessResult;
   expectedDefaultProcessResult.processName = "";
   expectedDefaultProcessResult.arguments = "";
   expectedDefaultProcessResult.exitCode = 0;
   expectedDefaultProcessResult.standardOutputAndError = "";
   expectedDefaultProcessResult.milliseconds = 0;
   ARE_EQUAL(expectedDefaultProcessResult, defaultProcessResult);
}

TEST(FiveArgCtor_SetsFields)
{
   const string processName = ZenUnit::Random<string>();
   const string arguments = ZenUnit::Random<string>();
   const int exitCode = ZenUnit::Random<int>();
   const string standardOutputAndError = ZenUnit::Random<string>();
   const unsigned milliseconds = ZenUnit::Random<unsigned>();
   //
   const ProcessResult processResult(processName, arguments, exitCode, standardOutputAndError, milliseconds);
   //
   ProcessResult expectedProcessResult;
   expectedProcessResult.processName = processName;
   expectedProcessResult.arguments = arguments;
   expectedProcessResult.exitCode = exitCode;
   expectedProcessResult.standardOutputAndError = standardOutputAndError;
   expectedProcessResult.milliseconds = milliseconds;
   ARE_EQUAL(expectedProcessResult, processResult);
}

TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
{
   SETUP_EQUALIZER_TEST(ProcessResult);
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ProcessResult, processName, ZenUnit::Random<string>());
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ProcessResult, arguments, ZenUnit::Random<string>());
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ProcessResult, exitCode, ZenUnit::RandomNon0<int>());
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ProcessResult, standardOutputAndError, ZenUnit::Random<string>());
}

RUN_TESTS(ProcessResultTests)
