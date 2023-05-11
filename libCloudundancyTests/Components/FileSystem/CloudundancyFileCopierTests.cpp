#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyFileCopier.h"
#include "libCloudundancyTests/Components/FileSystem/MetalMock/CloudundancyFileSystemMock.h"
#include "libCloudundancyTests/Components/FileSystem/MetalMock/CloudundancyLogFileWriterMock.h"
#include "libCloudundancyTests/Components/IniFile/MetalMock/CloudundancyIniFileReaderMock.h"

TESTS(CloudundancyFileCopierTests)
AFACT(DefaultConstructor_SetsFunctionsAndNewsComponents)
AFACT(CopyFilteredFilesAndFoldersToDestinationFolders_DeleteDestinationFoldersFirstIsTrue_DeletesDestinationFolders_CopiesFilesAndFoldersToFolders)
// Private Functions
AFACT(CopyFilteredFilesAndFoldersToDestinationFolder_TryCatchCallsDoCopyFilteredFilesAndFoldersToDestinationFolder)
AFACT(DoCopyFilteredFilesAndFoldersToDestinationFolder_AppendBackupStartedToLogFile_CopiesNonSkippedSourceFilesToDestinationFolder_AppendBackupSuccessfulToLogFile)
AFACT(DoCopyFilteredFilesAndFoldersToDestinationFolder_AppendBackupStartedToLogFile_CopiesNonSkippedSourceFilesToDestinationFolder_AppendBackupSuccessfulToLogFile)
AFACT(ExceptionHandlerForDoCopyFilteredFilesAndFoldersToDestinationFolder_WritesExceptionMessageToConsole_AppendsExceptionMessageToCloudundancyLogFile_RethrowsException)
AFACT(CopyFileOrFolderToFolder_SourcePathHasAFileName_CallsCopyFileToFileToFolder)
FACTS(CopyFileOrFolderToFolder_SourcePathDoesNotHaveAFileNameMeaningItIsAFolder_CallsRecursivelyCopyNonIgnoredFilesToFolder)
AFACT(CopyNonIgnoredFilesInAndBelowFolderToFolder_CopiesNonIgnoredFilesToFolderUntilRecursiveDirectoryIteratorReturnsNoMoreFiles)
AFACT(CopyNestedFileToFolder_RelativeDestinationFolderPathIsDot_CopiesNestedFileToFolderWithSlashDotSlashNotPresentInTheDestinationFilePath)
AFACT(CopyNestedFileToFolder_RelativeDestinationFolderPathIsNotDot_CopiesNestedFileToFolderWithRelativeDestinationFolderPathPresentInTheDestinationFilePath)
AFACT(CopyFileToFile_FileSizeIsGreaterThanOrEqualTo2GB_CopiesFileWithStdFilesystemCopyFileToFile_ReturnsFileCopyResult)
AFACT(CopyFileToFile_FileSizeIsLessThan2GB_CopiesFileWithCStyleCopyFileToFile_ReturnsFileCopyResult)
AFACT(CopyFileToFolder_RelativeDestinationFolderPathIsADot_DoesNotJoinDotCharacter_CallsCopyFileToFile)
AFACT(CopyFileToFolder_RelativeDestinationFolderPathIsNotADot_JoinsRelativeDestinationFolder_CallsCopyFileToFile)
AFACT(WriteCopiedMessageOrExitWithCode1IfCopyFailed_CopySucceeded_WritesCopiedAndDurationInMilliseconds)
AFACT(WriteCopiedMessageOrExitWithCode1IfCopyFailed_CopyFailed_WritesCopyFailedAndDurationInMillisecondsAndCopyFailureReason_AppendsErrorToCloudundancyLog_ExitsProgramWithCode1)
EVIDENCE

CloudundancyFileCopier _cloudundancyFileCopier;

// Function Pointers
METALMOCK_VOID1_FREE(_call_quick_exit, int)
METALMOCK_NONVOID3_FREE(string, _call_String_ReplaceFirst, const string&, const string&, const string&)
METALMOCK_NONVOID1_FREE(string, _call_Type_GetExceptionClassNameAndMessage, const exception*)

// Function Callers
using _caller_CopyFileToFileFunctionsMockType = Utils::VoidTwoArgMemberFunctionCallerMock<
   CloudundancyFileCopier, const CloudundancyIniCopyInstruction&, const fs::path&>;
_caller_CopyFileToFileFunctionsMockType* _caller_CopyFileToFileFunctionsMock = nullptr;

using _caller_CopyNestedFileToFolderMockType = Utils::VoidThreeArgMemberFunctionCallerMock<
   CloudundancyFileCopier, const fs::path&, const CloudundancyIniCopyInstruction&, const fs::path&>;
