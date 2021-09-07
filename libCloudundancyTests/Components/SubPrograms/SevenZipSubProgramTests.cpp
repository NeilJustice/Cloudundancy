#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/SevenZipSubProgram.h"
#include "libCloudundancyTests/Components/FileSystem/MetalMock/CloudundancyFileCopierMock.h"
#include "libCloudundancyTests/Components/FileSystem/MetalMock/CloudundancyFileSystemMock.h"

TESTS(SevenZipSubProgramTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(Run_DeletesCodeBackupFolder_CopiesCodeToBackupStagingFolder_SevenZipsBackupStagingFolder_Copies7ZipFileToDestinationFolders_Returns0)
AFACT(CopyFileToFilesAndFoldersToBackupStagingFolder_CopiesSourceFilesAndFoldersToBackupStagingFolder_PrintsElapsedSeconds)
AFACT(DeleteBackupStagingFolder_PrintsDeleting_DeletesBackupStagingFolder_PrintsDeletedInElapsedSeconds)
AFACT(SevenZipBackupStagingFolder_Writes7ZipFileToFolder7ZipFileBackslashCloudundancyBackup_PrintsElapsedSeconds)
AFACT(Copy7ZipFileToDestinationFolders_DoesSo_PrintsElapsedSeconds)
EVIDENCE

SevenZipSubProgram _sevenZipSubProgram;
// Function Callers
using VoidOneArgMemberFunctionCallerMockType = Utils::VoidOneArgMemberFunctionCallerMock<SevenZipSubProgram, const CloudundancyArgs&>;
VoidOneArgMemberFunctionCallerMockType* _voidOneArgMemberFunctionCallerMock = nullptr;
// Base Constant Components
Utils::ConsoleMock* _consoleMock = nullptr;
// Constant Components
CloudundancyFileCopierMock* _cloudundancyFileCopierMock = nullptr;
CloudundancyFileSystemMock* _cloudundancyFileSystemMock = nullptr;
Utils::FileSystemMock* _fileSystemMock = nullptr;
Utils::ProcessRunnerMock* _processRunnerMock = nullptr;
Utils::StopwatchMock* _stopwatchMock = nullptr;
// Mutable Componants
Utils::WatchMock* _watchMock = nullptr;

STARTUP
{
   // Function Callers
   _sevenZipSubProgram._voidOneArgMemberFunctionCaller.reset(_voidOneArgMemberFunctionCallerMock = new VoidOneArgMemberFunctionCallerMockType);
   // Base Constant Components
   _sevenZipSubProgram._console.reset(_consoleMock = new Utils::ConsoleMock);
   // Constant Components
   _sevenZipSubProgram._cloudundancyFileCopier.reset(_cloudundancyFileCopierMock = new CloudundancyFileCopierMock);
   _sevenZipSubProgram._cloudundancyFileSystem.reset(_cloudundancyFileSystemMock = new CloudundancyFileSystemMock);
   _sevenZipSubProgram._fileSystem.reset(_fileSystemMock = new Utils::FileSystemMock);
   _sevenZipSubProgram._processRunner.reset(_processRunnerMock = new Utils::ProcessRunnerMock);
   _sevenZipSubProgram._stopwatch.reset(_stopwatchMock = new Utils::StopwatchMock);
   // Mutable Componants
   _sevenZipSubProgram._watch.reset(_watchMock = new Utils::WatchMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   SevenZipSubProgram sevenZipSubProgram;
   // Function Callers
   DELETE_TO_ASSERT_NEWED(sevenZipSubProgram._voidOneArgMemberFunctionCaller);
   // Base Constant Components
   DELETE_TO_ASSERT_NEWED(sevenZipSubProgram._console);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(sevenZipSubProgram._cloudundancyFileCopier);
   DELETE_TO_ASSERT_NEWED(sevenZipSubProgram._cloudundancyFileSystem);
   DELETE_TO_ASSERT_NEWED(sevenZipSubProgram._fileSystem);
   DELETE_TO_ASSERT_NEWED(sevenZipSubProgram._processRunner);
   DELETE_TO_ASSERT_NEWED(sevenZipSubProgram._watch);
   // Mutable Componants
   DELETE_TO_ASSERT_NEWED(sevenZipSubProgram._stopwatch);
}

TEST(Run_DeletesCodeBackupFolder_CopiesCodeToBackupStagingFolder_SevenZipsBackupStagingFolder_Copies7ZipFileToDestinationFolders_Returns0)
{
   _voidOneArgMemberFunctionCallerMock->CallConstMemberFunctionMock.Expect();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   const int exitCode = _sevenZipSubProgram.Run(args);
   //
   METALMOCK(_voidOneArgMemberFunctionCallerMock->CallConstMemberFunctionMock.CalledAsFollows(
   {
      { &SevenZipSubProgram::DeleteBackupStagingFolder, &_sevenZipSubProgram, args },
      { &SevenZipSubProgram::CopyFileToFilesAndFoldersToBackupStagingFolder, &_sevenZipSubProgram, args },
      { &SevenZipSubProgram::SevenZipBackupStagingFolder, &_sevenZipSubProgram, args },
      { &SevenZipSubProgram::Copy7ZipFileToDestinationFolders, &_sevenZipSubProgram, args }
   }));
   IS_ZERO(exitCode);
}

TEST(CopyFileToFilesAndFoldersToBackupStagingFolder_CopiesSourceFilesAndFoldersToBackupStagingFolder_PrintsElapsedSeconds)
{
   _cloudundancyFileCopierMock->CopyFileToFilesAndFoldersToMultipleDestinationFoldersMock.Expect();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   _sevenZipSubProgram.CopyFileToFilesAndFoldersToBackupStagingFolder(args);
   //
   METALMOCK(_cloudundancyFileCopierMock->CopyFileToFilesAndFoldersToMultipleDestinationFoldersMock.CalledOnceWith(args.sevenZipModeIniFilePath, false));
}

TEST(DeleteBackupStagingFolder_PrintsDeleting_DeletesBackupStagingFolder_PrintsDeletedInElapsedSeconds)
{
   _consoleMock->WriteLineMock.Expect();
   _cloudundancyFileSystemMock->DeleteFolderContentsExceptForFileMock.Expect();
   _stopwatchMock->StartMock.Expect();
   const string elapsedSeconds = _stopwatchMock->StopAndGetElapsedSecondsMock.ReturnRandom();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   _sevenZipSubProgram.DeleteBackupStagingFolder(args);
   //
   const string expectedDeletingMessage = Utils::String::ConcatStrings("[Cloudundancy] Deleting ", args.sevenZipStagingFolderPath.string());
   const string expectedDeletedMessage = Utils::String::ConcatStrings(
      "[Cloudundancy] Deleted ", args.sevenZipStagingFolderPath.string(), " in ", elapsedSeconds, " seconds\n");
   METALMOCK(_consoleMock->WriteLineMock.CalledNTimes(2));
   METALMOCKTHEN(_stopwatchMock->StartMock.CalledOnce()).Then(
   METALMOCKTHEN(_consoleMock->WriteLineMock.CalledWith(expectedDeletingMessage))).Then(
   METALMOCKTHEN(_cloudundancyFileSystemMock->DeleteFolderContentsExceptForFileMock.CalledOnceWith(args.sevenZipStagingFolderPath, "Cloudundancy.log"))).Then(
   METALMOCKTHEN(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce())).Then(
   METALMOCKTHEN(_consoleMock->WriteLineMock.CalledWith(expectedDeletedMessage)));
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
   METALMOCK(_consoleMock->WriteLineColorMock.CalledNTimes(2));
   const string expectedSevenZipCommandLineArguments = Utils::String::ConcatStrings("a 7ZipFile/CloudundancyBackup_", dateTimeNowForFileNames, ".7z -r -mx9");
   const string expectedSevenZippingMessage = Utils::String::ConcatStrings("\n[Cloudundancy] 7-zipping ", args.sevenZipStagingFolderPath.string(), "...");
   const string expectedSevenZippedMessage = Utils::String::ConcatStrings("[Cloudundancy] 7-zipped ", args.sevenZipStagingFolderPath.string(), " in ", elapsedSeconds, " seconds\n");
   METALMOCKTHEN(_stopwatchMock->StartMock.CalledOnce()).Then(
   METALMOCKTHEN(_consoleMock->WriteLineColorMock.CalledWith(expectedSevenZippingMessage, Color::Teal))).Then(
   METALMOCKTHEN(_fileSystemMock->SetCurrentPathMock.CalledOnceWith(args.sevenZipStagingFolderPath))).Then(
   METALMOCKTHEN(_watchMock->DateTimeNowForFileNamesMock.CalledOnce())).Then(
   METALMOCKTHEN(_processRunnerMock->FailFastRunMock.CalledOnceWith("7z", expectedSevenZipCommandLineArguments, true))).Then(
   METALMOCKTHEN(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce())).Then(
   METALMOCKTHEN(_consoleMock->WriteLineColorMock.CalledWith(expectedSevenZippedMessage, Color::Green)));
}

TEST(Copy7ZipFileToDestinationFolders_DoesSo_PrintsElapsedSeconds)
{
   _consoleMock->WriteLineMock.Expect();
   _consoleMock->WriteLineColorMock.Expect();
   _cloudundancyFileCopierMock->CopyFileToFilesAndFoldersToMultipleDestinationFoldersMock.Expect();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   _sevenZipSubProgram.Copy7ZipFileToDestinationFolders(args);
   //
   METALMOCKTHEN(_consoleMock->WriteLineMock.CalledOnceWith("[Cloudundancy] Copying .7z file to [DestinationFolders]...")).Then(
   METALMOCKTHEN(_cloudundancyFileCopierMock->CopyFileToFilesAndFoldersToMultipleDestinationFoldersMock.CalledOnceWith(args.sevenZipFileCopyingIniFilePath, false))).Then(
   METALMOCKTHEN(_consoleMock->WriteLineColorMock.CalledOnceWith("\n[Cloudundancy] Successfully copied .7z file to [DestinationFolders]", Color::Green)));
}

RUN_TESTS(SevenZipSubProgramTests)
