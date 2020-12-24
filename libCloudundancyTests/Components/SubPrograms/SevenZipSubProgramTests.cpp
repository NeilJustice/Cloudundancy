#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/SevenZipSubProgram.h"
#include "libCloudundancyTests/Components/FileSystem/MetalMock/CloudundancyFileCopierMock.h"

TESTS(SevenZipSubProgramTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(Run_DeletesCodeBackupFolder_CopiesCodeToBackupStagingFolder_SevenZipsBackupStagingFolder_Copies7ZipFileToDestinationFolders_Returns0)
AFACT(DeleteBackupStagingFolder_PrintsDeleting_DeletesBackupStagingFolder_PrintsDeletedInElapsedSeconds)
AFACT(CopyFilesAndFoldersToBackupStagingFolder_CopiesSourceFilesAndFoldersToBackupStagingFolder_PrintsElapsedSeconds)
AFACT(SevenZipBackupStagingFolder_Writes7ZipFileToFolder7ZipFileBackslashCloudundancyBackup_PrintsElapsedSeconds)
AFACT(Copy7ZipFileToDestinationFolders_DoesSo_PrintsElapsedSeconds)
EVIDENCE

SevenZipSubProgram _sevenZipSubProgram;
// Function Callers
using VoidOneArgFunctionCallerMockType = VoidOneArgMemberFunctionCallerMock<
   SevenZipSubProgram, const CloudundancyArgs&>;
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
   _sevenZipSubProgram._voidOneArgFunctionCaller.reset(_voidOneArgFunctionCallerMock = new VoidOneArgFunctionCallerMockType);
   // Constant Components
   _sevenZipSubProgram._console.reset(_consoleMock = new ConsoleMock);
   _sevenZipSubProgram._cloudundancyFileCopier.reset(_cloudundancyFileCopierMock = new CloudundancyFileCopierMock);
   _sevenZipSubProgram._fileSystem.reset(_fileSystemMock = new FileSystemMock);
   _sevenZipSubProgram._processRunner.reset(_processRunnerMock = new ProcessRunnerMock);
   _sevenZipSubProgram._stopwatch.reset(_stopwatchMock = new StopwatchMock);
   // Mutable Componants
   _sevenZipSubProgram._watch.reset(_watchMock = new WatchMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   SevenZipSubProgram backupCodeRunner;
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
   const int exitCode = _sevenZipSubProgram.Run(args);
   //
   METALMOCK(_voidOneArgFunctionCallerMock->CallConstMemberFunctionMock.CalledAsFollows(
   {
      { &SevenZipSubProgram::DeleteBackupStagingFolder, &_sevenZipSubProgram, args },
      { &SevenZipSubProgram::CopyFilesAndFoldersToBackupStagingFolder, &_sevenZipSubProgram, args },
      { &SevenZipSubProgram::SevenZipBackupStagingFolder, &_sevenZipSubProgram, args },
      { &SevenZipSubProgram::Copy7ZipFileToDestinationFolders, &_sevenZipSubProgram, args }
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
   _sevenZipSubProgram.DeleteBackupStagingFolder(args);
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
   _cloudundancyFileCopierMock->CopyFilesAndFoldersToMultipleDestinationFoldersMock.Expect();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   _sevenZipSubProgram.CopyFilesAndFoldersToBackupStagingFolder(args);
   //
   METALMOCK(_cloudundancyFileCopierMock->CopyFilesAndFoldersToMultipleDestinationFoldersMock.
      CalledOnceWith(args.sevenZipModeIniFilePath, false));
}

TEST(SevenZipBackupStagingFolder_Writes7ZipFileToFolder7ZipFileBackslashCloudundancyBackup_PrintsElapsedSeconds)
{
   _consoleMock->WriteLineColorMock.Expect();

   _stopwatchMock->StartMock.Expect();

   _fileSystemMock->SetCurrentPathMock.Expect();

   const string dateTimeNowForFileNames = _watchMock->DateTimeNowForFileNamesMock.ReturnRandom();

   _processRunnerMock->FailFastRunMock.ReturnRandom();

   const string elapsedSeconds = _stopwatchMock->StopAndGetElapsedSecondsMock.ReturnRandom();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   _sevenZipSubProgram.SevenZipBackupStagingFolder(args);
   //
   METALMOCK(_stopwatchMock->StartMock.CalledOnce());
   METALMOCK(_fileSystemMock->SetCurrentPathMock.CalledOnceWith(args.sevenZipStagingFolderPath));
   METALMOCK(_watchMock->DateTimeNowForFileNamesMock.CalledOnce());
   const string expectedSevenZipCommandLineArguments = String::Concat(
      "a 7ZipFile/CloudundancyBackup_", dateTimeNowForFileNames, ".7z -r -mx9");
   METALMOCK(_processRunnerMock->FailFastRunMock.CalledOnceWith("7z", expectedSevenZipCommandLineArguments, true));
   METALMOCK(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce());
   const string expectedSevenZippingMessage =
      String::Concat("\n[Cloudundancy] 7-zipping ", args.sevenZipStagingFolderPath.string(), "...");
   const string expectedSevenZippedMessage = String::Concat(
      "[Cloudundancy] 7-zipped ", args.sevenZipStagingFolderPath.string(), " in ", elapsedSeconds, " seconds\n");
   METALMOCK(_consoleMock->WriteLineColorMock.CalledAsFollows(
   {
      { expectedSevenZippingMessage, Color::Teal },
      { expectedSevenZippedMessage, Color::Green }
   }));
}

TEST(Copy7ZipFileToDestinationFolders_DoesSo_PrintsElapsedSeconds)
{
   _consoleMock->WriteLineMock.Expect();
   _consoleMock->WriteLineColorMock.Expect();
   _cloudundancyFileCopierMock->CopyFilesAndFoldersToMultipleDestinationFoldersMock.Expect();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   _sevenZipSubProgram.Copy7ZipFileToDestinationFolders(args);
   //
   METALMOCK(_cloudundancyFileCopierMock->CopyFilesAndFoldersToMultipleDestinationFoldersMock.
      CalledOnceWith(args.sevenZipFileCopyingIniFilePath, false));
   METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith("[Cloudundancy] Copying .7z file to [DestinationFolders]..."));
   METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith(
      "\n[Cloudundancy] Successfully copied .7z file to [DestinationFolders]", Color::Green));
}

RUN_TESTS(SevenZipSubProgramTests)
