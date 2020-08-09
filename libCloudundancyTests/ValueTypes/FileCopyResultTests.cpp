#include "pch.h"
#include "libCloudundancy/ValueTypes/FileCopyResult.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/FileCopyResultEqualizer.h"

TESTS(FileCopyResultTests)
AFACT(DefaultConstructor_SetsFieldsTo0)
AFACT(MakeEmptyFileNotCopied_ReturnsFileCopyResultWithFilePathsSetAndCopySucceededSetToFalse)
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

TEST(MakeEmptyFileNotCopied_ReturnsFileCopyResultWithFilePathsSetAndCopySucceededSetToFalse)
{
   const fs::path emptySourceFilePath = ZenUnit::Random<fs::path>();
   const fs::path destinationFilePath = ZenUnit::Random<fs::path>();
   //
   const FileCopyResult emptyFileNotCopiedResult = FileCopyResult::MakeEmptyFileNotCopied(emptySourceFilePath, destinationFilePath);
   //
   FileCopyResult expectedReturnValue;
   expectedReturnValue.sourceFilePath = emptySourceFilePath;
   expectedReturnValue.destinationFilePath = destinationFilePath;
   expectedReturnValue.copySucceeded = false;
   expectedReturnValue.numberOfBytesCopied = 0;
   expectedReturnValue.durationInMilliseconds = 0;
   ARE_EQUAL(expectedReturnValue, emptyFileNotCopiedResult);
}

RUN_TESTS(FileCopyResultTests)
