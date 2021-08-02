#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/ProcessResultEqualizerAndRandom.h"

TESTS(ProcessResultEqualizerAndRandomTests)
AFACT(ZenUnitEqualizer_ThrowsZenUnitAnomalyIfAnyFieldNotEqual)
AFACT(TestableRandomProcessResult_ReturnsProcessResultWithAllRandomFields)
AFACT(ZenUnitRandomProcessResult_ReturnsResultOfCallingTestableRandomProcessResult)
EVIDENCE

TEST(ZenUnitEqualizer_ThrowsZenUnitAnomalyIfAnyFieldNotEqual)
{
   ZENUNIT_EQUALIZER_TEST_SETUP(Utils::ProcessResult);
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Utils::ProcessResult, processName, ZenUnit::Random<string>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Utils::ProcessResult, arguments, ZenUnit::Random<string>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Utils::ProcessResult, exitCode, ZenUnit::RandomNon0<int>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Utils::ProcessResult, standardOutputAndError, ZenUnit::Random<string>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Utils::ProcessResult, durationInMilliseconds, ZenUnit::RandomNon0<unsigned>());
}

TEST(TestableRandomProcessResult_ReturnsProcessResultWithAllRandomFields)
{
   ZenUnit::RandomGeneratorMock randomGeneratorMock;

   const string processName = ZenUnit::Random<string>();
   const string arguments = ZenUnit::Random<string>();
   const string standardOutputAndError = ZenUnit::Random<string>();
   randomGeneratorMock.StringMock.ReturnValues(processName, arguments, standardOutputAndError);

   const int exitCode = randomGeneratorMock.IntMock.ReturnRandom();

   const unsigned durationInMilliseconds = randomGeneratorMock.UnsignedIntMock.ReturnRandom();
   //
   const Utils::ProcessResult randomProcessResult = ZenUnit::TestableRandomProcessResult(&randomGeneratorMock);
   //
   METALMOCK(randomGeneratorMock.StringMock.CalledNTimes(3));
   METALMOCK(randomGeneratorMock.IntMock.CalledOnce());
   METALMOCK(randomGeneratorMock.UnsignedIntMock.CalledOnce());
   Utils::ProcessResult expectedRandomProcessResult;
   expectedRandomProcessResult.processName = processName;
   expectedRandomProcessResult.arguments = arguments;
   expectedRandomProcessResult.exitCode = exitCode;
   expectedRandomProcessResult.standardOutputAndError = standardOutputAndError;
   expectedRandomProcessResult.durationInMilliseconds = durationInMilliseconds;
   ARE_EQUAL(expectedRandomProcessResult, randomProcessResult);
}

TEST(ZenUnitRandomProcessResult_ReturnsResultOfCallingTestableRandomProcessResult)
{
   ZenUnit::Random<Utils::ProcessResult>();
}

RUN_TESTS(ProcessResultEqualizerAndRandomTests)
