#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyFileCopier.h"
#include "libCloudundancyTests/Components/FileSystem/MetalMock/CloudundancyFileSystemMock.h"
#include "libCloudundancyTests/Components/FileSystem/MetalMock/CloudundancyLogFileWriterMock.h"
#include "libCloudundancyTests/Components/IniFile/MetalMock/CloudundancyIniFileReaderMock.h"

TESTS(CloudundancyFileCopierTests)
AFACT(DefaultConstructor_SetsFunctionsAndNewsComponents)
AFACT(CopyFileToFilesAndFoldersToMultipleDestinationFolders_DeleteDestinationFoldersFirstIsTrue_DeletesDestinationFolders_CopiesFilesAndFoldersToFolders)
// Private Functions
AFACT(CopyFilesAndFoldersToDestinationFolder_TryCatchCallsDoCopyFilesAndFoldersToDestinationFolder)
AFACT(DoCopyFilesAndFoldersToDestinationFolder_AppendBackupStartedToLogFile_CopiesNonSkippedSourceFilesToDestinationFolder_AppendBackupSuccessfulToLogFile)
AFACT(DoCopyFilesAndFoldersToDestinationFolder_AppendBackupStartedToLogFile_CopiesNonSkippedSourceFilesToDestinationFolder_AppendBackupSuccessfulToLogFile)
AFACT(ExceptionHandlerForDoCopyFilesAndFoldersToDestinationFolder_WritesExceptionMessageToConsole_AppendsExceptionMessageToCloudundancyLogFile_RethrowsException)
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
METALMOCK_VOID1_FREE(_call_exit, int)
METALMOCK_NONVOID3_FREE(string, _call_String_ReplaceFirst, const string&, const string&, const string&)
METALMOCK_NONVOID1_FREE(string, _call_Type_GetExceptionClassNameAndMessage, const exception*)

// Function Callers
using _memberCaller_CopyFileToFileFunctionsMockType = Utils::VoidTwoArgMemberFunctionCallerMock<
   CloudundancyFileCopier, const CloudundancyIniCopyInstruction&, const fs::path&>;
_memberCaller_CopyFileToFileFunctionsMockType* _memberCaller_CopyFileToFileFunctionsMock = nullptr;

using _memberCaller_CopyNestedFileToFolderMockType = Utils::VoidThreeArgMemberFunctionCallerMock<
   CloudundancyFileCopier, const fs::path&, const CloudundancyIniCopyInstruction&, const fs::path&>;
_memberCaller_CopyNestedFileToFolderMockType* _memberCaller_CopyNestedFileToFolderMock = nullptr;

using _memberCaller_CopyFileToFileMockType = Utils::NonVoidTwoArgMemberFunctionCallerMock<
   Utils::FileCopyResult, CloudundancyFileCopier, const fs::path&, const fs::path&>;
_memberCaller_CopyFileToFileMockType* _memberCaller_CopyFileToFileMock = nullptr;

using _memberForEacher_CopyEachFileOrFolderToFolderMockType = Utils::OneExtraArgMemberFunctionForEacherMock<
   CloudundancyFileCopier, fs::path, const CloudundancyIni&>;
_memberForEacher_CopyEachFileOrFolderToFolderMockType* _memberForEacher_CopyEachFileOrFolderToFolderMock = nullptr;

using _memberForEacher_CopyFileOrFolderToFolderMockType = Utils::OneExtraArgMemberFunctionForEacherMock<
   CloudundancyFileCopier, CloudundancyIniCopyInstruction, const fs::path&>;
_memberForEacher_CopyFileOrFolderToFolderMockType* _memberForEacher_CopyFileOrFolderToFolderMock = nullptr;

using _memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMockType = Utils::VoidTwoArgMemberFunctionCallerMock<
   CloudundancyFileCopier, const Utils::FileCopyResult&, const fs::path&>;
_memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMockType* _memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock = nullptr;

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
   _cloudundancyFileCopier._call_exit = BIND_1ARG_METALMOCK_OBJECT(_call_exitMock);
   _cloudundancyFileCopier._call_String_ReplaceFirst = BIND_3ARG_METALMOCK_OBJECT(_call_String_ReplaceFirstMock);
   _cloudundancyFileCopier._call_Type_GetExceptionClassNameAndMessage = BIND_1ARG_METALMOCK_OBJECT(_call_Type_GetExceptionClassNameAndMessageMock);
   // Function Callers
   _cloudundancyFileCopier._memberCaller_CopyFileToFileFunctions.reset(_memberCaller_CopyFileToFileFunctionsMock = new _memberCaller_CopyFileToFileFunctionsMockType);
   _cloudundancyFileCopier._memberCaller_CopyNestedFileToFolder.reset(_memberCaller_CopyNestedFileToFolderMock = new _memberCaller_CopyNestedFileToFolderMockType);
   _cloudundancyFileCopier._memberCaller_CopyFileToFile.reset(_memberCaller_CopyFileToFileMock = new _memberCaller_CopyFileToFileMockType);
   _cloudundancyFileCopier._memberForEacher_CopyEachFileOrFolderToFolder.reset(_memberForEacher_CopyEachFileOrFolderToFolderMock = new _memberForEacher_CopyEachFileOrFolderToFolderMockType);
   _cloudundancyFileCopier._memberForEacher_CopyFileOrFolderToFolder.reset(_memberForEacher_CopyFileOrFolderToFolderMock = new _memberForEacher_CopyFileOrFolderToFolderMockType);
   _cloudundancyFileCopier._memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailed.reset(_memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock = new _memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMockType);
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
   STD_FUNCTION_TARGETS(exit, cloudundancyFileCopier._call_exit);
   STD_FUNCTION_TARGETS(Utils::String::ReplaceFirst, cloudundancyFileCopier._call_String_ReplaceFirst);
   STD_FUNCTION_TARGETS(Type::GetExceptionClassNameAndMessage, cloudundancyFileCopier._call_Type_GetExceptionClassNameAndMessage);
   // Function Callers
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._memberCaller_CopyFileToFileFunctions);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._memberCaller_CopyNestedFileToFolder);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._memberCaller_CopyFileToFile);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._memberForEacher_CopyEachFileOrFolderToFolder);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._memberForEacher_CopyFileOrFolderToFolder);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailed);
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

TEST(CopyFileToFilesAndFoldersToMultipleDestinationFolders_DeleteDestinationFoldersFirstIsTrue_DeletesDestinationFolders_CopiesFilesAndFoldersToFolders)
{
   const CloudundancyIni cloudundancyIni = _cloudundancyIniFileReaderMock->ReadIniFileMock.ReturnRandom();

   _consoleMock->WriteLineMock.Expect();
   _consoleMock->WriteLineColorMock.Expect();
   _consoleMock->WriteLinesMock.Expect();

   _cloudundancyFileSystemMock->DeleteMultipleFolderContentsExceptForFileMock.Expect();

   _recursiveDirectoryIteratorMock->SetFileSubpathsToIgnoreMock.Expect();

   _memberForEacher_CopyEachFileOrFolderToFolderMock->CallConstMemberFunctionForEachElementMock.Expect();

   const fs::path iniFilePath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileCopier.CopyFileToFilesAndFoldersToMultipleDestinationFolders(iniFilePath, true);
   //
   const string expectedCopyingMessage = Utils::String::ConcatStrings(
      "[Cloudundancy] Copying [SourceFilesAndFolders] to [DestinationFolders] as listed in ", iniFilePath.string(), ":\n");
   METALMOCKTHEN(_cloudundancyIniFileReaderMock->ReadIniFileMock.CalledOnceWith(iniFilePath)).Then(
   METALMOCKTHEN(_consoleMock->WriteLineMock.CalledOnceWith("[Cloudundancy] Deleting [DestinationFolders] first because --delete-destination-folders-first is specified"))).Then(
   METALMOCKTHEN(_cloudundancyFileSystemMock->DeleteMultipleFolderContentsExceptForFileMock.CalledOnceWith(cloudundancyIni.destinationFolderPaths, "Cloudundancy.log"))).Then(
   METALMOCKTHEN(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedCopyingMessage, Color::Teal))).Then(
   METALMOCKTHEN(_consoleMock->WriteLinesMock.CalledOnceWith(cloudundancyIni.iniFileLines))).Then(
   METALMOCKTHEN(_recursiveDirectoryIteratorMock->SetFileSubpathsToIgnoreMock.CalledOnceWith(cloudundancyIni.fileSubpathsToIgnore))).Then(
   METALMOCKTHEN(_memberForEacher_CopyEachFileOrFolderToFolderMock->CallConstMemberFunctionForEachElementMock.CalledOnceWith(
      cloudundancyIni.destinationFolderPaths,
      &CloudundancyFileCopier::CopyFilesAndFoldersToDestinationFolder,
      &_cloudundancyFileCopier, cloudundancyIni)));
}

