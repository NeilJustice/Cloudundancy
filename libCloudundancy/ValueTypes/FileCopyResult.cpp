#include "pch.h"
#include "libCloudundancy/ValueTypes/FileCopyResult.h"

FileCopyResult::FileCopyResult()
   : copySucceeded(false)
   , numberOfBytesCopied(0)
   , durationInMilliseconds(0)
{
}

FileCopyResult FileCopyResult::MakeEmptyFileNotCopied(
   const fs::path& emptySourceFilePath, const fs::path& destinationFilePath)
{
   FileCopyResult fileNotCopiedResult;
   fileNotCopiedResult.sourceFilePath = emptySourceFilePath;
   fileNotCopiedResult.destinationFilePath = destinationFilePath;
   fileNotCopiedResult.copySucceeded = false;
   fileNotCopiedResult.numberOfBytesCopied = 0;
   fileNotCopiedResult.durationInMilliseconds = 0;
   return fileNotCopiedResult;
}
