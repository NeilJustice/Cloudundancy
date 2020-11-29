#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/FileCopyResultEqualizerAndRandom.h"

namespace ZenUnit
{
   void Equalizer<FileCopyResult>::AssertEqual(
      const FileCopyResult& expectedFileCopyResult, const FileCopyResult& actualFileCopyResult)
   {
      ARE_EQUAL(expectedFileCopyResult.sourceFilePath, actualFileCopyResult.sourceFilePath);
      ARE_EQUAL(expectedFileCopyResult.destinationFilePath, actualFileCopyResult.destinationFilePath);
      ARE_EQUAL(expectedFileCopyResult.copySucceeded, actualFileCopyResult.copySucceeded);
      ARE_EQUAL(expectedFileCopyResult.numberOfBytesCopied, actualFileCopyResult.numberOfBytesCopied);
      ARE_EQUAL(expectedFileCopyResult.durationInMilliseconds, actualFileCopyResult.durationInMilliseconds);
      ARE_EQUAL(expectedFileCopyResult.copyFailureReason, actualFileCopyResult.copyFailureReason);
   }

   FileCopyResult TestableRandomFileCopyResult(const RandomGenerator* randomGenerator)
   {
      FileCopyResult randomFileCopyResult;
      randomFileCopyResult.sourceFilePath = randomGenerator->FilesystemPath();
      randomFileCopyResult.destinationFilePath = randomGenerator->FilesystemPath();
      randomFileCopyResult.copySucceeded = randomGenerator->Bool();
      randomFileCopyResult.numberOfBytesCopied = randomGenerator->UnsignedLongLong();
      randomFileCopyResult.durationInMilliseconds = randomGenerator->UnsignedLongLong();
      randomFileCopyResult.copyFailureReason = randomGenerator->String();
      return randomFileCopyResult;
   }

   template<>
   FileCopyResult Random()
   {
      return TestableRandomFileCopyResult(RandomGenerator::Instance());
   }
}
