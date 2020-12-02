#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/BackupFilesToMultipleFoldersSubProgram.h"
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"
#include "libCloudundancyTests/Components/FileSystem/MetalMock/CloudundancyFileCopierMock.h"

TESTS(BackupFilesToMultipleFoldersSubProgramTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(Run_SetsArgs_CallsCopyFilesAndFoldersToMultipleDestinationFolders_Returns0)
EVIDENCE

BackupFilesToMultipleFoldersSubProgram _backupFilesToMultipleFoldersSubProgram;
ConsoleMock* _consoleMock = nullptr;
CloudundancyFileCopierMock* _cloudundancyFileCopierMock = nullptr;

STARTUP
{
   _backupFilesToMultipleFoldersSubProgram._cloudundancyFileCopier.reset(
      _cloudundancyFileCopierMock = new CloudundancyFileCopierMock);
   _backupFilesToMultipleFoldersSubProgram._console.reset(_consoleMock = new ConsoleMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   BackupFilesToMultipleFoldersSubProgram backupFilesAndFoldersToMultipleFoldersSubProgram;
   DELETE_TO_ASSERT_NEWED(backupFilesAndFoldersToMultipleFoldersSubProgram._cloudundancyFileCopier);
}

TEST(Run_SetsArgs_CallsCopyFilesAndFoldersToMultipleDestinationFolders_Returns0)
{
   _cloudundancyFileCopierMock->CopyFilesAndFoldersToMultipleDestinationFoldersMock.Expect();
   _consoleMock->WriteLineMock.Expect();

   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   const int exitCode = _backupFilesToMultipleFoldersSubProgram.Run(args);
   //
   METALMOCK(_cloudundancyFileCopierMock->CopyFilesAndFoldersToMultipleDestinationFoldersMock.CalledOnceWith(args.iniFilePath));
   METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(
      "\n[Cloudundancy] OverallBackupResult: Successfully copied all [SourceFilesAndFolders] to all [DestinationFolders]"));
   IS_ZERO(exitCode);
}

RUN_TESTS(BackupFilesToMultipleFoldersSubProgramTests)