_caller_CopyNestedFileToFolderMockType* _caller_CopyNestedFileToFolderMock = nullptr;

using _caller_CopyFileToFileMockType = Utils::NonVoidTwoArgMemberFunctionCallerMock<
   Utils::FileCopyResult, CloudundancyFileCopier, const fs::path&, const fs::path&>;
_caller_CopyFileToFileMockType* _caller_CopyFileToFileMock = nullptr;

using _caller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMockType = Utils::VoidTwoArgMemberFunctionCallerMock<
   CloudundancyFileCopier, const Utils::FileCopyResult&, const fs::path&>;
_caller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMockType* _caller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock = nullptr;

using _forEacher_CopyEachFileOrFolderToFolderMockType = Utils::TwoArgMemberFunctionForEacherMock<
   CloudundancyFileCopier, fs::path, const CloudundancyIni&>;
_forEacher_CopyEachFileOrFolderToFolderMockType* _forEacher_CopyEachFileOrFolderToFolderMock = nullptr;

using _forEacher_CopyFileOrFolderToFolderMockType = Utils::TwoArgMemberFunctionForEacherMock<
   CloudundancyFileCopier, CloudundancyIniCopyInstruction, const fs::path&>;
_forEacher_CopyFileOrFolderToFolderMockType* _forEacher_CopyFileOrFolderToFolderMock = nullptr;

// Constant Components
CloudundancyIniFileReaderMock* _cloudundancyIniFileReaderMock = nullptr;
CloudundancyFileSystemMock* _cloudundancyFileSystemMock = nullptr;
CloudundancyLogFileWriterMock* _cloudundancyLogFileWriterMock = nullptr;
Utils::ConsoleMock* _consoleMock = nullptr;
Utils::FileSystemMock* _fileSystemMock = nullptr;
using TryCatchCallerMockType = Utils::TryCatchCallerMock<CloudundancyFileCopier, const pair<fs::path, CloudundancyIni>&>;
TryCatchCallerMockType* _tryCatchCallerMock = nullptr;

// Mutable Components
Utils::RecursiveDirectoryIteratorMock* _recursiveDirectoryIteratorMock = nullptr;
Utils::StopwatchMock* _stopwatchMock = nullptr;

STARTUP
{
   // Function Pointers
   _cloudundancyFileCopier._call_quick_exit = BIND_1ARG_METALMOCK_OBJECT(_call_quick_exitMock);
   _cloudundancyFileCopier._call_String_ReplaceFirst = BIND_3ARG_METALMOCK_OBJECT(_call_String_ReplaceFirstMock);
   _cloudundancyFileCopier._call_Type_GetExceptionClassNameAndMessage = BIND_1ARG_METALMOCK_OBJECT(_call_Type_GetExceptionClassNameAndMessageMock);
   // Function Callers
   _cloudundancyFileCopier._caller_CopyFileToFileFunctions.reset(_caller_CopyFileToFileFunctionsMock = new _caller_CopyFileToFileFunctionsMockType);
   _cloudundancyFileCopier._caller_CopyNestedFileToFolder.reset(_caller_CopyNestedFileToFolderMock = new _caller_CopyNestedFileToFolderMockType);
   _cloudundancyFileCopier._caller_CopyFileToFile.reset(_caller_CopyFileToFileMock = new _caller_CopyFileToFileMockType);
   _cloudundancyFileCopier._caller_WriteCopiedMessageOrExitWithCode1IfCopyFailed.reset(_caller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock = new _caller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMockType);
   _cloudundancyFileCopier._forEacher_CopyEachFileOrFolderToFolder.reset(_forEacher_CopyEachFileOrFolderToFolderMock = new _forEacher_CopyEachFileOrFolderToFolderMockType);
   _cloudundancyFileCopier._forEacher_CopyFileOrFolderToFolder.reset(_forEacher_CopyFileOrFolderToFolderMock = new _forEacher_CopyFileOrFolderToFolderMockType);
   // Constant Components
   _cloudundancyFileCopier._cloudundancyFileSystem.reset(_cloudundancyFileSystemMock = new CloudundancyFileSystemMock);
   _cloudundancyFileCopier._cloudundancyIniFileReader.reset(_cloudundancyIniFileReaderMock = new CloudundancyIniFileReaderMock);
   _cloudundancyFileCopier._cloudundancyLogFileWriter.reset(_cloudundancyLogFileWriterMock = new CloudundancyLogFileWriterMock);
   _cloudundancyFileCopier._console.reset(_consoleMock = new Utils::ConsoleMock);
   _cloudundancyFileCopier._fileSystem.reset(_fileSystemMock = new Utils::FileSystemMock);
   _cloudundancyFileCopier._tryCatchCaller.reset(_tryCatchCallerMock = new TryCatchCallerMockType);
   // Mutable Components
   _cloudundancyFileCopier._recursiveDirectoryIterator.reset(_recursiveDirectoryIteratorMock = new Utils::RecursiveDirectoryIteratorMock);
   _cloudundancyFileCopier._stopwatch.reset(_stopwatchMock = new Utils::StopwatchMock);
}

