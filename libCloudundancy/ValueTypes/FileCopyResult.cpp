#include "pch.h"
#include "libCloudundancy/ValueTypes/FileCopyResult.h"

FileCopyResult::FileCopyResult()
   : copySucceeded(false)
   , numberOfBytesCopied(0)
   , durationInMilliseconds(0)
{
}
