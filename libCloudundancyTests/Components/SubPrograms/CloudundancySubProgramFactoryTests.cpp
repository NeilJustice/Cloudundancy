#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/SevenZipSubProgram.h"
#include "libCloudundancy/Components/SubPrograms/CopyFilesToMultipleFoldersSubProgram.h"
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgramFactory.h"
#include "libCloudundancy/Components/SubPrograms/PrintExampleLinuxIniFileSubProgram.h"
#include "libCloudundancy/Components/SubPrograms/PrintExampleWindowsIniFileSubProgram.h"

TESTS(CloudundancySubProgramFactoryTests)
AFACT(NewCloudundancySubProgram_ProgramModeIsCopyFilesAndFoldersToMultipleFolder_ReturnsMakeSharedCopyFilesToMultipleFoldersSubProgram)
AFACT(NewCloudundancySubProgram_ProgramModeIsCopyFilesAndFoldersToMultipleFolderTo7ZipFile_ReturnsMakeSharedSevenZipSubProgram)
AFACT(NewCloudundancySubProgram_ProgramModeIsPrintExampleLinuxIniFile_ReturnsPrintExampleLinuxIniFileSubProgram)
AFACT(NewCloudundancySubProgram_ProgramModeIsPrintExampleWindowsIniFile_ReturnsPrintExampleWindowsIniFileSubProgram)
FACTS(NewCloudundancySubProgram_ProgramModeIsUnset_ThrowsInvalidArgumentException)
EVIDENCE

CloudundancySubProgramFactory _cloudundancySubProgramFactory;

TEST(NewCloudundancySubProgram_ProgramModeIsCopyFilesAndFoldersToMultipleFolder_ReturnsMakeSharedCopyFilesToMultipleFoldersSubProgram)
{
   const shared_ptr<CloudundancySubProgram> cloudundancySubProgram =
      _cloudundancySubProgramFactory.NewCloudundancySubProgram(ProgramMode::CopyFilesAndFoldersToMultipleFolders);
   POINTEE_IS_EXACT_TYPE(CopyFilesToMultipleFoldersSubProgram, cloudundancySubProgram);
}

TEST(NewCloudundancySubProgram_ProgramModeIsCopyFilesAndFoldersToMultipleFolderTo7ZipFile_ReturnsMakeSharedSevenZipSubProgram)
{
   const shared_ptr<CloudundancySubProgram> cloudundancySubProgram =
      _cloudundancySubProgramFactory.NewCloudundancySubProgram(ProgramMode::SevenZip);
   POINTEE_IS_EXACT_TYPE(SevenZipSubProgram, cloudundancySubProgram);
}

TEST(NewCloudundancySubProgram_ProgramModeIsPrintExampleLinuxIniFile_ReturnsPrintExampleLinuxIniFileSubProgram)
{
   const shared_ptr<CloudundancySubProgram> cloudundancySubProgram =
      _cloudundancySubProgramFactory.NewCloudundancySubProgram(ProgramMode::PrintExampleLinuxIniFile);
   POINTEE_IS_EXACT_TYPE(PrintExampleLinuxIniFileSubProgram, cloudundancySubProgram);
}

TEST(NewCloudundancySubProgram_ProgramModeIsPrintExampleWindowsIniFile_ReturnsPrintExampleWindowsIniFileSubProgram)
{
   const shared_ptr<CloudundancySubProgram> cloudundancySubProgram =
      _cloudundancySubProgramFactory.NewCloudundancySubProgram(ProgramMode::PrintExampleWindowsIniFile);
   POINTEE_IS_EXACT_TYPE(PrintExampleWindowsIniFileSubProgram, cloudundancySubProgram);
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