TEST(DefaultConstructor_SetsFunctionsAndNewsComponents)
{
   CloudundancyFileCopier cloudundancyFileCopier;
   // Function Pointers
   STD_FUNCTION_TARGETS(quick_exit, cloudundancyFileCopier._call_quick_exit);
   STD_FUNCTION_TARGETS(Utils::String::ReplaceFirst, cloudundancyFileCopier._call_String_ReplaceFirst);
   STD_FUNCTION_TARGETS(Type::GetExceptionClassNameAndMessage, cloudundancyFileCopier._call_Type_GetExceptionClassNameAndMessage);
   // Function Callers
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._caller_CopyFileToFileFunctions);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._caller_CopyNestedFileToFolder);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._caller_CopyFileToFile);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._caller_WriteCopiedMessageOrExitWithCode1IfCopyFailed);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._forEacher_CopyEachFileOrFolderToFolder);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._forEacher_CopyFileOrFolderToFolder);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._cloudundancyFileSystem);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._cloudundancyIniFileReader);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._console);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._fileSystem);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._tryCatchCaller);
   // Mutable Components
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._recursiveDirectoryIterator);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._stopwatch);
}

TEST(CopyFilteredFilesAndFoldersToDestinationFolders_DeleteDestinationFoldersFirstIsTrue_DeletesDestinationFolders_CopiesFilesAndFoldersToFolders)
{
   const CloudundancyIni cloudundancyIni = _cloudundancyIniFileReaderMock->ReadIniFileMock.ReturnRandom();

   _consoleMock->WriteLineMock.Expect();
   _consoleMock->WriteLineColorMock.Expect();
   _consoleMock->WriteLinesMock.Expect();

   _cloudundancyFileSystemMock->DeleteMultipleFolderContentsExceptForFileMock.Expect();

   _recursiveDirectoryIteratorMock->SetFileSubpathsToIgnoreMock.Expect();

   _forEacher_CopyEachFileOrFolderToFolderMock->CallConstMemberFunctionWithEachElementMock.Expect();

   const fs::path iniFilePath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileCopier.CopyFilteredFilesAndFoldersToDestinationFolders(iniFilePath, true);
   //
   const string expectedCopyingMessage = Utils::String::ConcatStrings(
      "[Cloudundancy] Copying [SourceFilesAndFolders] to [DestinationFolders] as listed in ", iniFilePath.string(), ":\n");
   METALMOCKTHEN(_cloudundancyIniFileReaderMock->ReadIniFileMock.CalledOnceWith(iniFilePath)).Then(
   METALMOCKTHEN(_consoleMock->WriteLineMock.CalledOnceWith("[Cloudundancy] Deleting [DestinationFolders] first because --delete-destination-folders-first is specified"))).Then(
   METALMOCKTHEN(_cloudundancyFileSystemMock->DeleteMultipleFolderContentsExceptForFileMock.CalledOnceWith(cloudundancyIni.destinationFolderPaths, "Cloudundancy.log"))).Then(
   METALMOCKTHEN(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedCopyingMessage, Color::Teal))).Then(
   METALMOCKTHEN(_consoleMock->WriteLinesMock.CalledOnceWith(cloudundancyIni.iniFileLines))).Then(
   METALMOCKTHEN(_recursiveDirectoryIteratorMock->SetFileSubpathsToIgnoreMock.CalledOnceWith(cloudundancyIni.fileSubpathsToIgnore))).Then(
   METALMOCKTHEN(_forEacher_CopyEachFileOrFolderToFolderMock->CallConstMemberFunctionWithEachElementMock.CalledOnceWith(
      cloudundancyIni.destinationFolderPaths,
      &_cloudundancyFileCopier,
      &CloudundancyFileCopier::CopyFilteredFilesAndFoldersToDestinationFolder,
      cloudundancyIni)));
}

