#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/FileCopyResultEqualizerAndRandom.h"

TESTS(FileCopyResultEqualizerAndRandomTests)
AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
AFACT(TestableRandomFileCopyResult_ReturnsFileCopyResultWithAllRandomFields)
AFACT(ZenUnitRandomFileCopyResult_DoesNotThrowException)
EVIDENCE

TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
{
   ZENUNIT_EQUALIZER_TEST_SETUP(Utils::FileCopyResult);
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Utils::FileCopyResult, sourceFilePath, ZenUnit::Random<fs::path>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Utils::FileCopyResult, destinationFilePath, ZenUnit::Random<fs::path>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Utils::FileCopyResult, copySucceeded, true);
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Utils::FileCopyResult, numberOfBytesCopied, ZenUnit::RandomNon0<unsigned long long>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Utils::FileCopyResult, durationInMilliseconds, ZenUnit::RandomNon0<unsigned long long>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(Utils::FileCopyResult, copyFailureReason, ZenUnit::Random<string>());
}

TEST(TestableRandomFileCopyResult_ReturnsFileCopyResultWithAllRandomFields)
{
   const ZenUnit::RandomGeneratorMock randomGeneratorMock;

   const fs::path sourceFilePath = ZenUnit::Random<fs::path>();
   const fs::path destinationFilePath = ZenUnit::Random<fs::path>();
   randomGeneratorMock.FilesystemPathMock.ReturnValues(sourceFilePath, destinationFilePath);

   const bool copySucceeded = randomGeneratorMock.BoolMock.ReturnRandom();

   unsigned long long numberOfBytesCopied = ZenUnit::Random<unsigned long long>();
   unsigned long long durationInMilliseconds = ZenUnit::Random<unsigned long long>();
   randomGeneratorMock.UnsignedLongLongMock.ReturnValues(numberOfBytesCopied, durationInMilliseconds);

   const string copyFailureReason = randomGeneratorMock.StringMock.ReturnRandom();
   //
   const Utils::FileCopyResult randomFileCopyResult = ZenUnit::TestableRandomFileCopyResult(&randomGeneratorMock);
   //
   METALMOCK(randomGeneratorMock.FilesystemPathMock.CalledNTimes(2));
   METALMOCK(randomGeneratorMock.BoolMock.CalledOnce());
   METALMOCK(randomGeneratorMock.UnsignedLongLongMock.CalledNTimes(2));
   METALMOCK(randomGeneratorMock.StringMock.CalledOnce());
   Utils::FileCopyResult expectedRandomFileCopyResult;
   expectedRandomFileCopyResult.sourceFilePath = sourceFilePath;
   expectedRandomFileCopyResult.destinationFilePath = destinationFilePath;
   expectedRandomFileCopyResult.copySucceeded = copySucceeded;
   expectedRandomFileCopyResult.numberOfBytesCopied = numberOfBytesCopied;
   expectedRandomFileCopyResult.durationInMilliseconds = durationInMilliseconds;
   expectedRandomFileCopyResult.copyFailureReason = copyFailureReason;
   ARE_EQUAL(expectedRandomFileCopyResult, randomFileCopyResult);
}

TEST(ZenUnitRandomFileCopyResult_DoesNotThrowException)
{
   ZenUnit::Random<Utils::FileCopyResult>();
}

RUN_TESTS(FileCopyResultEqualizerAndRandomTests)
