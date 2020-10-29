#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/BackupFilesAndFoldersTo7zFileSubProgram.h"
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgramFactory.h"
#include "libCloudundancy/Components/SubPrograms/BackupFilesAndFoldersSubProgram.h"

TESTS(CloudundancySubProgramFactoryTests)
AFACT(NewCloudundancySubProgram_ProgramModeIsBackupFilesAndFolders_ReturnsMakeSharedBackupFilesAndFoldersSubProgram)
AFACT(NewCloudundancySubProgram_ProgramModeIsBackupFilesAndFoldersWith7Zip_ReturnsMakeSharedSevenZipSubProgram)
FACTS(NewCloudundancySubProgram_ProgramModeIsUnset_ThrowsInvalidArgumentException)
EVIDENCE

CloudundancySubProgramFactory _cloudundancyRunnerFactory;

TEST(NewCloudundancySubProgram_ProgramModeIsBackupFilesAndFolders_ReturnsMakeSharedBackupFilesAndFoldersSubProgram)
{
   const shared_ptr<CloudundancySubProgram> cloudundancySubProgram =
      _cloudundancyRunnerFactory.NewCloudundancySubProgram(ProgramMode::BackupFilesAndFolders);
   POINTEE_IS_EXACT_TYPE(BackupFilesAndFoldersSubProgram, cloudundancySubProgram);
}

TEST(NewCloudundancySubProgram_ProgramModeIsBackupFilesAndFoldersWith7Zip_ReturnsMakeSharedSevenZipSubProgram)
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
