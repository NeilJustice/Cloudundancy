#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/FileCopyResultEqualizer.h"

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
      ARE_EQUAL(expectedFileCopyResult.errorMessage, actualFileCopyResult.errorMessage);
   }
}
