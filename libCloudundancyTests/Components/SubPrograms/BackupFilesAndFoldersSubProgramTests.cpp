#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/BackupFilesAndFoldersSubProgram.h"
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"
#include "libCloudundancyTests/Components/FileSystem/MetalMock/CloudundancyFileCopierMock.h"

TESTS(BackupFilesAndFoldersSubProgramTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(Run_SetsArgs_CallsCopyFilesAndFoldersToMultipleDestinationFolders_Returns0)
EVIDENCE

BackupFilesAndFoldersSubProgram _backupFilesAndFoldersToMultipleFoldersSubProgram;
ConsoleMock* _consoleMock = nullptr;
CloudundancyFileCopierMock* _cloudundancyFileCopierMock = nullptr;

STARTUP
{
   _backupFilesAndFoldersToMultipleFoldersSubProgram._cloudundancyFileCopier.reset(
      _cloudundancyFileCopierMock = new CloudundancyFileCopierMock);
   _backupFilesAndFoldersToMultipleFoldersSubProgram._console.reset(_consoleMock = new ConsoleMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   BackupFilesAndFoldersSubProgram backupFilesAndFoldersToMultipleFoldersSubProgram;
   DELETE_TO_ASSERT_NEWED(backupFilesAndFoldersToMultipleFoldersSubProgram._cloudundancyFileCopier);
}

TEST(Run_SetsArgs_CallsCopyFilesAndFoldersToMultipleDestinationFolders_Returns0)
{
   _cloudundancyFileCopierMock->CopyFilesAndFoldersToMultipleDestinationFoldersMock.Expect();
   _consoleMock->WriteLineMock.Expect();

   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   const int exitCode = _backupFilesAndFoldersToMultipleFoldersSubProgram.Run(args);
   //
   METALMOCK(_cloudundancyFileCopierMock->CopyFilesAndFoldersToMultipleDestinationFoldersMock.CalledOnceWith(args.iniFilePath));
   METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(
      "[Cloudundancy] OverallBackupResult: Successfully backed up all files and folders to all destination folders"));
   IS_ZERO(exitCode);
}

RUN_TESTS(BackupFilesAndFoldersSubProgramTests)
