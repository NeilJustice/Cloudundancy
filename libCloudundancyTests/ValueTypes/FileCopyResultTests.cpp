#include "pch.h"
#include "libCloudundancy/ValueTypes/FileCopyResult.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/FileCopyResultEqualizer.h"

TESTS(FileCopyResultTests)
AFACT(DefaultConstructor_SetsFieldsTo0)
EVIDENCE

TEST(DefaultConstructor_SetsFieldsTo0)
{
   const FileCopyResult defaultFileCopyResult;
   //
   FileCopyResult expectedDefaultFileCopyResult;
   expectedDefaultFileCopyResult.sourceFilePath = fs::path();
   expectedDefaultFileCopyResult.destinationFilePath = fs::path();
   expectedDefaultFileCopyResult.copySucceeded = false;
   expectedDefaultFileCopyResult.numberOfBytesCopied = 0;
   expectedDefaultFileCopyResult.durationInMilliseconds = 0;
   ARE_EQUAL(expectedDefaultFileCopyResult, defaultFileCopyResult);
}

RUN_TESTS(FileCopyResultTests)
