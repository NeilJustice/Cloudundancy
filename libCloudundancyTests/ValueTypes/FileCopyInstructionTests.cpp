#include "pch.h"
#include "libCloudundancy/ValueTypes/FileCopyInstruction.h"

TESTS(FileCopyInstructionTests)
AFACT(DefaultConstructor_SetsFilePathsToEmptyPaths)
AFACT(FromCloudundancyIniCopyInstruction_ReturnsAbsoluteSourceFilePathCopyInstruction)
EVIDENCE

FileCopyInstruction _fileCopyInstruction;

TEST(DefaultConstructor_SetsFilePathsToEmptyPaths)
{
   FileCopyInstruction fileCopyInstruction;
   ARE_EQUAL(fs::path(), fileCopyInstruction.absoluteSourceFilePath);
   ARE_EQUAL(fs::path(), fileCopyInstruction.absoluteDestinationFilePath);
}

TEST(FromCloudundancyIniCopyInstruction_ReturnsAbsoluteSourceFilePathCopyInstruction)
{
   const AbsoluteFileOrFolderPathToRelativeFolderPath cloudundancyIniCopyInstruction = ZenUnit::Random<AbsoluteFileOrFolderPathToRelativeFolderPath>();
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   //
   FileCopyInstruction fileCopyInstruction = FileCopyInstruction::FromCloudundancyIniCopyInstruction(cloudundancyIniCopyInstruction, destinationFolderPath);
   //

}

RUN_TESTS(FileCopyInstructionTests)
