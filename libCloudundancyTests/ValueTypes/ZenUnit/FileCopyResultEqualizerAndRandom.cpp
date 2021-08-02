#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/FileCopyResultEqualizerAndRandom.h"

namespace ZenUnit
{
   void Equalizer<Utils::FileCopyResult>::AssertEqual(
      const Utils::FileCopyResult& expectedFileCopyResult, const Utils::FileCopyResult& actualFileCopyResult)
   {
      ARE_EQUAL(expectedFileCopyResult.sourceFilePath, actualFileCopyResult.sourceFilePath);
      ARE_EQUAL(expectedFileCopyResult.destinationFilePath, actualFileCopyResult.destinationFilePath);
      ARE_EQUAL(expectedFileCopyResult.copySucceeded, actualFileCopyResult.copySucceeded);
      ARE_EQUAL(expectedFileCopyResult.numberOfBytesCopied, actualFileCopyResult.numberOfBytesCopied);
      ARE_EQUAL(expectedFileCopyResult.durationInMilliseconds, actualFileCopyResult.durationInMilliseconds);
      ARE_EQUAL(expectedFileCopyResult.copyFailureReason, actualFileCopyResult.copyFailureReason);
   }

   Utils::FileCopyResult TestableRandomFileCopyResult(const RandomGenerator* randomGenerator)
   {
      Utils::FileCopyResult randomFileCopyResult;
      randomFileCopyResult.sourceFilePath = randomGenerator->FilesystemPath();
      randomFileCopyResult.destinationFilePath = randomGenerator->FilesystemPath();
      randomFileCopyResult.copySucceeded = randomGenerator->Bool();
      randomFileCopyResult.numberOfBytesCopied = randomGenerator->UnsignedLongLong();
      randomFileCopyResult.durationInMilliseconds = randomGenerator->UnsignedLongLong();
      randomFileCopyResult.copyFailureReason = randomGenerator->String();
      return randomFileCopyResult;
   }

   template<>
   Utils::FileCopyResult Random()
   {
      return TestableRandomFileCopyResult(RandomGenerator::Instance());
   }
}