TEST(CopyFileToFilesAndFoldersToMultipleDestinationFolders_DeleteDestinationFoldersFirstIsFalse_DoesNotDeleteDestinationFolders_CopiesFilesAndFoldersToFolders)
{
   const CloudundancyIni cloudundancyIni = _cloudundancyIniFileReaderMock->ReadIniFileMock.ReturnRandom();

   _consoleMock->WriteLineMock.Expect();
   _consoleMock->WriteLinesMock.Expect();

   _recursiveDirectoryIteratorMock->SetFileSubpathsToIgnoreMock.Expect();

   _memberForEacher_CopyEachFileOrFolderToFolderMock->CallConstMemberFunctionForEachElementMock.Expect();

   const fs::path iniFilePath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileCopier.CopyFileToFilesAndFoldersToMultipleDestinationFolders(iniFilePath, false);
   //
   const string expectedCopyingMessage = Utils::String::ConcatStrings(
      "[Cloudundancy] Copying [SourceFilesAndFolders] to [DestinationFolders] as listed in ", iniFilePath.string(), ":\n");
   METALMOCKTHEN(_cloudundancyIniFileReaderMock->ReadIniFileMock.CalledOnceWith(iniFilePath)).Then(
   METALMOCKTHEN(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedCopyingMessage, Color::Teal))).Then(
   METALMOCKTHEN(_consoleMock->WriteLinesMock.CalledOnceWith(cloudundancyIni.iniFileLines))).Then(
   METALMOCKTHEN(_recursiveDirectoryIteratorMock->SetFileSubpathsToIgnoreMock.CalledOnceWith(cloudundancyIni.fileSubpathsToIgnore))).Then(
   METALMOCKTHEN(_memberForEacher_CopyEachFileOrFolderToFolderMock->CallConstMemberFunctionForEachElementMock.CalledOnceWith(
      cloudundancyIni.destinationFolderPaths,
      &CloudundancyFileCopier::CopyFilesAndFoldersToDestinationFolder,
      &_cloudundancyFileCopier, cloudundancyIni)));
}

// Private Functions

TEST(CopyFilesAndFoldersToDestinationFolder_TryCatchCallsDoCopyFilesAndFoldersToDestinationFolder)
{
   _tryCatchCallerMock->TryCatchCallConstMemberFunctionMock.Expect();
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   const CloudundancyIni cloudundancyIni = ZenUnit::Random<CloudundancyIni>();
   //
   _cloudundancyFileCopier.CopyFilesAndFoldersToDestinationFolder(destinationFolderPath, cloudundancyIni);
   //
   const pair<fs::path, CloudundancyIni> expectedDestinationFolderPath_cloudundancyIni =
      make_pair(destinationFolderPath, cloudundancyIni);
   METALMOCK(_tryCatchCallerMock->TryCatchCallConstMemberFunctionMock.CalledOnceWith(
      &_cloudundancyFileCopier, &CloudundancyFileCopier::DoCopyFilesAndFoldersToDestinationFolder,
      expectedDestinationFolderPath_cloudundancyIni,
      &CloudundancyFileCopier::ExceptionHandlerForDoCopyFilesAndFoldersToDestinationFolder));
}

