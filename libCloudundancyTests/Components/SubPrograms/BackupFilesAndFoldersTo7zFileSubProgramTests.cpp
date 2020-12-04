#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/BackupFilesAndFoldersTo7zFileSubProgram.h"
#include "libCloudundancyTests/Components/FileSystem/MetalMock/CloudundancyFileCopierMock.h"

TESTS(BackupFilesAndFoldersTo7zFileSubProgramTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(Run_DeletesCodeBackupFolder_CopiesCodeToBackupStagingFolder_SevenZipsBackupStagingFolder_Copies7zFileToDestinationFolders_Returns0)
AFACT(DeleteBackupStagingFolder_PrintsDeleting_DeletesBackupStagingFolder_PrintsDeletedInElapsedSeconds)
AFACT(CopyFilesAndFoldersToBackupStagingFolder_CopiesSourceFilesAndFoldersToBackupStagingFolder_PrintsElapsedSeconds)
AFACT(SevenZipBackupStagingFolder_Writes7zFileToFolder7zFileBackslashCloudundancyBackup_PrintsElapsedSeconds)
AFACT(Copy7zFileToDestinationFolders_DoesSo_PrintsElapsedSeconds)
EVIDENCE

BackupFilesAndFoldersTo7zFileSubProgram _backupFilesAndFoldersTo7zFileSubProgram;
// Function Callers
using VoidOneArgFunctionCallerMockType = VoidOneArgMemberFunctionCallerMock<
   BackupFilesAndFoldersTo7zFileSubProgram, const CloudundancyArgs&>;
VoidOneArgFunctionCallerMockType* _voidOneArgFunctionCallerMock = nullptr;
// Constant Components
ConsoleMock* _consoleMock = nullptr;
CloudundancyFileCopierMock* _cloudundancyFileCopierMock = nullptr;
FileSystemMock* _fileSystemMock = nullptr;
ProcessRunnerMock* _processRunnerMock = nullptr;
StopwatchMock* _stopwatchMock = nullptr;
// Mutable Componants
WatchMock* _watchMock = nullptr;

STARTUP
{
   // Function Callers
   _backupFilesAndFoldersTo7zFileSubProgram._voidOneArgFunctionCaller.reset(_voidOneArgFunctionCallerMock = new VoidOneArgFunctionCallerMockType);
   // Constant Components
   _backupFilesAndFoldersTo7zFileSubProgram._console.reset(_consoleMock = new ConsoleMock);
   _backupFilesAndFoldersTo7zFileSubProgram._cloudundancyFileCopier.reset(_cloudundancyFileCopierMock = new CloudundancyFileCopierMock);
   _backupFilesAndFoldersTo7zFileSubProgram._fileSystem.reset(_fileSystemMock = new FileSystemMock);
   _backupFilesAndFoldersTo7zFileSubProgram._processRunner.reset(_processRunnerMock = new ProcessRunnerMock);
   _backupFilesAndFoldersTo7zFileSubProgram._stopwatch.reset(_stopwatchMock = new StopwatchMock);
   // Mutable Componants
   _backupFilesAndFoldersTo7zFileSubProgram._watch.reset(_watchMock = new WatchMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   BackupFilesAndFoldersTo7zFileSubProgram backupCodeRunner;
   // Function Callers
   DELETE_TO_ASSERT_NEWED(backupCodeRunner._voidOneArgFunctionCaller);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(backupCodeRunner._console);
   DELETE_TO_ASSERT_NEWED(backupCodeRunner._cloudundancyFileCopier);
   DELETE_TO_ASSERT_NEWED(backupCodeRunner._fileSystem);
   DELETE_TO_ASSERT_NEWED(backupCodeRunner._processRunner);
   DELETE_TO_ASSERT_NEWED(backupCodeRunner._watch);
   // Mutable Componants
   DELETE_TO_ASSERT_NEWED(backupCodeRunner._stopwatch);
}

TEST(Run_DeletesCodeBackupFolder_CopiesCodeToBackupStagingFolder_SevenZipsBackupStagingFolder_Copies7zFileToDestinationFolders_Returns0)
{
   _voidOneArgFunctionCallerMock->CallConstMemberFunctionMock.Expect();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   const int exitCode = _backupFilesAndFoldersTo7zFileSubProgram.Run(args);
   //
   METALMOCK(_voidOneArgFunctionCallerMock->CallConstMemberFunctionMock.CalledAsFollows(
   {
      { &BackupFilesAndFoldersTo7zFileSubProgram::DeleteBackupStagingFolder, &_backupFilesAndFoldersTo7zFileSubProgram, args },
      { &BackupFilesAndFoldersTo7zFileSubProgram::CopyFilesAndFoldersToBackupStagingFolder, &_backupFilesAndFoldersTo7zFileSubProgram, args },
      { &BackupFilesAndFoldersTo7zFileSubProgram::SevenZipBackupStagingFolder, &_backupFilesAndFoldersTo7zFileSubProgram, args },
      { &BackupFilesAndFoldersTo7zFileSubProgram::Copy7zFileToDestinationFolders, &_backupFilesAndFoldersTo7zFileSubProgram, args }
   }));
   IS_ZERO(exitCode);
}

TEST(DeleteBackupStagingFolder_PrintsDeleting_DeletesBackupStagingFolder_PrintsDeletedInElapsedSeconds)
{
   _consoleMock->WriteLineMock.Expect();
   _fileSystemMock->DeleteFolderMock.Expect();
   _stopwatchMock->StartMock.Expect();
   const string elapsedSeconds = _stopwatchMock->StopAndGetElapsedSecondsMock.ReturnRandom();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   _backupFilesAndFoldersTo7zFileSubProgram.DeleteBackupStagingFolder(args);
   //
   METALMOCK(_fileSystemMock->DeleteFolderMock.CalledOnceWith(args.sevenZipStagingFolderPath));
   METALMOCK(_stopwatchMock->StartMock.CalledOnce());
   METALMOCK(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce());
   const string expectedDeletingMessage = String::Concat("[Cloudundancy] Deleting ", args.sevenZipStagingFolderPath.string());
   const string expectedDeletedMessage = String::Concat(
      "[Cloudundancy] Deleted ", args.sevenZipStagingFolderPath.string(), " in ", elapsedSeconds, " seconds\n");
   METALMOCK(_consoleMock->WriteLineMock.CalledAsFollows(
   {
      { expectedDeletingMessage },
      { expectedDeletedMessage }
   }));
}

TEST(CopyFilesAndFoldersToBackupStagingFolder_CopiesSourceFilesAndFoldersToBackupStagingFolder_PrintsElapsedSeconds)
{
   _consoleMock->WriteLineMock.Expect();
   _stopwatchMock->StartMock.Expect();
   _cloudundancyFileCopierMock->CopyFilesAndFoldersToMultipleDestinationFoldersMock.Expect();
   const string elapsedSeconds = _stopwatchMock->StopAndGetElapsedSecondsMock.ReturnRandom();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   _backupFilesAndFoldersTo7zFileSubProgram.CopyFilesAndFoldersToBackupStagingFolder(args);
   //
   METALMOCK(_stopwatchMock->StartMock.CalledOnce());
   METALMOCK(_cloudundancyFileCopierMock->CopyFilesAndFoldersToMultipleDestinationFoldersMock.
      CalledOnceWith(args.sevenZipModeIniFilePath, false));
   METALMOCK(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce());
   const string expectedCopyingMessage = String::Concat(
      "[Cloudundancy] Copying [SourceFilesAndFolders] To " + args.sevenZipStagingFolderPath.string());
   const string expectedCopiedMessage = String::Concat(
      "[Cloudundancy] Copied [SourceFilesAndFolders] To ", args.sevenZipStagingFolderPath.string(), " in ", elapsedSeconds, " seconds\n");
   METALMOCK(_consoleMock->WriteLineMock.CalledAsFollows(
   {
      { expectedCopyingMessage },
      { expectedCopiedMessage }
   }));
}

TEST(SevenZipBackupStagingFolder_Writes7zFileToFolder7zFileBackslashCloudundancyBackup_PrintsElapsedSeconds)
{
   _consoleMock->WriteLineMock.Expect();
   _stopwatchMock->StartMock.Expect();
   _fileSystemMock->SetCurrentPathMock.Expect();
   const string dateTimeNowForFileNames = _watchMock->DateTimeNowForFileNamesMock.ReturnRandom();
   _processRunnerMock->FailFastRunMock.ReturnRandom();
   const string elapsedSeconds = _stopwatchMock->StopAndGetElapsedSecondsMock.ReturnRandom();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   _backupFilesAndFoldersTo7zFileSubProgram.SevenZipBackupStagingFolder(args);
   //
   METALMOCK(_stopwatchMock->StartMock.CalledOnce());
   METALMOCK(_fileSystemMock->SetCurrentPathMock.CalledOnceWith(args.sevenZipStagingFolderPath));
   METALMOCK(_watchMock->DateTimeNowForFileNamesMock.CalledOnce());
   const string expectedSevenZipCommandLineArguments = String::Concat(
      "a -r -mx9 7zFile\\CloudundancyBackup_" + dateTimeNowForFileNames + ".7z");
   METALMOCK(_processRunnerMock->FailFastRunMock.CalledOnceWith("7z", expectedSevenZipCommandLineArguments, true));
   METALMOCK(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce());
   const string expectedSevenZippingMessage = String::Concat("[Cloudundancy] 7-zipping ", args.sevenZipStagingFolderPath.string(), "...");
   const string expectedSevenZippedMessage = String::Concat(
      "[Cloudundancy] 7-zipped ", args.sevenZipStagingFolderPath.string(), " in ", elapsedSeconds, " seconds\n");
   METALMOCK(_consoleMock->WriteLineMock.CalledAsFollows(
   {
      { expectedSevenZippingMessage },
      { expectedSevenZippedMessage }
   }));
}

TEST(Copy7zFileToDestinationFolders_DoesSo_PrintsElapsedSeconds)
{
   _consoleMock->WriteLineMock.Expect();
   _stopwatchMock->StartMock.Expect();
   const string elapsedSeconds = _stopwatchMock->StopAndGetElapsedSecondsMock.ReturnRandom();
   _cloudundancyFileCopierMock->CopyFilesAndFoldersToMultipleDestinationFoldersMock.Expect();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   _backupFilesAndFoldersTo7zFileSubProgram.Copy7zFileToDestinationFolders(args);
   //
   METALMOCK(_stopwatchMock->StartMock.CalledOnce());
   METALMOCK(_cloudundancyFileCopierMock->CopyFilesAndFoldersToMultipleDestinationFoldersMock.
      CalledOnceWith(args.sevenZipModeIniFilePath, false));
   METALMOCK(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce());
   const string expectedCopiedMessage = String::Concat(
      "[Cloudundancy] Copied .7z file to [DestinationFolders] in ", elapsedSeconds, " seconds\n");
   METALMOCK(_consoleMock->WriteLineMock.CalledAsFollows(
   {
      { "[Cloudundancy] Copying .7z file to [DestinationFolders]..." },
      { expectedCopiedMessage }
   }));
}

RUN_TESTS(BackupFilesAndFoldersTo7zFileSubProgramTests)