TEST(CopyFilteredFilesAndFoldersToDestinationFolders_DeleteDestinationFoldersFirstIsFalse_DoesNotDeleteDestinationFolders_CopiesFilesAndFoldersToFolders)
{
   const CloudundancyIni cloudundancyIni = _cloudundancyIniFileReaderMock->ReadIniFileMock.ReturnRandom();

   _consoleMock->WriteLineMock.Expect();
   _consoleMock->WriteLinesMock.Expect();

   _recursiveDirectoryIteratorMock->SetFileSubpathsToIgnoreMock.Expect();

   _forEacher_CopyEachFileOrFolderToFolderMock->CallConstMemberFunctionWithEachElementMock.Expect();

   const fs::path iniFilePath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileCopier.CopyFilteredFilesAndFoldersToDestinationFolders(iniFilePath, false);
   //
   const string expectedCopyingMessage = Utils::String::ConcatStrings(
      "[Cloudundancy] Copying [SourceFilesAndFolders] to [DestinationFolders] as listed in ", iniFilePath.string(), ":\n");
   METALMOCKTHEN(_cloudundancyIniFileReaderMock->ReadIniFileMock.CalledOnceWith(iniFilePath)).Then(
   METALMOCKTHEN(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedCopyingMessage, Color::Teal))).Then(
   METALMOCKTHEN(_consoleMock->WriteLinesMock.CalledOnceWith(cloudundancyIni.iniFileLines))).Then(
   METALMOCKTHEN(_recursiveDirectoryIteratorMock->SetFileSubpathsToIgnoreMock.CalledOnceWith(cloudundancyIni.fileSubpathsToIgnore))).Then(
   METALMOCKTHEN(_forEacher_CopyEachFileOrFolderToFolderMock->CallConstMemberFunctionWithEachElementMock.CalledOnceWith(
      cloudundancyIni.destinationFolderPaths,
      &_cloudundancyFileCopier,
      &CloudundancyFileCopier::CopyFilteredFilesAndFoldersToDestinationFolder,
      cloudundancyIni)));
}

// Private Functions

TEST(CopyFilteredFilesAndFoldersToDestinationFolder_TryCatchCallsDoCopyFilteredFilesAndFoldersToDestinationFolder)
{
   _tryCatchCallerMock->TryCatchCallConstMemberFunctionMock.Expect();
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   const CloudundancyIni cloudundancyIni = ZenUnit::Random<CloudundancyIni>();
   //
   _cloudundancyFileCopier.CopyFilteredFilesAndFoldersToDestinationFolder(destinationFolderPath, cloudundancyIni);
   //
   const pair<fs::path, CloudundancyIni> expectedDestinationFolderPath_cloudundancyIni =
      make_pair(destinationFolderPath, cloudundancyIni);
   METALMOCK(_tryCatchCallerMock->TryCatchCallConstMemberFunctionMock.CalledOnceWith(
      &_cloudundancyFileCopier, &CloudundancyFileCopier::DoCopyFilteredFilesAndFoldersToDestinationFolder,
      expectedDestinationFolderPath_cloudundancyIni,
      &CloudundancyFileCopier::ExceptionHandlerForDoCopyFilteredFilesAndFoldersToDestinationFolder));
}

TEST(DoCopyFilteredFilesAndFoldersToDestinationFolder_AppendBackupStartedToLogFile_CopiesNonSkippedSourceFilesToDestinationFolder_AppendBackupSuccessfulToLogFile)
{
   _consoleMock->WriteLineMock.Expect();
   _consoleMock->WriteLineColorMock.Expect();

   _cloudundancyLogFileWriterMock->AppendTextToCloudundancyLogFileInFolderMock.Expect();

   _stopwatchMock->StartMock.Expect();

   _forEacher_CopyFileOrFolderToFolderMock->CallConstMemberFunctionWithEachElementMock.Expect();

   const string elapsedSeconds = _stopwatchMock->StopAndGetElapsedSecondsMock.ReturnRandom();

   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   const CloudundancyIni cloudundancyIni = ZenUnit::Random<CloudundancyIni>();
   const pair<fs::path, CloudundancyIni> destinationFolderPath_cloudundancyIni = make_pair(destinationFolderPath, cloudundancyIni);
   //
   _cloudundancyFileCopier.DoCopyFilteredFilesAndFoldersToDestinationFolder(destinationFolderPath_cloudundancyIni);
   //
   METALMOCK(_consoleMock->WriteLineColorMock.CalledNTimes(2));
   METALMOCK(_cloudundancyLogFileWriterMock->AppendTextToCloudundancyLogFileInFolderMock.CalledNTimes(2));

   const string expectedCopyingMessage = Utils::String::ConcatStrings(
      "\n[Cloudundancy] Copying [SourceFilesAndFolders] to destination folder ", destinationFolderPath.string(), ":\n");

   const string expectedFolderBackupResultSuccessMessage = Utils::String::ConcatStrings(
      "[Cloudundancy]   FolderBackupResult: Successfully copied [SourceFilesAndFolders] to ", destinationFolderPath.string());

   const string expectedFolderBackupDurationMessage = Utils::String::ConcatStrings(
      "[Cloudundancy] FolderBackupDuration: ", elapsedSeconds, " seconds");

   const string expectedBackupSuccessfulLogFileMessage = Utils::String::ConcatStrings(
      "Cloudundancy backup successful in ", elapsedSeconds, " seconds");

   METALMOCKTHEN(_consoleMock->WriteLineColorMock.CalledWith(expectedCopyingMessage, Color::Teal)).Then(
   METALMOCKTHEN(_cloudundancyLogFileWriterMock->AppendTextToCloudundancyLogFileInFolderMock.CalledWith(destinationFolderPath, "Cloudundancy backup started"))).Then(
   METALMOCKTHEN(_stopwatchMock->StartMock.CalledOnce())).Then(
   METALMOCKTHEN(_forEacher_CopyFileOrFolderToFolderMock->CallConstMemberFunctionWithEachElementMock.CalledOnceWith(
      cloudundancyIni.cloudundancyIniCopyInstructions,
      &_cloudundancyFileCopier,
      &CloudundancyFileCopier::CopyFileOrFolderToFolder,
      destinationFolderPath))).Then(
   METALMOCKTHEN(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce())).Then(
   METALMOCKTHEN(_consoleMock->WriteLineColorMock.CalledWith(expectedFolderBackupResultSuccessMessage, Color::Green))).Then(
   METALMOCKTHEN(_consoleMock->WriteLineMock.CalledOnceWith(expectedFolderBackupDurationMessage))).Then(
   METALMOCKTHEN(_cloudundancyLogFileWriterMock->AppendTextToCloudundancyLogFileInFolderMock.CalledWith(destinationFolderPath, expectedBackupSuccessfulLogFileMessage)));
}