TEST(DoCopyFilesAndFoldersToDestinationFolder_AppendBackupStartedToLogFile_CopiesNonSkippedSourceFilesToDestinationFolder_AppendBackupSuccessfulToLogFile)
{
   _consoleMock->WriteLineMock.Expect();
   _consoleMock->WriteLineColorMock.Expect();

   _cloudundancyLogFileWriterMock->AppendTextToCloudundancyLogFileInFolderMock.Expect();

   _stopwatchMock->StartMock.Expect();

   _memberForEacher_CopyFileOrFolderToFolderMock->CallConstMemberFunctionForEachElementMock.Expect();

   const string elapsedSeconds = _stopwatchMock->StopAndGetElapsedSecondsMock.ReturnRandom();

   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   const CloudundancyIni cloudundancyIni = ZenUnit::Random<CloudundancyIni>();
   const pair<fs::path, CloudundancyIni> destinationFolderPath_cloudundancyIni = make_pair(destinationFolderPath, cloudundancyIni);
   //
   _cloudundancyFileCopier.DoCopyFilesAndFoldersToDestinationFolder(destinationFolderPath_cloudundancyIni);
   //
   METALMOCK(_consoleMock->WriteLineColorMock.CalledNTimes(2));
   METALMOCK(_cloudundancyLogFileWriterMock->AppendTextToCloudundancyLogFileInFolderMock.CalledNTimes(2));
   const string expectedCopyingMessage = Utils::String::ConcatStrings(
      "\n[Cloudundancy] Copying [SourceFilesAndFolders] to destination folder ", destinationFolderPath.string(), ":\n");
   const string expectedFolderBackupResultSuccessMessage = Utils::String::ConcatStrings(
      "[Cloudundancy]   FolderBackupResult: Successfully copied [SourceFilesAndFolders] to ", destinationFolderPath.string());
   const string expectedFolderBackupDurationMessage = Utils::String::ConcatStrings("[Cloudundancy] FolderBackupDuration: ", elapsedSeconds, " seconds");
   const string expectedBackupSuccessfulLogFileMessage = Utils::String::ConcatStrings("Cloudundancy backup successful in ", elapsedSeconds, " seconds");
   METALMOCKTHEN(_consoleMock->WriteLineColorMock.CalledWith(expectedCopyingMessage, Color::Teal)).Then(
   METALMOCKTHEN(_cloudundancyLogFileWriterMock->AppendTextToCloudundancyLogFileInFolderMock.CalledWith(destinationFolderPath, "Cloudundancy backup started"))).Then(
   METALMOCKTHEN(_stopwatchMock->StartMock.CalledOnce())).Then(
   METALMOCKTHEN(_memberForEacher_CopyFileOrFolderToFolderMock->CallConstMemberFunctionForEachElementMock.CalledOnceWith(
      cloudundancyIni.cloudundancyIniCopyInstructions,
      &CloudundancyFileCopier::CopyFileOrFolderToFolder,
      &_cloudundancyFileCopier, destinationFolderPath))).Then(
   METALMOCKTHEN(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce())).Then(
   METALMOCKTHEN(_consoleMock->WriteLineColorMock.CalledWith(expectedFolderBackupResultSuccessMessage, Color::Green))).Then(
   METALMOCKTHEN(_consoleMock->WriteLineMock.CalledOnceWith(expectedFolderBackupDurationMessage))).Then(
   METALMOCKTHEN(_cloudundancyLogFileWriterMock->AppendTextToCloudundancyLogFileInFolderMock.CalledWith(destinationFolderPath, expectedBackupSuccessfulLogFileMessage)));
}

