#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgramFactory.h"
#include "libCloudundancy/Components/SubPrograms/CopyFilesToMultipleFoldersSubProgram.h"
#include "libCloudundancy/Components/SubPrograms/ExampleLinuxIniFileSubProgram.h"
#include "libCloudundancy/Components/SubPrograms/ExampleWindowsIniFileSubProgram.h"
#include "libCloudundancy/Components/SubPrograms/SevenZipSubProgram.h"

TESTS(CloudundancySubProgramFactoryTests)
AFACT(NewCloudundancySubProgram_ProgramModeIsCopyFileFastsAndFoldersToMultipleFolder_ReturnsMakeSharedCopyFileFastsToMultipleFoldersSubProgram)
AFACT(NewCloudundancySubProgram_ProgramModeIsCopyFileFastsAndFoldersToMultipleFolderTo7ZipFile_ReturnsMakeSharedSevenZipSubProgram)
AFACT(NewCloudundancySubProgram_ProgramModeIsExampleLinuxIniFile_ReturnsExampleLinuxIniFileSubProgram)
AFACT(NewCloudundancySubProgram_ProgramModeIsExampleWindowsIniFile_ReturnsExampleWindowsIniFileSubProgram)
FACTS(NewCloudundancySubProgram_ProgramModeIsUnset_ThrowsInvalidArgumentException)
EVIDENCE

CloudundancySubProgramFactory _cloudundancySubProgramFactory;

TEST(NewCloudundancySubProgram_ProgramModeIsCopyFileFastsAndFoldersToMultipleFolder_ReturnsMakeSharedCopyFileFastsToMultipleFoldersSubProgram)
{
   const shared_ptr<CloudundancySubProgram> cloudundancySubProgram =
      _cloudundancySubProgramFactory.NewCloudundancySubProgram(ProgramMode::CopyFileFastsAndFoldersToMultipleFolders);
   POINTEE_IS_EXACT_TYPE(CopyFileFastsToMultipleFoldersSubProgram, cloudundancySubProgram);
}

TEST(NewCloudundancySubProgram_ProgramModeIsCopyFileFastsAndFoldersToMultipleFolderTo7ZipFile_ReturnsMakeSharedSevenZipSubProgram)
{
   const shared_ptr<CloudundancySubProgram> cloudundancySubProgram =
      _cloudundancySubProgramFactory.NewCloudundancySubProgram(ProgramMode::SevenZip);
   POINTEE_IS_EXACT_TYPE(SevenZipSubProgram, cloudundancySubProgram);
}

TEST(NewCloudundancySubProgram_ProgramModeIsExampleLinuxIniFile_ReturnsExampleLinuxIniFileSubProgram)
{
   const shared_ptr<CloudundancySubProgram> cloudundancySubProgram =
      _cloudundancySubProgramFactory.NewCloudundancySubProgram(ProgramMode::ExampleLinuxIniFile);
   POINTEE_IS_EXACT_TYPE(ExampleLinuxIniFileSubProgram, cloudundancySubProgram);
}

TEST(NewCloudundancySubProgram_ProgramModeIsExampleWindowsIniFile_ReturnsExampleWindowsIniFileSubProgram)
{
   const shared_ptr<CloudundancySubProgram> cloudundancySubProgram =
      _cloudundancySubProgramFactory.NewCloudundancySubProgram(ProgramMode::ExampleWindowsIniFile);
   POINTEE_IS_EXACT_TYPE(ExampleWindowsIniFileSubProgram, cloudundancySubProgram);
}

TEST1X1(NewCloudundancySubProgram_ProgramModeIsUnset_ThrowsInvalidArgumentException,
   ProgramMode invalidProgramMode,
   ProgramMode::Unset,
   ProgramMode::MaxValue)
{
   THROWS_EXCEPTION(_cloudundancySubProgramFactory.NewCloudundancySubProgram(invalidProgramMode),
      invalid_argument, "Invalid Cloudundancy program mode: " + to_string(static_cast<int>(invalidProgramMode)));
}

RUN_TESTS(CloudundancySubProgramFactoryTests)