TEST(ExceptionHandlerForDoCopyFilteredFilesAndFoldersToDestinationFolder_WritesExceptionMessageToConsole_AppendsExceptionMessageToCloudundancyLogFile_RethrowsException)
{
   const string exceptionClassNameAndMessage = _call_Type_GetExceptionClassNameAndMessageMock.ReturnRandom();

   _cloudundancyLogFileWriterMock->AppendTextToCloudundancyLogFileInFolderMock.Expect();

   const string exceptionMessage = ZenUnit::Random<string>();
   const runtime_error ex(exceptionMessage);

   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   const CloudundancyIni cloudundancyIni = ZenUnit::Random<CloudundancyIni>();
   const pair<fs::path, CloudundancyIni> destinationFolderPath_cloudundancyIni = make_pair(destinationFolderPath, cloudundancyIni);
   //
   THROWS_EXCEPTION(_cloudundancyFileCopier.ExceptionHandlerForDoCopyFilteredFilesAndFoldersToDestinationFolder(
      ex, destinationFolderPath_cloudundancyIni),
      runtime_error, exceptionClassNameAndMessage);
   //
   METALMOCK(_call_Type_GetExceptionClassNameAndMessageMock.CalledOnceWith(&ex));
   const string expectedErrorMessage = Utils::String::ConcatStrings(
      "Exception thrown while copying files to destination folder ", destinationFolderPath.string(), ": ", exceptionClassNameAndMessage);
   METALMOCK(_cloudundancyLogFileWriterMock->AppendTextToCloudundancyLogFileInFolderMock.CalledOnceWith(
      destinationFolderPath, expectedErrorMessage));
}

