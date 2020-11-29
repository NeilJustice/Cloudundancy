#include "pch.h"
#include "libCloudundancy/ValueTypes/ProcessResult.h"

TESTS(ProcessResultTests)
AFACT(DefaultConstrructor_SetsFieldsTo0)
AFACT(FiveArgConstructor_SetsFields)
AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
EVIDENCE

TEST(DefaultConstrructor_SetsFieldsTo0)
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

TEST(FiveArgConstructor_SetsFields)
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
   ZENUNIT_EQUALIZER_TEST_SETUP(ProcessResult);
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ProcessResult, processName, ZenUnit::Random<string>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ProcessResult, arguments, ZenUnit::Random<string>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ProcessResult, exitCode, ZenUnit::RandomNon0<int>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(ProcessResult, standardOutputAndError, ZenUnit::Random<string>());
}

RUN_TESTS(ProcessResultTests)
