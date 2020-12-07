#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/BackupFilesAndFoldersTo7ZipFileSubProgram.h"
#include "libCloudundancyTests/Components/FileSystem/MetalMock/CloudundancyFileCopierMock.h"

TESTS(BackupFilesAndFoldersTo7ZipFileSubProgramTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(Run_DeletesCodeBackupFolder_CopiesCodeToBackupStagingFolder_SevenZipsBackupStagingFolder_Copies7ZipFileToDestinationFolders_Returns0)
AFACT(DeleteBackupStagingFolder_PrintsDeleting_DeletesBackupStagingFolder_PrintsDeletedInElapsedSeconds)
AFACT(CopyFilesAndFoldersToBackupStagingFolder_CopiesSourceFilesAndFoldersToBackupStagingFolder_PrintsElapsedSeconds)
AFACT(SevenZipBackupStagingFolder_Writes7ZipFileToFolder7ZipFileBackslashCloudundancyBackup_PrintsElapsedSeconds)
AFACT(Copy7ZipFileToDestinationFolders_DoesSo_PrintsElapsedSeconds)
EVIDENCE

BackupFilesAndFoldersTo7ZipFileSubProgram _backupFilesAndFoldersTo7ZipFileSubProgram;
// Function Callers
using VoidOneArgFunctionCallerMockType = VoidOneArgMemberFunctionCallerMock<
   BackupFilesAndFoldersTo7ZipFileSubProgram, const CloudundancyArgs&>;
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
   _backupFilesAndFoldersTo7ZipFileSubProgram._voidOneArgFunctionCaller.reset(_voidOneArgFunctionCallerMock = new VoidOneArgFunctionCallerMockType);
   // Constant Components
   _backupFilesAndFoldersTo7ZipFileSubProgram._console.reset(_consoleMock = new ConsoleMock);
   _backupFilesAndFoldersTo7ZipFileSubProgram._cloudundancyFileCopier.reset(_cloudundancyFileCopierMock = new CloudundancyFileCopierMock);
   _backupFilesAndFoldersTo7ZipFileSubProgram._fileSystem.reset(_fileSystemMock = new FileSystemMock);
   _backupFilesAndFoldersTo7ZipFileSubProgram._processRunner.reset(_processRunnerMock = new ProcessRunnerMock);
   _backupFilesAndFoldersTo7ZipFileSubProgram._stopwatch.reset(_stopwatchMock = new StopwatchMock);
   // Mutable Componants
   _backupFilesAndFoldersTo7ZipFileSubProgram._watch.reset(_watchMock = new WatchMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   BackupFilesAndFoldersTo7ZipFileSubProgram backupCodeRunner;
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

TEST(Run_DeletesCodeBackupFolder_CopiesCodeToBackupStagingFolder_SevenZipsBackupStagingFolder_Copies7ZipFileToDestinationFolders_Returns0)
{
   _voidOneArgFunctionCallerMock->CallConstMemberFunctionMock.Expect();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   const int exitCode = _backupFilesAndFoldersTo7ZipFileSubProgram.Run(args);
   //
   METALMOCK(_voidOneArgFunctionCallerMock->CallConstMemberFunctionMock.CalledAsFollows(
   {
      { &BackupFilesAndFoldersTo7ZipFileSubProgram::DeleteBackupStagingFolder, &_backupFilesAndFoldersTo7ZipFileSubProgram, args },
      { &BackupFilesAndFoldersTo7ZipFileSubProgram::CopyFilesAndFoldersToBackupStagingFolder, &_backupFilesAndFoldersTo7ZipFileSubProgram, args },
      { &BackupFilesAndFoldersTo7ZipFileSubProgram::SevenZipBackupStagingFolder, &_backupFilesAndFoldersTo7ZipFileSubProgram, args },
      { &BackupFilesAndFoldersTo7ZipFileSubProgram::Copy7ZipFileToDestinationFolders, &_backupFilesAndFoldersTo7ZipFileSubProgram, args }
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
   _backupFilesAndFoldersTo7ZipFileSubProgram.DeleteBackupStagingFolder(args);
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
   _backupFilesAndFoldersTo7ZipFileSubProgram.CopyFilesAndFoldersToBackupStagingFolder(args);
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

TEST(SevenZipBackupStagingFolder_Writes7ZipFileToFolder7ZipFileBackslashCloudundancyBackup_PrintsElapsedSeconds)
{
   _consoleMock->WriteLineMock.Expect();
   _stopwatchMock->StartMock.Expect();
   _fileSystemMock->SetCurrentPathMock.Expect();
   const string dateTimeNowForFileNames = _watchMock->DateTimeNowForFileNamesMock.ReturnRandom();
   _processRunnerMock->FailFastRunMock.ReturnRandom();
   const string elapsedSeconds = _stopwatchMock->StopAndGetElapsedSecondsMock.ReturnRandom();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   _backupFilesAndFoldersTo7ZipFileSubProgram.SevenZipBackupStagingFolder(args);
   //
   METALMOCK(_stopwatchMock->StartMock.CalledOnce());
   METALMOCK(_fileSystemMock->SetCurrentPathMock.CalledOnceWith(args.sevenZipStagingFolderPath));
   METALMOCK(_watchMock->DateTimeNowForFileNamesMock.CalledOnce());
   const string expectedSevenZipCommandLineArguments = String::Concat(
      "a -r -mx9 7ZipFile\\CloudundancyBackup_" + dateTimeNowForFileNames + ".7z");
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

TEST(Copy7ZipFileToDestinationFolders_DoesSo_PrintsElapsedSeconds)
{
   _consoleMock->WriteLineMock.Expect();
   _stopwatchMock->StartMock.Expect();
   const string elapsedSeconds = _stopwatchMock->StopAndGetElapsedSecondsMock.ReturnRandom();
   _cloudundancyFileCopierMock->CopyFilesAndFoldersToMultipleDestinationFoldersMock.Expect();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   _backupFilesAndFoldersTo7ZipFileSubProgram.Copy7ZipFileToDestinationFolders(args);
   //
   METALMOCK(_stopwatchMock->StartMock.CalledOnce());
   METALMOCK(_cloudundancyFileCopierMock->CopyFilesAndFoldersToMultipleDestinationFoldersMock.
      CalledOnceWith(args.sevenZipFileCopyingIniFilePath, false));
   METALMOCK(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce());
   const string expectedCopiedMessage = String::Concat(
      "[Cloudundancy] Copied .7z file to [DestinationFolders] in ", elapsedSeconds, " seconds\n");
   METALMOCK(_consoleMock->WriteLineMock.CalledAsFollows(
   {
      { "[Cloudundancy] Copying .7z file to [DestinationFolders]..." },
      { expectedCopiedMessage }
   }));
}

RUN_TESTS(BackupFilesAndFoldersTo7ZipFileSubProgramTests)
