#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/BackupCodeSubProgram.h"
#include "libCloudundancyTests/Components/ZenMock/CloudundancyFileCopierMock.h"

TESTS(BackupCodeSubProgramTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(Run_DeletesCodeBackupFolder_CopiesCodeToBackupStagingFolder_SevenZipsBackupStagingFolder_Copies7zFileToDestinationFolders)
AFACT(DeleteBackupStagingFolder_PrintsDeleting_DeletesBackupStagingFolder_PrintsDeletedInElapsedSeconds)
AFACT(CopyFilesAndFoldersToBackupStagingFolder_CopiesSourceFilesAndFoldersToBackupStagingFolder_PrintsElapsedSeconds)
AFACT(SevenZipBackupStagingFolder_Writes7zFileToFolder7zFileBackslashSourceFilesAndFolders_PrintsElapsedSeconds)
AFACT(Copy7zFileToDestinationFolders_DoesSo_PrintsElapsedSeconds)
EVIDENCE

BackupCodeSubProgram _backupCodeRunner;
// Components
ConsoleMock* _consoleMock = nullptr;
CloudundancyFileCopierMock* _cloudundancyFileCopierMock = nullptr;
FileSystemMock* _fileSystemMock = nullptr;
ProcessRunnerMock* _processRunnerMock = nullptr;
StopwatchMock* _stopwatchMock = nullptr;
// Function Callers
using VoidOneArgFunctionCallerMockType = VoidOneArgMemberFunctionCallerMock<BackupCodeSubProgram, const CloudundancyArgs&>;
VoidOneArgFunctionCallerMockType* _voidOneArgFunctionCallerMock = nullptr;
// Mutable Componants
WatchMock* _watchMock = nullptr;

STARTUP
{
   // Components
   _backupCodeRunner._console.reset(_consoleMock = new ConsoleMock);
   _backupCodeRunner._cloudundancyFileCopier.reset(_cloudundancyFileCopierMock = new CloudundancyFileCopierMock);
   _backupCodeRunner._fileSystem.reset(_fileSystemMock = new FileSystemMock);
   _backupCodeRunner._processRunner.reset(_processRunnerMock = new ProcessRunnerMock);
   _backupCodeRunner._stopwatch.reset(_stopwatchMock = new StopwatchMock);
   // Function Callers
   _backupCodeRunner._voidOneArgFunctionCaller.reset(_voidOneArgFunctionCallerMock = new VoidOneArgFunctionCallerMockType);
   // Mutable Componants
   _backupCodeRunner._watch.reset(_watchMock = new WatchMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   BackupCodeSubProgram backupCodeRunner;
   // Components
   DELETE_TO_ASSERT_NEWED(backupCodeRunner._console);
   DELETE_TO_ASSERT_NEWED(backupCodeRunner._cloudundancyFileCopier);
   DELETE_TO_ASSERT_NEWED(backupCodeRunner._fileSystem);
   DELETE_TO_ASSERT_NEWED(backupCodeRunner._processRunner);
   DELETE_TO_ASSERT_NEWED(backupCodeRunner._stopwatch);
   // Function Callers
   DELETE_TO_ASSERT_NEWED(backupCodeRunner._voidOneArgFunctionCaller);
   // Mutable Componants
   DELETE_TO_ASSERT_NEWED(backupCodeRunner._watch);
}

TEST(Run_DeletesCodeBackupFolder_CopiesCodeToBackupStagingFolder_SevenZipsBackupStagingFolder_Copies7zFileToDestinationFolders)
{
   _voidOneArgFunctionCallerMock->ConstCallMock.Expect();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   _backupCodeRunner.Run(args);
   //
   ZENMOCK(_voidOneArgFunctionCallerMock->ConstCallMock.CalledAsFollows(
   {
      { &_backupCodeRunner, &BackupCodeSubProgram::DeleteBackupStagingFolder, args },
      { &_backupCodeRunner, &BackupCodeSubProgram::CopyFilesAndFoldersToBackupStagingFolder, args },
      { &_backupCodeRunner, &BackupCodeSubProgram::SevenZipBackupStagingFolder, args },
      { &_backupCodeRunner, &BackupCodeSubProgram::Copy7zFileToDestinationFolders, args }
   }));
}

TEST(DeleteBackupStagingFolder_PrintsDeleting_DeletesBackupStagingFolder_PrintsDeletedInElapsedSeconds)
{
   _consoleMock->WriteLineMock.Expect();
   _cloudundancyFileCopierMock->DeleteFolderMock.Expect();
   _stopwatchMock->StartMock.Expect();
   const string elapsedSeconds = _stopwatchMock->StopAndGetElapsedSecondsMock.ReturnRandom();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   _backupCodeRunner.DeleteBackupStagingFolder(args);
   //
   ZENMOCK(_cloudundancyFileCopierMock->DeleteFolderMock.CalledOnceWith(args.backupStagingFolderPath));
   ZENMOCK(_stopwatchMock->StartMock.CalledOnce());
   ZENMOCK(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce());
   ZENMOCK(_consoleMock->WriteLineMock.CalledAsFollows(
   {
      { "[Cloudundancy] Deleting " + args.backupStagingFolderPath.string() },
      { "[Cloudundancy] Deleted " + args.backupStagingFolderPath.string() + " in " + elapsedSeconds + " seconds\n" }
   }));
}

TEST(CopyFilesAndFoldersToBackupStagingFolder_CopiesSourceFilesAndFoldersToBackupStagingFolder_PrintsElapsedSeconds)
{
   _consoleMock->WriteLineMock.Expect();
   _stopwatchMock->StartMock.Expect();
   _cloudundancyFileCopierMock->CopyFilesAndFoldersToMultipleFoldersMock.Expect();
   const string elapsedSeconds = _stopwatchMock->StopAndGetElapsedSecondsMock.ReturnRandom();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   _backupCodeRunner.CopyFilesAndFoldersToBackupStagingFolder(args);
   //
   ZENMOCK(_stopwatchMock->StartMock.CalledOnce());
   ZENMOCK(_cloudundancyFileCopierMock->CopyFilesAndFoldersToMultipleFoldersMock.CalledOnceWith(args.iniFilePath));
   ZENMOCK(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce());
   ZENMOCK(_consoleMock->WriteLineMock.CalledAsFollows(
   {
      { "[Cloudundancy] Copying Code Folder To " + args.backupStagingFolderPath.string() },
      { "[Cloudundancy] Copied Code Folder To " + args.backupStagingFolderPath.string() + " in " + elapsedSeconds + " seconds\n" }
   }));
}

TEST(SevenZipBackupStagingFolder_Writes7zFileToFolder7zFileBackslashSourceFilesAndFolders_PrintsElapsedSeconds)
{
   _consoleMock->WriteLineMock.Expect();
   _stopwatchMock->StartMock.Expect();
   _fileSystemMock->SetCurrentPathMock.Expect();
   const string dateTimeNowHoursMinutes = _watchMock->DateTimeNowHoursMinutesForFileNamesMock.ReturnRandom();
   _processRunnerMock->FailFastRunMock.ReturnRandom();
   const string elapsedSeconds = _stopwatchMock->StopAndGetElapsedSecondsMock.ReturnRandom();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   _backupCodeRunner.SevenZipBackupStagingFolder(args);
   //
   ZENMOCK(_stopwatchMock->StartMock.CalledOnce());
   ZENMOCK(_fileSystemMock->SetCurrentPathMock.CalledOnceWith(args.backupStagingFolderPath));
   ZENMOCK(_watchMock->DateTimeNowHoursMinutesForFileNamesMock.CalledOnce());
   const string expectedSevenZipCommandLineArguments = "a -r -mx9 7zFile\\SourceFilesAndFolders_" + dateTimeNowHoursMinutes + ".7z";
   ZENMOCK(_processRunnerMock->FailFastRunMock.CalledOnceWith(
      "7z.exe", expectedSevenZipCommandLineArguments));
   ZENMOCK(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce());
   const string expectedSevenZippingMessage = String::Concat("[Cloudundancy] 7-zipping ", args.backupStagingFolderPath.string());
   const string expectedSevenZippedMessage = String::Concat(
      "[Cloudundancy] 7-zipped ", args.backupStagingFolderPath.string(), " in ", elapsedSeconds, " seconds\n");
   ZENMOCK(_consoleMock->WriteLineMock.CalledAsFollows(
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
   _cloudundancyFileCopierMock->CopyFilesAndFoldersToMultipleFoldersMock.Expect();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   _backupCodeRunner.Copy7zFileToDestinationFolders(args);
   //
   ZENMOCK(_stopwatchMock->StartMock.CalledOnce());
   ZENMOCK(_cloudundancyFileCopierMock->CopyFilesAndFoldersToMultipleFoldersMock.CalledOnceWith(args.sevenZipIniFilePath));
   ZENMOCK(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce());
   ZENMOCK(_consoleMock->WriteLineMock.CalledAsFollows(
   {
      { "[Cloudundancy] Copying .7z File To Backup Folders." },
      { "[Cloudundancy] Copied .7z File To Backup Folders in " + elapsedSeconds + " seconds\n" }
   }));
}

RUN_TESTS(BackupCodeSubProgramTests)
