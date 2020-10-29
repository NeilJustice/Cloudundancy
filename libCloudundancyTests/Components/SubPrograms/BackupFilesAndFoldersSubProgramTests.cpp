#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/BackupFilesAndFoldersSubProgram.h"
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"
#include "libCloudundancyTests/Components/MetalMock/CloudundancyFileCopierMock.h"

TESTS(BackupFilesAndFoldersSubProgramTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(Run_SetsArgs_CallsCopyFilesAndFoldersToMultipleFolders_Returns0)
EVIDENCE

BackupFilesAndFoldersSubProgram _backupFilesAndFoldersToMultipleFoldersSubProgram;
CloudundancyFileCopierMock* _cloudundancyFileCopierMock = nullptr;

STARTUP
{
   _backupFilesAndFoldersToMultipleFoldersSubProgram._cloudundancyFileCopier.reset(
      _cloudundancyFileCopierMock = new CloudundancyFileCopierMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   DELETE_TO_ASSERT_NEWED(_backupFilesAndFoldersToMultipleFoldersSubProgram._cloudundancyFileCopier);
}

TEST(Run_SetsArgs_CallsCopyFilesAndFoldersToMultipleFolders_Returns0)
{
   _cloudundancyFileCopierMock->CopyFilesAndFoldersToMultipleFoldersMock.Expect();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   const int exitCode = _backupFilesAndFoldersToMultipleFoldersSubProgram.Run(args);
   //
   METALMOCK(_cloudundancyFileCopierMock->CopyFilesAndFoldersToMultipleFoldersMock.CalledOnceWith(args.iniFilePath));
   IS_ZERO(exitCode);
}

RUN_TESTS(BackupFilesAndFoldersSubProgramTests)
