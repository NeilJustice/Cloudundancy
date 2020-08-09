#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/BackupFilesAndFoldersSubProgram.h"
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"
#include "libCloudundancyTests/Components/ZenMock/CloudundancyFileCopierMock.h"

TESTS(BackupFilesAndFoldersSubProgramTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(Run_SetsArgs_CallsCopyFilesAndFoldersToMultipleFolders)
EVIDENCE

BackupFilesAndFoldersSubProgram _backupFilesAndFoldersToMultipleFoldersSubProgram;
CloudundancyFileCopierMock* _cloudundancyFileCopierMock = nullptr;

STARTUP
{
   _backupFilesAndFoldersToMultipleFoldersSubProgram._cloudundancyFileCopier.reset(_cloudundancyFileCopierMock = new CloudundancyFileCopierMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   DELETE_TO_ASSERT_NEWED(_backupFilesAndFoldersToMultipleFoldersSubProgram._cloudundancyFileCopier);
}

TEST(Run_SetsArgs_CallsCopyFilesAndFoldersToMultipleFolders)
{
   _cloudundancyFileCopierMock->CopyFilesAndFoldersToMultipleFoldersMock.Expect();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   _backupFilesAndFoldersToMultipleFoldersSubProgram.Run(args);
   //
   ZENMOCK(_cloudundancyFileCopierMock->CopyFilesAndFoldersToMultipleFoldersMock.CalledOnceWith(args.iniFilePath));
}

RUN_TESTS(BackupFilesAndFoldersSubProgramTests)
