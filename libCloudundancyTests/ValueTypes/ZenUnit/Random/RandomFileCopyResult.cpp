#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Random/RandomFileCopyResult.h"

namespace ZenUnit
{
   template<>
   FileCopyResult Random()
   {
      return TestableRandomFileCopyResult(RandomGenerator::Instance());
   }

   FileCopyResult TestableRandomFileCopyResult(const RandomGenerator* randomGenerator)
   {
      FileCopyResult randomFileCopyResult;
      randomFileCopyResult.sourceFilePath = randomGenerator->FilesystemPath();
      randomFileCopyResult.destinationFilePath = randomGenerator->FilesystemPath();
      randomFileCopyResult.copySucceeded = randomGenerator->Bool();
      randomFileCopyResult.numberOfBytesCopied = randomGenerator->UnsignedLongLong();
      randomFileCopyResult.durationInMilliseconds = randomGenerator->UnsignedLongLong();
      randomFileCopyResult.errorMessage = randomGenerator->String();
      return randomFileCopyResult;
   }
}
