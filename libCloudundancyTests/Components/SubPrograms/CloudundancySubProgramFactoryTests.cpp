#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/BackupFilesAndFoldersTo7zFileSubProgram.h"
#include "libCloudundancy/Components/SubPrograms/BackupFilesAndFoldersSubProgram.h"
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgramFactory.h"
#include "libCloudundancy/Components/SubPrograms/PrintExampleLinuxIniFileSubProgram.h"
#include "libCloudundancy/Components/SubPrograms/PrintExampleWindowsIniFileSubProgram.h"

TESTS(CloudundancySubProgramFactoryTests)
AFACT(NewCloudundancySubProgram_ProgramModeIsPrintExampleLinuxIniFile_ReturnsPrintExampleLinuxIniFileSubProgram)
AFACT(NewCloudundancySubProgram_ProgramModeIsPrintExampleWindowsIniFile_ReturnsPrintExampleWindowsIniFileSubProgram)
AFACT(NewCloudundancySubProgram_ProgramModeIsBackupFilesAndFolders_ReturnsMakeSharedBackupFilesAndFoldersSubProgram)
AFACT(NewCloudundancySubProgram_ProgramModeIsBackupFilesAndFoldersTo7zFile_ReturnsMakeSharedSevenZipSubProgram)
FACTS(NewCloudundancySubProgram_ProgramModeIsUnset_ThrowsInvalidArgumentException)
EVIDENCE

CloudundancySubProgramFactory _cloudundancyRunnerFactory;

TEST(NewCloudundancySubProgram_ProgramModeIsPrintExampleLinuxIniFile_ReturnsPrintExampleLinuxIniFileSubProgram)
{
   const shared_ptr<CloudundancySubProgram> cloudundancySubProgram =
      _cloudundancyRunnerFactory.NewCloudundancySubProgram(ProgramMode::PrintExampleLinuxIniFile);
   POINTEE_IS_EXACT_TYPE(PrintExampleLinuxIniFileSubProgram, cloudundancySubProgram);
}

TEST(NewCloudundancySubProgram_ProgramModeIsPrintExampleWindowsIniFile_ReturnsPrintExampleWindowsIniFileSubProgram)
{
   const shared_ptr<CloudundancySubProgram> cloudundancySubProgram =
      _cloudundancyRunnerFactory.NewCloudundancySubProgram(ProgramMode::PrintExampleWindowsIniFile);
   POINTEE_IS_EXACT_TYPE(PrintExampleWindowsIniFileSubProgram, cloudundancySubProgram);
}

TEST(NewCloudundancySubProgram_ProgramModeIsBackupFilesAndFolders_ReturnsMakeSharedBackupFilesAndFoldersSubProgram)
{
   const shared_ptr<CloudundancySubProgram> cloudundancySubProgram =
      _cloudundancyRunnerFactory.NewCloudundancySubProgram(ProgramMode::BackupFilesAndFolders);
   POINTEE_IS_EXACT_TYPE(BackupFilesAndFoldersSubProgram, cloudundancySubProgram);
}

TEST(NewCloudundancySubProgram_ProgramModeIsBackupFilesAndFoldersTo7zFile_ReturnsMakeSharedSevenZipSubProgram)
{
   const shared_ptr<CloudundancySubProgram> cloudundancySubProgram =
      _cloudundancyRunnerFactory.NewCloudundancySubProgram(ProgramMode::BackupFilesAndFoldersTo7zFile);
   POINTEE_IS_EXACT_TYPE(BackupFilesAndFoldersTo7zFileSubProgram, cloudundancySubProgram);
}

TEST1X1(NewCloudundancySubProgram_ProgramModeIsUnset_ThrowsInvalidArgumentException,
   ProgramMode invalidProgramMode,
   ProgramMode::Unset,
   ProgramMode::MaxValue)
{
   THROWS_EXCEPTION(_cloudundancyRunnerFactory.NewCloudundancySubProgram(invalidProgramMode),
      invalid_argument, "Invalid Cloudundancy program mode: " + to_string(static_cast<int>(invalidProgramMode)));
}

RUN_TESTS(CloudundancySubProgramFactoryTests)
