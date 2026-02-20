#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/SevenZipSubProgram.h"
#include "libCloudundancyTests/Components/FileSystem/MetalMock/CloudundancyFileCopierMock.h"
#include "libCloudundancyTests/Components/FileSystem/MetalMock/CloudundancyFileSystemMock.h"

TESTS(SevenZipSubProgramTests)
AFACT(Run_DoesSo)
AFACT(CopyFileToFilesAndFoldersToBackupStagingFolder_CopiesSourceFilesAndFoldersToBackupStagingFolder_PrintsElapsedSeconds)
AFACT(DeleteBackupStagingFolder_PrintsDeleting_DeletesBackupStagingFolder_PrintsDeletedInElapsedSeconds)
AFACT(SevenZipBackupStagingFolder_Writes7ZipFileToFolder7ZipFileBackslashCloudundancyBackup_PrintsElapsedSeconds)
AFACT(Copy7ZipFileToDestinationFolders_DoesSo_PrintsElapsedSeconds)
EVIDENCE

SevenZipSubProgram _sevenZipSubProgram;
// Function Callers
using _voidZeroArgMemberFunctionCallerMockType = Utils::VoidZeroArgMemberFunctionCallerMock<SevenZipSubProgram>;
_voidZeroArgMemberFunctionCallerMockType* _voidZeroArgMemberFunctionCallerMock = nullptr;
// Base Constant Components
Utils::ConsoleMock* p_consoleMock = nullptr;
// Constant Components
CloudundancyFileCopierMock* _cloudundancyFileCopierMock = nullptr;
CloudundancyFileSystemMock* _cloudundancyFileSystemMock = nullptr;
Utils::FileSystemMock* _fileSystemMock = nullptr;
Utils::ProcessRunnerMock* _processRunnerMock = nullptr;
Utils::StopwatchMock* _stopwatchMock = nullptr;
// Mutable Componants
Utils::WatchMock* _watchMock = nullptr;
// Mutable Fields
CloudundancyArgs p_args;

STARTUP
{
   // Function Callers
   _sevenZipSubProgram._voidZeroArgMemberFunctionCaller.reset(_voidZeroArgMemberFunctionCallerMock = new _voidZeroArgMemberFunctionCallerMockType);
   // Base Constant Components
   _sevenZipSubProgram.p_console.reset(p_consoleMock = new Utils::ConsoleMock);
   // Constant Components
   _sevenZipSubProgram._cloudundancyFileCopier.reset(_cloudundancyFileCopierMock = new CloudundancyFileCopierMock);
   _sevenZipSubProgram._cloudundancyFileSystem.reset(_cloudundancyFileSystemMock = new CloudundancyFileSystemMock);
   _sevenZipSubProgram._fileSystem.reset(_fileSystemMock = new Utils::FileSystemMock);
   _sevenZipSubProgram._processRunner.reset(_processRunnerMock = new Utils::ProcessRunnerMock);
   _sevenZipSubProgram._stopwatch.reset(_stopwatchMock = new Utils::StopwatchMock);
   // Mutable Componants
   _sevenZipSubProgram._watch.reset(_watchMock = new Utils::WatchMock);
   // Mutable Fields
   _sevenZipSubProgram.p_args = p_args = ZenUnit::Random<CloudundancyArgs>();
}

TEST(Run_DoesSo)
{
   _voidZeroArgMemberFunctionCallerMock->CallConstMemberFunctionMock.Expect();
   //
   const int exitCode = _sevenZipSubProgram.Run();
   //
   METALMOCK(_voidZeroArgMemberFunctionCallerMock->CallConstMemberFunctionMock.CalledNTimes(4));

   METALMOCKTHEN(_voidZeroArgMemberFunctionCallerMock->CallConstMemberFunctionMock.CalledWith(
      &_sevenZipSubProgram, &SevenZipSubProgram::DeleteBackupStagingFolder)).Then(

   METALMOCKTHEN(_voidZeroArgMemberFunctionCallerMock->CallConstMemberFunctionMock.CalledWith(
      &_sevenZipSubProgram, &SevenZipSubProgram::CopyFileToFilesAndFoldersToBackupStagingFolder))).Then(

   METALMOCKTHEN(_voidZeroArgMemberFunctionCallerMock->CallConstMemberFunctionMock.CalledWith(
      &_sevenZipSubProgram, &SevenZipSubProgram::SevenZipBackupStagingFolder))).Then(

   METALMOCKTHEN(_voidZeroArgMemberFunctionCallerMock->CallConstMemberFunctionMock.CalledWith(
      &_sevenZipSubProgram, &SevenZipSubProgram::Copy7ZipFileToDestinationFolders)));
   IS_ZERO(exitCode);
}

TEST(CopyFileToFilesAndFoldersToBackupStagingFolder_CopiesSourceFilesAndFoldersToBackupStagingFolder_PrintsElapsedSeconds)
{
   _cloudundancyFileCopierMock->CopyFilteredFilesAndFoldersToDestinationFoldersMock.Expect();
   //
   _sevenZipSubProgram.CopyFileToFilesAndFoldersToBackupStagingFolder();
   //
   METALMOCK(_cloudundancyFileCopierMock->CopyFilteredFilesAndFoldersToDestinationFoldersMock.CalledOnceWith(
      p_args.sevenZipModeIniInputFilePath, false));
}