TEST(ExceptionHandlerForDoCopyFilesAndFoldersToDestinationFolder_WritesExceptionMessageToConsole_AppendsExceptionMessageToCloudundancyLogFile_RethrowsException)
{
   const string exceptionClassNameAndMessage = _call_Type_GetExceptionClassNameAndMessageMock.ReturnRandom();

   _cloudundancyLogFileWriterMock->AppendTextToCloudundancyLogFileInFolderMock.Expect();

   const string exceptionMessage = ZenUnit::Random<string>();
   const runtime_error ex(exceptionMessage);

   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   const CloudundancyIni cloudundancyIni = ZenUnit::Random<CloudundancyIni>();
   const pair<fs::path, CloudundancyIni> destinationFolderPath_cloudundancyIni = make_pair(destinationFolderPath, cloudundancyIni);
   //
   THROWS_EXCEPTION(_cloudundancyFileCopier.ExceptionHandlerForDoCopyFilesAndFoldersToDestinationFolder(
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
   _memberCaller_CopyFileToFileFunctionsMock->CallConstMemberFunctionMock.Expect();
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   const CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction =
      ZenUnit::Random<CloudundancyIniCopyInstruction>();
   //
   _cloudundancyFileCopier.CopyFileOrFolderToFolder(cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   METALMOCK(_memberCaller_CopyFileToFileFunctionsMock->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyFileCopier::CopyFileToFolder,
      &_cloudundancyFileCopier, cloudundancyIniCopyInstruction, destinationFolderPath));
}

TEST1X1(CopyFileOrFolderToFolder_SourcePathDoesNotHaveAFileNameMeaningItIsAFolder_CallsRecursivelyCopyNonIgnoredFilesToFolder,
   const fs::path& sourceFileOrFolderPath,
   "FolderNameA/",
   "FolderNameB\\")
{
   _memberCaller_CopyFileToFileFunctionsMock->CallConstMemberFunctionMock.Expect();
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction = ZenUnit::Random<CloudundancyIniCopyInstruction>();
   cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath = sourceFileOrFolderPath;
   //
   _cloudundancyFileCopier.CopyFileOrFolderToFolder(cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   METALMOCK(_memberCaller_CopyFileToFileFunctionsMock->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyFileCopier::CopyNonIgnoredFilesInAndBelowFolderToFolder,
      &_cloudundancyFileCopier, cloudundancyIniCopyInstruction, destinationFolderPath));
}

TEST(CopyNonIgnoredFilesInAndBelowFolderToFolder_CopiesNonIgnoredFilesToFolderUntilRecursiveDirectoryIteratorReturnsNoMoreFiles)
{
   _recursiveDirectoryIteratorMock->InitializeIteratorAtFolderPathMock.Expect();

   const fs::path nonIgnoredSourceFilePath1 = ZenUnit::Random<fs::path>();
   const fs::path nonIgnoredSourceFilePath2 = ZenUnit::Random<fs::path>();
   const fs::path terminatorFilePath;
   _recursiveDirectoryIteratorMock->NextNonIgnoredFilePathMock.ReturnValues(
      nonIgnoredSourceFilePath1, nonIgnoredSourceFilePath2, terminatorFilePath);

   _memberCaller_CopyNestedFileToFolderMock->ConstCallMock.Expect();

   const CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction = ZenUnit::Random<CloudundancyIniCopyInstruction>();
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileCopier.CopyNonIgnoredFilesInAndBelowFolderToFolder(cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   METALMOCK(_recursiveDirectoryIteratorMock->NextNonIgnoredFilePathMock.CalledNTimes(3));
   METALMOCK(_memberCaller_CopyNestedFileToFolderMock->ConstCallMock.CalledNTimes(2));

   METALMOCKTHEN(_recursiveDirectoryIteratorMock->InitializeIteratorAtFolderPathMock.
      CalledOnceWith(cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath)).Then(

   METALMOCKTHEN(_recursiveDirectoryIteratorMock->NextNonIgnoredFilePathMock.Called())).Then(
   METALMOCKTHEN(_memberCaller_CopyNestedFileToFolderMock->ConstCallMock.CalledWith(
      &CloudundancyFileCopier::CopyNestedFileToFolder, &_cloudundancyFileCopier, nonIgnoredSourceFilePath1, cloudundancyIniCopyInstruction, destinationFolderPath))).Then(

   METALMOCKTHEN(_recursiveDirectoryIteratorMock->NextNonIgnoredFilePathMock.Called())).Then(
   METALMOCKTHEN(_memberCaller_CopyNestedFileToFolderMock->ConstCallMock.CalledWith(
      &CloudundancyFileCopier::CopyNestedFileToFolder, &_cloudundancyFileCopier, nonIgnoredSourceFilePath2, cloudundancyIniCopyInstruction, destinationFolderPath))).Then(

   METALMOCKTHEN(_recursiveDirectoryIteratorMock->NextNonIgnoredFilePathMock.Called()));
}

TEST(CopyNestedFileToFolder_RelativeDestinationFolderPathIsDot_CopiesNestedFileToFolderWithSlashDotSlashNotPresentInTheDestinationFilePath)
{
   const fs::path sourceFilePathRelativeToSourceFolderPath = _call_String_ReplaceFirstMock.ReturnRandom();

   const Utils::FileCopyResult fileCopyResult = _memberCaller_CopyFileToFileMock->CallConstMemberFunctionMock.ReturnRandom();

   _memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.Expect();

   const fs::path sourceFilePath = ZenUnit::Random<fs::path>();
   CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction = ZenUnit::Random<CloudundancyIniCopyInstruction>();
   cloudundancyIniCopyInstruction.relativeDestinationFolderPath = ".";
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileCopier.CopyNestedFileToFolder(sourceFilePath, cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   METALMOCK(_call_String_ReplaceFirstMock.CalledOnceWith(
      sourceFilePath.string(), cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath.string(), ""));
   const fs::path expectedDestinationFilePath =
      destinationFolderPath /
      sourceFilePathRelativeToSourceFolderPath;
   METALMOCK(_memberCaller_CopyFileToFileMock->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyFileCopier::CopyFileToFile, &_cloudundancyFileCopier, sourceFilePath, expectedDestinationFilePath));
   METALMOCK(_memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyFileCopier::WriteCopiedMessageOrExitWithCode1IfCopyFailed, &_cloudundancyFileCopier, fileCopyResult, destinationFolderPath));
}

TEST(CopyNestedFileToFolder_RelativeDestinationFolderPathIsNotDot_CopiesNestedFileToFolderWithRelativeDestinationFolderPathPresentInTheDestinationFilePath)
{
   const fs::path sourceFilePathRelativeToSourceFolderPath = _call_String_ReplaceFirstMock.ReturnRandom();

   const Utils::FileCopyResult fileCopyResult = _memberCaller_CopyFileToFileMock->CallConstMemberFunctionMock.ReturnRandom();

   _memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.Expect();

   const fs::path sourceFilePath = ZenUnit::Random<fs::path>();
   const CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction = ZenUnit::Random<CloudundancyIniCopyInstruction>();
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileCopier.CopyNestedFileToFolder(sourceFilePath, cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   METALMOCK(_call_String_ReplaceFirstMock.CalledOnceWith(
      sourceFilePath.string(), cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath.string(), ""));
   const fs::path expectedDestinationFilePath =
      destinationFolderPath /
      cloudundancyIniCopyInstruction.relativeDestinationFolderPath /
      sourceFilePathRelativeToSourceFolderPath;
   METALMOCK(_memberCaller_CopyFileToFileMock->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyFileCopier::CopyFileToFile, &_cloudundancyFileCopier, sourceFilePath, expectedDestinationFilePath));
   METALMOCK(_memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyFileCopier::WriteCopiedMessageOrExitWithCode1IfCopyFailed, &_cloudundancyFileCopier, fileCopyResult, destinationFolderPath));
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
   const Utils::FileCopyResult fileCopyResult = _memberCaller_CopyFileToFileMock->CallConstMemberFunctionMock.ReturnRandom();

   _memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.Expect();

   CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction = ZenUnit::Random<CloudundancyIniCopyInstruction>();
   cloudundancyIniCopyInstruction.relativeDestinationFolderPath = ".";
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileCopier.CopyFileToFolder(cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   const fs::path& expectedSourceFilePath = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath;
   const fs::path expectedSourceFileName = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath.filename();
   const fs::path expectedDestinationFilePath = destinationFolderPath / expectedSourceFileName;
   METALMOCKTHEN(_memberCaller_CopyFileToFileMock->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyFileCopier::CopyFileToFile, &_cloudundancyFileCopier, expectedSourceFilePath, expectedDestinationFilePath)).Then(
   METALMOCKTHEN(_memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyFileCopier::WriteCopiedMessageOrExitWithCode1IfCopyFailed, &_cloudundancyFileCopier, fileCopyResult, destinationFolderPath)));
}