TEST(CopyFileOrFolderToFolder_SourcePathHasAFileName_CallsCopyFileToFileToFolder)
{
   _caller_CopyFileToFileFunctionsMock->CallConstMemberFunctionMock.Expect();
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   const CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction =
      ZenUnit::Random<CloudundancyIniCopyInstruction>();
   //
   _cloudundancyFileCopier.CopyFileOrFolderToFolder(cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   METALMOCK(_caller_CopyFileToFileFunctionsMock->CallConstMemberFunctionMock.CalledOnceWith(
      &_cloudundancyFileCopier, &CloudundancyFileCopier::CopyFileToFolder,
      cloudundancyIniCopyInstruction, destinationFolderPath));
}

TEST1X1(CopyFileOrFolderToFolder_SourcePathDoesNotHaveAFileNameMeaningItIsAFolder_CallsRecursivelyCopyNonIgnoredFilesToFolder,
   const fs::path& sourceFileOrFolderPath,
   "FolderNameA/",
   "FolderNameB\\")
{
   _caller_CopyFileToFileFunctionsMock->CallConstMemberFunctionMock.Expect();
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction = ZenUnit::Random<CloudundancyIniCopyInstruction>();
   cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath = sourceFileOrFolderPath;
   //
   _cloudundancyFileCopier.CopyFileOrFolderToFolder(cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   METALMOCK(_caller_CopyFileToFileFunctionsMock->CallConstMemberFunctionMock.CalledOnceWith(
      &_cloudundancyFileCopier, &CloudundancyFileCopier::CopyNonIgnoredFilesInAndBelowFolderToFolder,
      cloudundancyIniCopyInstruction, destinationFolderPath));
}

TEST(CopyNonIgnoredFilesInAndBelowFolderToFolder_CopiesNonIgnoredFilesToFolderUntilRecursiveDirectoryIteratorReturnsNoMoreFiles)
{
   _recursiveDirectoryIteratorMock->InitializeIteratorAtFolderPathMock.Expect();

   const fs::path nonIgnoredSourceFilePath1 = ZenUnit::Random<fs::path>();
   const fs::path nonIgnoredSourceFilePath2 = ZenUnit::Random<fs::path>();
   const fs::path terminatorFilePath;
   _recursiveDirectoryIteratorMock->NextNonIgnoredFilePathMock.ReturnValues(
      nonIgnoredSourceFilePath1, nonIgnoredSourceFilePath2, terminatorFilePath);

   _caller_CopyNestedFileToFolderMock->CallConstMemberFunctionMock.Expect();

   const CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction = ZenUnit::Random<CloudundancyIniCopyInstruction>();
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileCopier.CopyNonIgnoredFilesInAndBelowFolderToFolder(cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   METALMOCK(_recursiveDirectoryIteratorMock->NextNonIgnoredFilePathMock.CalledNTimes(3));
   METALMOCK(_caller_CopyNestedFileToFolderMock->CallConstMemberFunctionMock.CalledNTimes(2));

   METALMOCKTHEN(_recursiveDirectoryIteratorMock->InitializeIteratorAtFolderPathMock.CalledOnceWith(cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath)).Then(

   METALMOCKTHEN(_recursiveDirectoryIteratorMock->NextNonIgnoredFilePathMock.Called())).Then(
   METALMOCKTHEN(_caller_CopyNestedFileToFolderMock->CallConstMemberFunctionMock.CalledWith(
      &_cloudundancyFileCopier, &CloudundancyFileCopier::CopyNestedFileToFolder,
      nonIgnoredSourceFilePath1, cloudundancyIniCopyInstruction, destinationFolderPath))).Then(

   METALMOCKTHEN(_recursiveDirectoryIteratorMock->NextNonIgnoredFilePathMock.Called())).Then(
   METALMOCKTHEN(_caller_CopyNestedFileToFolderMock->CallConstMemberFunctionMock.CalledWith(
      &_cloudundancyFileCopier, &CloudundancyFileCopier::CopyNestedFileToFolder,
      nonIgnoredSourceFilePath2, cloudundancyIniCopyInstruction, destinationFolderPath))).Then(

   METALMOCKTHEN(_recursiveDirectoryIteratorMock->NextNonIgnoredFilePathMock.Called()));
}

TEST(CopyNestedFileToFolder_RelativeDestinationFolderPathIsDot_CopiesNestedFileToFolderWithSlashDotSlashNotPresentInTheDestinationFilePath)
{
   const fs::path sourceFilePathRelativeToSourceFolderPath = _call_String_ReplaceFirstMock.ReturnRandom();

   const Utils::FileCopyResult fileCopyResult = _caller_CopyFileToFileMock->CallConstMemberFunctionMock.ReturnRandom();

   _caller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.Expect();

   const fs::path sourceFilePath = ZenUnit::Random<fs::path>();
   CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction = ZenUnit::Random<CloudundancyIniCopyInstruction>();
   cloudundancyIniCopyInstruction.relativeDestinationFolderPath = ".";
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileCopier.CopyNestedFileToFolder(sourceFilePath, cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   const fs::path expectedDestinationFilePath =
      destinationFolderPath /
      sourceFilePathRelativeToSourceFolderPath;
   METALMOCKTHEN(_call_String_ReplaceFirstMock.CalledOnceWith(sourceFilePath.string(), cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath.string(), "")).Then(
   METALMOCKTHEN(_caller_CopyFileToFileMock->CallConstMemberFunctionMock.CalledOnceWith(
      &_cloudundancyFileCopier, &CloudundancyFileCopier::CopyFileToFile, sourceFilePath, expectedDestinationFilePath))).Then(
   METALMOCKTHEN(_caller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.CalledOnceWith(
      &_cloudundancyFileCopier, &CloudundancyFileCopier::WriteCopiedMessageOrExitWithCode1IfCopyFailed, fileCopyResult, destinationFolderPath)));
}

TEST(CopyNestedFileToFolder_RelativeDestinationFolderPathIsNotDot_CopiesNestedFileToFolderWithRelativeDestinationFolderPathPresentInTheDestinationFilePath)
{
   const fs::path sourceFilePathRelativeToSourceFolderPath = _call_String_ReplaceFirstMock.ReturnRandom();

   const Utils::FileCopyResult fileCopyResult = _caller_CopyFileToFileMock->CallConstMemberFunctionMock.ReturnRandom();

   _caller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.Expect();

   const fs::path sourceFilePath = ZenUnit::Random<fs::path>();
   const CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction = ZenUnit::Random<CloudundancyIniCopyInstruction>();
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileCopier.CopyNestedFileToFolder(sourceFilePath, cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   const fs::path expectedDestinationFilePath =
      destinationFolderPath /
      cloudundancyIniCopyInstruction.relativeDestinationFolderPath /
      sourceFilePathRelativeToSourceFolderPath;
   METALMOCKTHEN(_call_String_ReplaceFirstMock.CalledOnceWith(sourceFilePath.string(), cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath.string(), "")).Then(
   METALMOCKTHEN(_caller_CopyFileToFileMock->CallConstMemberFunctionMock.CalledOnceWith(&_cloudundancyFileCopier, &CloudundancyFileCopier::CopyFileToFile, sourceFilePath, expectedDestinationFilePath))).Then(
   METALMOCKTHEN(_caller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.CalledOnceWith(
      &_cloudundancyFileCopier, &CloudundancyFileCopier::WriteCopiedMessageOrExitWithCode1IfCopyFailed, fileCopyResult, destinationFolderPath)));
}

TEST(CopyFileToFile_FileSizeIsGreaterThanOrEqualTo2GB_CopiesFileWithStdFilesystemCopyFileToFile_ReturnsFileCopyResult)
{
   _consoleMock->WriteMock.Expect();

   _cloudundancyFileSystemMock->FileSizeIsGreaterThanOrEqualTo2GBMock.Return(true);

   const Utils::FileCopyResult fileCopyResult = ZenUnit::Random<Utils::FileCopyResult>();
   _fileSystemMock->CopyFileToFileLargerThan2GBMock.Return(fileCopyResult);

   const fs::path sourceFilePath = ZenUnit::Random<fs::path>();
   const fs::path destinationFilePath = ZenUnit::Random<fs::path>();
   //
   const Utils::FileCopyResult returnedFileCopyResult = _cloudundancyFileCopier.CopyFileToFile(sourceFilePath, destinationFilePath);
   //
   const string expectedCopyingFileMessage = Utils::String::ConcatStrings(
      "Copying ", sourceFilePath.string(), "\n",
      "     to ", destinationFilePath.string(), ". ");
   METALMOCKTHEN(_consoleMock->WriteMock.CalledOnceWith(expectedCopyingFileMessage)).Then(
   METALMOCKTHEN(_cloudundancyFileSystemMock->FileSizeIsGreaterThanOrEqualTo2GBMock.CalledOnceWith(sourceFilePath))).Then(
   METALMOCKTHEN(_fileSystemMock->CopyFileToFileLargerThan2GBMock.CalledOnceWith(sourceFilePath, destinationFilePath)));
   ARE_EQUAL(fileCopyResult, returnedFileCopyResult);
}

TEST(CopyFileToFile_FileSizeIsLessThan2GB_CopiesFileWithCStyleCopyFileToFile_ReturnsFileCopyResult)
{
   _consoleMock->WriteMock.Expect();

   _cloudundancyFileSystemMock->FileSizeIsGreaterThanOrEqualTo2GBMock.Return(false);
   const Utils::FileCopyResult fileCopyResult = _fileSystemMock->CopyFileToFileMock.ReturnRandom();

   const fs::path sourceFilePath = ZenUnit::Random<fs::path>();
   const fs::path destinationFilePath = ZenUnit::Random<fs::path>();
   //
   const Utils::FileCopyResult returnedFileCopyResult = _cloudundancyFileCopier.CopyFileToFile(sourceFilePath, destinationFilePath);
   //
   const string expectedCopyingFileMessage = Utils::String::ConcatStrings(
      "Copying ", sourceFilePath.string(), "\n",
      "     to ", destinationFilePath.string(), ". ");
   METALMOCKTHEN(_consoleMock->WriteMock.CalledOnceWith(expectedCopyingFileMessage)).Then(
   METALMOCKTHEN(_cloudundancyFileSystemMock->FileSizeIsGreaterThanOrEqualTo2GBMock.CalledOnceWith(sourceFilePath))).Then(
   METALMOCKTHEN(_fileSystemMock->CopyFileToFileMock.CalledOnceWith(sourceFilePath, destinationFilePath)));
   ARE_EQUAL(fileCopyResult, returnedFileCopyResult);
}

TEST(CopyFileToFolder_RelativeDestinationFolderPathIsADot_DoesNotJoinDotCharacter_CallsCopyFileToFile)
{
   const Utils::FileCopyResult fileCopyResult = _caller_CopyFileToFileMock->CallConstMemberFunctionMock.ReturnRandom();

   _caller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.Expect();

   CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction = ZenUnit::Random<CloudundancyIniCopyInstruction>();
   cloudundancyIniCopyInstruction.relativeDestinationFolderPath = ".";
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileCopier.CopyFileToFolder(cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   const fs::path& expectedSourceFilePath = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath;
   const fs::path expectedSourceFileName = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath.filename();
   const fs::path expectedDestinationFilePath = destinationFolderPath / expectedSourceFileName;
   METALMOCKTHEN(_caller_CopyFileToFileMock->CallConstMemberFunctionMock.CalledOnceWith(
      &_cloudundancyFileCopier, &CloudundancyFileCopier::CopyFileToFile, expectedSourceFilePath, expectedDestinationFilePath)).Then(
   METALMOCKTHEN(_caller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.CalledOnceWith(
      &_cloudundancyFileCopier, &CloudundancyFileCopier::WriteCopiedMessageOrExitWithCode1IfCopyFailed, fileCopyResult, destinationFolderPath)));
}

TEST(CopyFileToFolder_RelativeDestinationFolderPathIsNotADot_JoinsRelativeDestinationFolder_CallsCopyFileToFile)
{
   const Utils::FileCopyResult fileCopyResult = _caller_CopyFileToFileMock->CallConstMemberFunctionMock.ReturnRandom();

   _caller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.Expect();

   const CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction = ZenUnit::Random<CloudundancyIniCopyInstruction>();
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileCopier.CopyFileToFolder(cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   const fs::path& expectedSourceFilePath = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath;
   const fs::path expectedSourceFileName = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath.filename();
   const fs::path expectedDestinationFilePath =
      destinationFolderPath / cloudundancyIniCopyInstruction.relativeDestinationFolderPath / expectedSourceFileName;
   METALMOCKTHEN(_caller_CopyFileToFileMock->CallConstMemberFunctionMock.CalledOnceWith(
      &_cloudundancyFileCopier, &CloudundancyFileCopier::CopyFileToFile, expectedSourceFilePath, expectedDestinationFilePath)).Then(
   METALMOCKTHEN(_caller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.CalledOnceWith(
      &_cloudundancyFileCopier, &CloudundancyFileCopier::WriteCopiedMessageOrExitWithCode1IfCopyFailed, fileCopyResult, destinationFolderPath)));
}

TEST(WriteCopiedMessageOrExitWithCode1IfCopyFailed_CopySucceeded_WritesCopiedAndDurationInMilliseconds)
{
   _consoleMock->WriteLineColorMock.Expect();
   Utils::FileCopyResult fileCopyResult = ZenUnit::Random<Utils::FileCopyResult>();
   fileCopyResult.copySucceeded = true;
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileCopier.WriteCopiedMessageOrExitWithCode1IfCopyFailed(fileCopyResult, destinationFolderPath);
   //
   const string expectedCopiedMessage = Utils::String::ConcatValues("Copied [", fileCopyResult.durationInMilliseconds, "ms]\n");
   METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedCopiedMessage, Color::Green));
}

TEST(WriteCopiedMessageOrExitWithCode1IfCopyFailed_CopyFailed_WritesCopyFailedAndDurationInMillisecondsAndCopyFailureReason_AppendsErrorToCloudundancyLog_ExitsProgramWithCode1)
{
   _consoleMock->WriteLineColorMock.Expect();
   _cloudundancyLogFileWriterMock->AppendTextToCloudundancyLogFileInFolderMock.Expect();
   _call_quick_exitMock.Expect();
   Utils::FileCopyResult fileCopyResult = ZenUnit::Random<Utils::FileCopyResult>();
   fileCopyResult.copySucceeded = false;
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileCopier.WriteCopiedMessageOrExitWithCode1IfCopyFailed(fileCopyResult, destinationFolderPath);
   //
   const string expectedCopyFailedLogFileMessage = Utils::String::ConcatStrings("File copy failed: ",
      fileCopyResult.sourceFilePath.string(), " -> ", fileCopyResult.destinationFilePath.string(),
      ". Reason: ", fileCopyResult.copyFailureReason);
   const string expectedCopyFailedConsoleMessage = Utils::String::ConcatValues(
      "Copy failed [", fileCopyResult.durationInMilliseconds, "ms]: ", fileCopyResult.copyFailureReason, "\n\n[Cloudundancy] ExitCode: 1");
   METALMOCKTHEN(_cloudundancyLogFileWriterMock->AppendTextToCloudundancyLogFileInFolderMock.CalledOnceWith(destinationFolderPath, expectedCopyFailedLogFileMessage)).Then(
   METALMOCKTHEN(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedCopyFailedConsoleMessage, Color::Red))).Then(
   METALMOCKTHEN(_call_quick_exitMock.CalledOnceWith(1)));
}

RUN_TESTS(CloudundancyFileCopierTests)