TEST(DeleteBackupStagingFolder_PrintsDeleting_DeletesBackupStagingFolder_PrintsDeletedInElapsedSeconds)
{
   p_consoleMock->WriteLineMock.Expect();
   _cloudundancyFileSystemMock->DeleteFolderContentsExceptForFileMock.Expect();
   _stopwatchMock->StartMock.Expect();
   const string elapsedSeconds = _stopwatchMock->StopAndGetElapsedSecondsMock.ReturnRandom();
   //
   _sevenZipSubProgram.DeleteBackupStagingFolder();
   //
   const string expectedDeletingMessage = Utils::String::ConcatStrings(
      "[Cloudundancy] Deleting ", p_args.sevenZipStagingFolderPath.string());
   const string expectedDeletedMessage = Utils::String::ConcatStrings(
      "[Cloudundancy] Deleted ", p_args.sevenZipStagingFolderPath.string(), " in ", elapsedSeconds, " seconds\n");
   METALMOCK(p_consoleMock->WriteLineMock.CalledNTimes(2));
   METALMOCKTHEN(_stopwatchMock->StartMock.CalledOnce()).Then(
   METALMOCKTHEN(p_consoleMock->WriteLineMock.CalledWith(expectedDeletingMessage))).Then(
   METALMOCKTHEN(_cloudundancyFileSystemMock->DeleteFolderContentsExceptForFileMock.CalledOnceWith(
      p_args.sevenZipStagingFolderPath, "Cloudundancy.log"))).Then(
   METALMOCKTHEN(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce())).Then(
   METALMOCKTHEN(p_consoleMock->WriteLineMock.CalledWith(expectedDeletedMessage)));
}

TEST(SevenZipBackupStagingFolder_Writes7ZipFileToFolder7ZipFileBackslashCloudundancyBackup_PrintsElapsedSeconds)
{
   p_consoleMock->WriteLineColorMock.Expect();

   _stopwatchMock->StartMock.Expect();

   _fileSystemMock->SetCurrentPathMock.Expect();

   const string dateTimeNowForFileNames = _watchMock->DateTimeNowForFileNamesMock.ReturnRandom();

   _processRunnerMock->FailFastRunMock.ReturnRandom();

   const string elapsedSeconds = _stopwatchMock->StopAndGetElapsedSecondsMock.ReturnRandom();
   //
   _sevenZipSubProgram.SevenZipBackupStagingFolder();
   //
   METALMOCK(p_consoleMock->WriteLineColorMock.CalledNTimes(2));
   const string expectedSevenZipCommandLineArguments = Utils::String::ConcatStrings(
      "a 7ZipFile/CloudundancyBackup_", dateTimeNowForFileNames, ".7z -r -mx9");
   const string expectedSevenZippingMessage = Utils::String::ConcatStrings(
      "\n[Cloudundancy] 7-zipping ", p_args.sevenZipStagingFolderPath.string(), "...");
   const string expectedSevenZippedMessage = Utils::String::ConcatStrings(
      "[Cloudundancy] 7-zipped ", p_args.sevenZipStagingFolderPath.string(), " in ", elapsedSeconds, " seconds\n");
   METALMOCKTHEN(_stopwatchMock->StartMock.CalledOnce()).Then(
   METALMOCKTHEN(p_consoleMock->WriteLineColorMock.CalledWith(expectedSevenZippingMessage, Utils::Color::Teal))).Then(
   METALMOCKTHEN(_fileSystemMock->SetCurrentPathMock.CalledOnceWith(p_args.sevenZipStagingFolderPath))).Then(
   METALMOCKTHEN(_watchMock->DateTimeNowForFileNamesMock.CalledOnce())).Then(
   METALMOCKTHEN(_processRunnerMock->FailFastRunMock.CalledOnceWith("7z", expectedSevenZipCommandLineArguments, true))).Then(
   METALMOCKTHEN(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce())).Then(
   METALMOCKTHEN(p_consoleMock->WriteLineColorMock.CalledWith(expectedSevenZippedMessage, Utils::Color::Green)));
}

TEST(Copy7ZipFileToDestinationFolders_DoesSo_PrintsElapsedSeconds)
{
   p_consoleMock->WriteLineMock.Expect();
   p_consoleMock->WriteLineColorMock.Expect();
   _cloudundancyFileCopierMock->CopyFilteredFilesAndFoldersToDestinationFoldersMock.Expect();
   //
   _sevenZipSubProgram.Copy7ZipFileToDestinationFolders();
   //
   METALMOCKTHEN(p_consoleMock->WriteLineMock.CalledOnceWith(
      "[Cloudundancy] Copying .7z file to [DestinationFolders]...")).Then(
   METALMOCKTHEN(_cloudundancyFileCopierMock->CopyFilteredFilesAndFoldersToDestinationFoldersMock.CalledOnceWith(
      p_args.sevenZipFileCopyingIniInputFilePath, false))).Then(
   METALMOCKTHEN(p_consoleMock->WriteLineColorMock.CalledOnceWith(
      "\n[Cloudundancy] Successfully copied .7z file to [DestinationFolders]", Utils::Color::Green)));
}

RUN_TESTS(SevenZipSubProgramTests)
