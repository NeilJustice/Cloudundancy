#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/BackupFilesAndFoldersWith7ZipSubProgram.h"
#include "libCloudundancyTests/Components/MetalMock/CloudundancyFileCopierMock.h"

TESTS(BackupFilesAndFoldersWith7ZipSubProgramTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(Run_DeletesCodeBackupFolder_CopiesCodeToCodeBackupFolder_SevenZipsCodeBackupFolder_Copies7zFileToDestinationFolders)
// Private Functions
AFACT(CopyFilesAndFoldersToBackupStagingFolder_PrintsCopying_CopiesSourceFilesAndFolderToCodeBackupStagingFolder_PrintsCopiedInElapsedSeconds)
AFACT(DeleteBackupStagingFolder_PrintsDeleting_DeletesBackupStagingFolder_PrintsDeletedInElapsedSeconds)
AFACT(Copy7zFileToDestinationFolders_DoesSo_PrintsElapsedSeconds)
AFACT(SevenZipCodeBackupFolder_DoesSo_PrintsElapsedSeconds)
EVIDENCE

BackupFilesAndFoldersWith7ZipSubProgram _backupFilesAndFoldersTo7zFileSubProgram;
// Constant Components
ConsoleMock* _consoleMock = nullptr;
CloudundancyFileCopierMock* _fileCopierMock = nullptr;
FileSystemMock* _fileSystemMock = nullptr;
ProcessRunnerMock* _processRunnerMock = nullptr;
WatchMock* _watchMock = nullptr;
// Function Callers
using VoidOneArgFunctionCallerMockType = VoidOneArgMemberFunctionCallerMock<BackupFilesAndFoldersWith7ZipSubProgram, const CloudundancyArgs&>;
VoidOneArgFunctionCallerMockType* _voidOneArgFunctionCallerMock = nullptr;
// Mutable Components
StopwatchMock* _stopwatchMock = nullptr;

STARTUP
{
   // Constant Components
   _backupFilesAndFoldersTo7zFileSubProgram._console.reset(_consoleMock = new ConsoleMock);
   _backupFilesAndFoldersTo7zFileSubProgram._cloudundancyFileCopier.reset(_fileCopierMock = new CloudundancyFileCopierMock);
   _backupFilesAndFoldersTo7zFileSubProgram._fileSystem.reset(_fileSystemMock = new FileSystemMock);
   _backupFilesAndFoldersTo7zFileSubProgram._processRunner.reset(_processRunnerMock = new ProcessRunnerMock);
   _backupFilesAndFoldersTo7zFileSubProgram._watch.reset(_watchMock = new WatchMock);
   // Function Callers
   _backupFilesAndFoldersTo7zFileSubProgram._voidOneArgFunctionCaller.reset(_voidOneArgFunctionCallerMock = new VoidOneArgFunctionCallerMockType);
   // Mutable Components
   _backupFilesAndFoldersTo7zFileSubProgram._stopwatch.reset(_stopwatchMock = new StopwatchMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   BackupFilesAndFoldersWith7ZipSubProgram backupCodeRunner;
   // Constant Components
   DELETE_TO_ASSERT_NEWED(backupCodeRunner._console);
   DELETE_TO_ASSERT_NEWED(backupCodeRunner._cloudundancyFileCopier);
   DELETE_TO_ASSERT_NEWED(backupCodeRunner._fileSystem);
   DELETE_TO_ASSERT_NEWED(backupCodeRunner._processRunner);
   DELETE_TO_ASSERT_NEWED(backupCodeRunner._watch);
   // Function Callers
   DELETE_TO_ASSERT_NEWED(backupCodeRunner._voidOneArgFunctionCaller);
   // Mutable Components
   DELETE_TO_ASSERT_NEWED(backupCodeRunner._stopwatch);
}

TEST(Run_DeletesCodeBackupFolder_CopiesCodeToCodeBackupFolder_SevenZipsCodeBackupFolder_Copies7zFileToDestinationFolders)
{
   _voidOneArgFunctionCallerMock->ConstCallMock.Expect();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   _backupFilesAndFoldersTo7zFileSubProgram.Run(args);
   //
   METALMOCK(_voidOneArgFunctionCallerMock->ConstCallMock.CalledAsFollows(
   {
      { &_backupFilesAndFoldersTo7zFileSubProgram, &BackupFilesAndFoldersWith7ZipSubProgram::DeleteBackupStagingFolder, args },
      { &_backupFilesAndFoldersTo7zFileSubProgram, &BackupFilesAndFoldersWith7ZipSubProgram::CopyFilesAndFoldersToBackupStagingFolder, args },
      { &_backupFilesAndFoldersTo7zFileSubProgram, &BackupFilesAndFoldersWith7ZipSubProgram::SevenZipCodeBackupFolder, args },
      { &_backupFilesAndFoldersTo7zFileSubProgram, &BackupFilesAndFoldersWith7ZipSubProgram::Copy7zFileToDestinationFolders, args }
   }));
}

TEST(DeleteBackupStagingFolder_PrintsDeleting_DeletesBackupStagingFolder_PrintsDeletedInElapsedSeconds)
{
   _consoleMock->WriteLineMock.Expect();
   _fileCopierMock->DeleteFolderMock.Expect();
   _stopwatchMock->StartMock.Expect();
   const string elapsedSeconds = _stopwatchMock->StopAndGetElapsedSecondsMock.ReturnRandom();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   _backupFilesAndFoldersTo7zFileSubProgram.DeleteBackupStagingFolder(args);
   //
   METALMOCK(_fileCopierMock->DeleteFolderMock.CalledOnceWith(args.backupStagingFolderPath));
   METALMOCK(_stopwatchMock->StartMock.CalledOnce());
   METALMOCK(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce());
   METALMOCK(_consoleMock->WriteLineMock.CalledAsFollows(
   {
      { "[Cloudundancy] Deleting " + args.backupStagingFolderPath.string() },
      { "[Cloudundancy] Deleted " + args.backupStagingFolderPath.string() + " in " + elapsedSeconds + " seconds\n" }
   }));
}

TEST(CopyFilesAndFoldersToBackupStagingFolder_PrintsCopying_CopiesSourceFilesAndFolderToCodeBackupStagingFolder_PrintsCopiedInElapsedSeconds)
{
   _consoleMock->WriteLineMock.Expect();
   _stopwatchMock->StartMock.Expect();
   _fileCopierMock->CopyFilesAndFoldersToMultipleFoldersMock.Expect();
   const string elapsedSeconds = _stopwatchMock->StopAndGetElapsedSecondsMock.ReturnRandom();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   _backupFilesAndFoldersTo7zFileSubProgram.CopyFilesAndFoldersToBackupStagingFolder(args);
   //
   METALMOCK(_stopwatchMock->StartMock.CalledOnce());
   METALMOCK(_fileCopierMock->CopyFilesAndFoldersToMultipleFoldersMock.CalledOnceWith(args.iniFilePath));
   METALMOCK(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce());
   METALMOCK(_consoleMock->WriteLineMock.CalledAsFollows(
   {
      { "[Cloudundancy] Copying Code Folder To " + args.backupStagingFolderPath.string() },
      { "[Cloudundancy] Copied Code Folder To " + args.backupStagingFolderPath.string() + " in " + elapsedSeconds + " seconds\n" }
   }));
}

TEST(SevenZipCodeBackupFolder_DoesSo_PrintsElapsedSeconds)
{
   _consoleMock->WriteLineMock.Expect();
   _stopwatchMock->StartMock.Expect();
   _fileSystemMock->SetCurrentPathMock.Expect();
   const string dateTimeNowHoursMinutes = _watchMock->DateTimeNowHoursMinutesForFileNamesMock.ReturnRandom();
   _processRunnerMock->FailFastRunMock.ReturnRandom();
   const string elapsedSeconds = _stopwatchMock->StopAndGetElapsedSecondsMock.ReturnRandom();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   _backupFilesAndFoldersTo7zFileSubProgram.SevenZipCodeBackupFolder(args);
   //
   METALMOCK(_stopwatchMock->StartMock.CalledOnce());
   METALMOCK(_fileSystemMock->SetCurrentPathMock.CalledOnceWith(args.backupStagingFolderPath));
   METALMOCK(_watchMock->DateTimeNowHoursMinutesForFileNamesMock.CalledOnce());
   const string expectedSevenZipCommandLineArguments = "a -r -mx9 7zFile\\SourceFilesAndFolders_" + dateTimeNowHoursMinutes + ".7z";
   METALMOCK(_processRunnerMock->FailFastRunMock.CalledOnceWith(
      "7z.exe", expectedSevenZipCommandLineArguments));
   METALMOCK(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce());
   METALMOCK(_consoleMock->WriteLineMock.CalledAsFollows(
   {
      { "[Cloudundancy] 7-zipping 7zFile\\SourceFilesAndFolders." },
      { "[Cloudundancy] 7-zipped 7zFile\\SourceFilesAndFolders in " + elapsedSeconds + " seconds\n" }
   }));
}

TEST(Copy7zFileToDestinationFolders_DoesSo_PrintsElapsedSeconds)
{
   _consoleMock->WriteLineMock.Expect();
   _stopwatchMock->StartMock.Expect();
   const string elapsedSeconds = _stopwatchMock->StopAndGetElapsedSecondsMock.ReturnRandom();
   _fileCopierMock->CopyFilesAndFoldersToMultipleFoldersMock.Expect();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   _backupFilesAndFoldersTo7zFileSubProgram.Copy7zFileToDestinationFolders(args);
   //
   METALMOCK(_stopwatchMock->StartMock.CalledOnce());
   METALMOCK(_fileCopierMock->CopyFilesAndFoldersToMultipleFoldersMock.CalledOnceWith(args.sevenZipIniFilePath));
   METALMOCK(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce());
   METALMOCK(_consoleMock->WriteLineMock.CalledAsFollows(
   {
      { "[Cloudundancy] Copying .7z File To Backup Folders." },
      { "[Cloudundancy] Copied .7z File To Backup Folders in " + elapsedSeconds + " seconds\n" }
   }));
}

RUN_TESTS(BackupFilesAndFoldersWith7ZipSubProgramTests)