TEST(CopyFileToFolder_RelativeDestinationFolderPathIsNotADot_JoinsRelativeDestinationFolder_CallsCopyFileToFile)
{
   const Utils::FileCopyResult fileCopyResult = _memberCaller_CopyFileToFileMock->CallConstMemberFunctionMock.ReturnRandom();

   _memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.Expect();

   const CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction = ZenUnit::Random<CloudundancyIniCopyInstruction>();
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileCopier.CopyFileToFolder(cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   const fs::path& expectedSourceFilePath = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath;
   const fs::path expectedSourceFileName = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath.filename();
   const fs::path expectedDestinationFilePath =
      destinationFolderPath / cloudundancyIniCopyInstruction.relativeDestinationFolderPath / expectedSourceFileName;
   METALMOCKTHEN(_memberCaller_CopyFileToFileMock->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyFileCopier::CopyFileToFile, &_cloudundancyFileCopier, expectedSourceFilePath, expectedDestinationFilePath)).Then(
   METALMOCKTHEN(_memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyFileCopier::WriteCopiedMessageOrExitWithCode1IfCopyFailed, &_cloudundancyFileCopier, fileCopyResult, destinationFolderPath)));
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
   _call_exitMock.Expect();
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
   METALMOCKTHEN(_cloudundancyLogFileWriterMock->AppendTextToCloudundancyLogFileInFolderMock.CalledOnceWith(
      destinationFolderPath, expectedCopyFailedLogFileMessage)).Then(
   METALMOCKTHEN(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedCopyFailedConsoleMessage, Color::Red))).Then(
   METALMOCKTHEN(_call_exitMock.CalledOnceWith(1)));
}

RUN_TESTS(CloudundancyFileCopierTests)
