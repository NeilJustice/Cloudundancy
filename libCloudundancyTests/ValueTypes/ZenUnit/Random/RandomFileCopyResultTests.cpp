#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/FileCopyResultEqualizer.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Random/RandomFileCopyResult.h"

TESTS(RandomFileCopyResultTests)
AFACT(RandomFileCopyResult_CodeCoverage)
AFACT(TestableRandomFileCopyResult_ReturnsFileCopyResultWithAllRandomFields)
EVIDENCE

TEST(RandomFileCopyResult_CodeCoverage)
{
   ZenUnit::Random<FileCopyResult>();
}

TEST(TestableRandomFileCopyResult_ReturnsFileCopyResultWithAllRandomFields)
{
   const ZenUnit::RandomGeneratorMock randomGeneratorMock;

   const fs::path sourceFilePath = ZenUnit::Random<fs::path>();
   const fs::path destinationFilePath = ZenUnit::Random<fs::path>();
   randomGeneratorMock.PathMock.ReturnValues(sourceFilePath, destinationFilePath);

   const bool copySucceeded = randomGeneratorMock.BoolMock.ReturnRandom();

   unsigned long long numberOfBytesCopied = ZenUnit::Random<unsigned long long>();
   unsigned long long durationInMilliseconds = ZenUnit::Random<unsigned long long>();
   randomGeneratorMock.UnsignedLongLongMock.ReturnValues(numberOfBytesCopied, durationInMilliseconds);

   const string errorMessage = randomGeneratorMock.StringMock.ReturnRandom();
   //
   const FileCopyResult randomFileCopyResult = ZenUnit::TestableRandomFileCopyResult(&randomGeneratorMock);
   //
   METALMOCK(randomGeneratorMock.PathMock.CalledNTimes(2));
   METALMOCK(randomGeneratorMock.BoolMock.CalledOnce());
   METALMOCK(randomGeneratorMock.UnsignedLongLongMock.CalledNTimes(2));
   METALMOCK(randomGeneratorMock.StringMock.CalledOnce());
   FileCopyResult expectedRandomFileCopyResult;
   expectedRandomFileCopyResult.sourceFilePath = sourceFilePath;
   expectedRandomFileCopyResult.destinationFilePath = destinationFilePath;
   expectedRandomFileCopyResult.copySucceeded = copySucceeded;
   expectedRandomFileCopyResult.numberOfBytesCopied = numberOfBytesCopied;
   expectedRandomFileCopyResult.durationInMilliseconds = durationInMilliseconds;
   expectedRandomFileCopyResult.errorMessage = errorMessage;
   ARE_EQUAL(expectedRandomFileCopyResult, randomFileCopyResult);
}

RUN_TESTS(RandomFileCopyResultTests)
