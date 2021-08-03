#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyFileCopier.h"
#include "libCloudundancyTests/Components/FileSystem/MetalMock/CloudundancyFileSystemMock.h"
#include "libCloudundancyTests/Components/FileSystem/MetalMock/CloudundancyLogFileWriterMock.h"
#include "libCloudundancyTests/Components/IniFile/MetalMock/CloudundancyIniFileReaderMock.h"

TESTS(CloudundancyFileCopierTests)
AFACT(DefaultConstructor_SetsFunctionsAndNewsComponents)
AFACT(CopyFileFastsAndFoldersToMultipleDestinationFolders_DeleteDestinationFoldersFirstIsTrue_DeletesDestinationFolders_CopiesFilesAndFoldersToFolders)
// Private Functions
AFACT(CopyFileFastsAndFoldersToDestinationFolder_TryCatchCallsDoCopyFileFastsAndFoldersToDestinationFolder)
AFACT(DoCopyFileFastsAndFoldersToDestinationFolder_AppendBackupStartedToLogFile_CopiesNonSkippedSourceFilesToDestinationFolder_AppendBackupSuccessfulToLogFile)
AFACT(DoCopyFileFastsAndFoldersToDestinationFolder_AppendBackupStartedToLogFile_CopiesNonSkippedSourceFilesToDestinationFolder_AppendBackupSuccessfulToLogFile)
AFACT(ExceptionHandlerForDoCopyFileFastsAndFoldersToDestinationFolder_WritesExceptionMessageToConsole_AppendsExceptionMessageToCloudundancyLogFile_RethrowsException)
AFACT(CopyFileFastOrFolderToFolder_SourcePathHasAFileName_CallsCopyFileFastToFolder)
FACTS(CopyFileFastOrFolderToFolder_SourcePathDoesNotHaveAFileNameMeaningItIsAFolder_CallsRecursivelyCopyNonIgnoredFilesToFolder)
AFACT(CopyNonIgnoredFilesInAndBelowFolderToFolder_CopiesNonIgnoredFilesToFolderUntilRecursiveDirectoryIteratorReturnsNoMoreFiles)
AFACT(CopyNestedFileToFolder_RelativeDestinationFolderPathIsDot_CopiesNestedFileToFolderWithSlashDotSlashNotPresentInTheDestinationFilePath)
AFACT(CopyNestedFileToFolder_RelativeDestinationFolderPathIsNotDot_CopiesNestedFileToFolderWithRelativeDestinationFolderPathPresentInTheDestinationFilePath)
AFACT(CopyFileFast_FileSizeIsGreaterThanOrEqualTo2GB_CopiesFileWithStdFilesystemCopyFileFast_ReturnsFileCopyResult)
AFACT(CopyFileFast_FileSizeIsLessThan2GB_CopiesFileWithCStyleCopyFileFast_ReturnsFileCopyResult)
AFACT(CopyFileFastToFolder_RelativeDestinationFolderPathIsADot_DoesNotJoinDotCharacter_CallsCopyFileFast)
AFACT(CopyFileFastToFolder_RelativeDestinationFolderPathIsNotADot_JoinsRelativeDestinationFolder_CallsCopyFileFast)
AFACT(WriteCopiedMessageOrExitWithCode1IfCopyFailed_CopySucceeded_WritesCopiedAndDurationInMilliseconds)
AFACT(WriteCopiedMessageOrExitWithCode1IfCopyFailed_CopyFailed_WritesCopyFailedAndDurationInMillisecondsAndCopyFailureReason_AppendsErrorToCloudundancyLog_ExitsProgramWithCode1)
EVIDENCE

CloudundancyFileCopier _cloudundancyFileCopier;

// Function Pointers
METALMOCK_VOID1_FREE(_call_exit, int)
METALMOCK_NONVOID3_STATIC(string, String, _call_String_ReplaceFirst, const string&, const string&, const string&)
METALMOCK_NONVOID1_STATIC(string, Type, _call_Type_GetExceptionClassNameAndMessage, const exception*)

// Function Callers
using _memberCaller_CopyFileFastFunctionsMockType = Utils::VoidTwoArgMemberFunctionCallerMock<
   CloudundancyFileCopier, const CloudundancyIniCopyInstruction&, const fs::path&>;
_memberCaller_CopyFileFastFunctionsMockType* _memberCaller_CopyFileFastFunctionsMock = nullptr;

using _memberCaller_CopyNestedFileToFolderMockType = Utils::VoidThreeArgMemberFunctionCallerMock<
   CloudundancyFileCopier, const fs::path&, const CloudundancyIniCopyInstruction&, const fs::path&>;
_memberCaller_CopyNestedFileToFolderMockType* _memberCaller_CopyNestedFileToFolderMock = nullptr;

using _memberCaller_CopyFileFastMockType = Utils::NonVoidTwoArgMemberFunctionCallerMock<
   Utils::FileCopyResult, CloudundancyFileCopier, const fs::path&, const fs::path&>;
_memberCaller_CopyFileFastMockType* _memberCaller_CopyFileFastMock = nullptr;

using _memberForEacher_CopyEachFileOrFolderToFolderMockType = Utils::OneExtraArgMemberFunctionForEacherMock<
   CloudundancyFileCopier, fs::path, const CloudundancyIni&>;
_memberForEacher_CopyEachFileOrFolderToFolderMockType* _memberForEacher_CopyEachFileOrFolderToFolderMock = nullptr;

using _memberForEacher_CopyFileFastOrFolderToFolderMockType = Utils::OneExtraArgMemberFunctionForEacherMock<
   CloudundancyFileCopier, CloudundancyIniCopyInstruction, const fs::path&>;
_memberForEacher_CopyFileFastOrFolderToFolderMockType* _memberForEacher_CopyFileFastOrFolderToFolderMock = nullptr;

using _memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMockType = Utils::VoidTwoArgMemberFunctionCallerMock<
   CloudundancyFileCopier, const Utils::FileCopyResult&, const fs::path&>;
_memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMockType* _memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock = nullptr;

// Constant Components
CloudundancyIniFileReaderMock* _cloudundancyIniFileReaderMock = nullptr;
CloudundancyFileSystemMock* _cloudundancyFileSystemMock = nullptr;
CloudundancyLogFileWriterMock* _cloudundancyLogFileWriterMock = nullptr;
Utils::ConsoleMock* _consoleMock = nullptr;
Utils::RawFileSystemMock* _rawFileSystemMock = nullptr;
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
   _cloudundancyFileCopier._memberCaller_CopyFileFastFunctions.reset(_memberCaller_CopyFileFastFunctionsMock = new _memberCaller_CopyFileFastFunctionsMockType);
   _cloudundancyFileCopier._memberCaller_CopyNestedFileToFolder.reset(_memberCaller_CopyNestedFileToFolderMock = new _memberCaller_CopyNestedFileToFolderMockType);
   _cloudundancyFileCopier._memberCaller_CopyFileFast.reset(_memberCaller_CopyFileFastMock = new _memberCaller_CopyFileFastMockType);
   _cloudundancyFileCopier._memberForEacher_CopyEachFileOrFolderToFolder.reset(_memberForEacher_CopyEachFileOrFolderToFolderMock = new _memberForEacher_CopyEachFileOrFolderToFolderMockType);
   _cloudundancyFileCopier._memberForEacher_CopyFileFastOrFolderToFolder.reset(_memberForEacher_CopyFileFastOrFolderToFolderMock = new _memberForEacher_CopyFileFastOrFolderToFolderMockType);
   _cloudundancyFileCopier._memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailed.reset(_memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock = new _memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMockType);
   // Constant Components
   _cloudundancyFileCopier._cloudundancyFileSystem.reset(_cloudundancyFileSystemMock = new CloudundancyFileSystemMock);
   _cloudundancyFileCopier._cloudundancyIniFileReader.reset(_cloudundancyIniFileReaderMock = new CloudundancyIniFileReaderMock);
   _cloudundancyFileCopier._cloudundancyLogFileWriter.reset(_cloudundancyLogFileWriterMock = new CloudundancyLogFileWriterMock);
   _cloudundancyFileCopier._console.reset(_consoleMock = new Utils::ConsoleMock);
   _cloudundancyFileCopier._rawFileSystem.reset(_rawFileSystemMock = new Utils::RawFileSystemMock);
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
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._memberCaller_CopyFileFastFunctions);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._memberCaller_CopyNestedFileToFolder);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._memberCaller_CopyFileFast);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._memberForEacher_CopyEachFileOrFolderToFolder);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._memberForEacher_CopyFileFastOrFolderToFolder);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailed);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._cloudundancyFileSystem);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._cloudundancyIniFileReader);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._console);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._rawFileSystem);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._tryCatchCaller);
   // Mutable Components
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._recursiveDirectoryIterator);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._stopwatch);
}

TEST(CopyFileFastsAndFoldersToMultipleDestinationFolders_DeleteDestinationFoldersFirstIsTrue_DeletesDestinationFolders_CopiesFilesAndFoldersToFolders)
{
   const CloudundancyIni cloudundancyIni = _cloudundancyIniFileReaderMock->ReadIniFileMock.ReturnRandom();

   _consoleMock->WriteLineMock.Expect();
   _consoleMock->WriteLineColorMock.Expect();
   _consoleMock->WriteLinesMock.Expect();

   _recursiveDirectoryIteratorMock->SetFileSubpathsToIgnoreMock.Expect();

   _memberForEacher_CopyEachFileOrFolderToFolderMock->CallConstMemberFunctionForEachElementMock.Expect();

   _cloudundancyFileSystemMock->DeleteMultipleFolderContentsExceptForFileMock.Expect();

   const fs::path iniFilePath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileCopier.CopyFileFastsAndFoldersToMultipleDestinationFolders(iniFilePath, true);
   //
   METALMOCK(_cloudundancyIniFileReaderMock->ReadIniFileMock.CalledOnceWith(iniFilePath));
   const string expectedCopyingMessage = Utils::String::ConcatStrings(
      "[Cloudundancy] Copying [SourceFilesAndFolders] to [DestinationFolders] as listed in ", iniFilePath.string(), ":\n");
   METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedCopyingMessage, Color::Teal));
   METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(
      "[Cloudundancy] Deleting [DestinationFolders] first because --delete-destination-folders-first is specified"));
   METALMOCK(_cloudundancyFileSystemMock->DeleteMultipleFolderContentsExceptForFileMock.CalledOnceWith(cloudundancyIni.destinationFolderPaths, "Cloudundancy.log"));
   METALMOCK(_consoleMock->WriteLinesMock.CalledOnceWith(cloudundancyIni.iniFileLines));
   METALMOCK(_recursiveDirectoryIteratorMock->SetFileSubpathsToIgnoreMock.CalledOnceWith(cloudundancyIni.fileSubpathsToIgnore));
   METALMOCK(_memberForEacher_CopyEachFileOrFolderToFolderMock->CallConstMemberFunctionForEachElementMock.CalledOnceWith(
      cloudundancyIni.destinationFolderPaths,
      &CloudundancyFileCopier::CopyFileFastsAndFoldersToDestinationFolder,
      &_cloudundancyFileCopier, cloudundancyIni));
}

TEST(CopyFileFastsAndFoldersToMultipleDestinationFolders_DeleteDestinationFoldersFirstIsFalse_DoesNotDeleteDestinationFolders_CopiesFilesAndFoldersToFolders)
{
   const CloudundancyIni cloudundancyIni = _cloudundancyIniFileReaderMock->ReadIniFileMock.ReturnRandom();

   _consoleMock->WriteLineMock.Expect();
   _consoleMock->WriteLinesMock.Expect();

   _recursiveDirectoryIteratorMock->SetFileSubpathsToIgnoreMock.Expect();

   _memberForEacher_CopyEachFileOrFolderToFolderMock->CallConstMemberFunctionForEachElementMock.Expect();

   const fs::path iniFilePath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileCopier.CopyFileFastsAndFoldersToMultipleDestinationFolders(iniFilePath, false);
   //
   METALMOCK(_cloudundancyIniFileReaderMock->ReadIniFileMock.CalledOnceWith(iniFilePath));
   const string expectedCopyingMessage = Utils::String::ConcatStrings(
      "[Cloudundancy] Copying [SourceFilesAndFolders] to [DestinationFolders] as listed in ", iniFilePath.string(), ":\n");
   METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedCopyingMessage, Color::Teal));
   METALMOCK(_consoleMock->WriteLinesMock.CalledOnceWith(cloudundancyIni.iniFileLines));
   METALMOCK(_recursiveDirectoryIteratorMock->SetFileSubpathsToIgnoreMock.CalledOnceWith(cloudundancyIni.fileSubpathsToIgnore));
   METALMOCK(_memberForEacher_CopyEachFileOrFolderToFolderMock->CallConstMemberFunctionForEachElementMock.CalledOnceWith(
      cloudundancyIni.destinationFolderPaths,
      &CloudundancyFileCopier::CopyFileFastsAndFoldersToDestinationFolder,
      &_cloudundancyFileCopier, cloudundancyIni));
}

// Private Functions

TEST(CopyFileFastsAndFoldersToDestinationFolder_TryCatchCallsDoCopyFileFastsAndFoldersToDestinationFolder)
{
   _tryCatchCallerMock->TryCatchCallConstMemberFunctionMock.Expect();
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   const CloudundancyIni cloudundancyIni = ZenUnit::Random<CloudundancyIni>();
   //
   _cloudundancyFileCopier.CopyFileFastsAndFoldersToDestinationFolder(destinationFolderPath, cloudundancyIni);
   //
   const pair<fs::path, CloudundancyIni> expectedDestinationFolderPath_cloudundancyIni =
      make_pair(destinationFolderPath, cloudundancyIni);
   METALMOCK(_tryCatchCallerMock->TryCatchCallConstMemberFunctionMock.CalledOnceWith(
      &_cloudundancyFileCopier, &CloudundancyFileCopier::DoCopyFileFastsAndFoldersToDestinationFolder,
      expectedDestinationFolderPath_cloudundancyIni,
      &CloudundancyFileCopier::ExceptionHandlerForDoCopyFileFastsAndFoldersToDestinationFolder));
}

TEST(DoCopyFileFastsAndFoldersToDestinationFolder_AppendBackupStartedToLogFile_CopiesNonSkippedSourceFilesToDestinationFolder_AppendBackupSuccessfulToLogFile)
{
   _consoleMock->WriteLineMock.Expect();
   _consoleMock->WriteLineColorMock.Expect();

   _cloudundancyLogFileWriterMock->AppendTextToCloudundancyLogFileInFolderMock.Expect();

   _stopwatchMock->StartMock.Expect();

   _memberForEacher_CopyFileFastOrFolderToFolderMock->CallConstMemberFunctionForEachElementMock.Expect();

   const string elapsedSeconds = _stopwatchMock->StopAndGetElapsedSecondsMock.ReturnRandom();

   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   const CloudundancyIni cloudundancyIni = ZenUnit::Random<CloudundancyIni>();
   const pair<fs::path, CloudundancyIni> destinationFolderPath_cloudundancyIni = make_pair(destinationFolderPath, cloudundancyIni);
   //
   _cloudundancyFileCopier.DoCopyFileFastsAndFoldersToDestinationFolder(destinationFolderPath_cloudundancyIni);
   //
   const string expectedCopyingMessage = Utils::String::ConcatStrings(
      "\n[Cloudundancy] Copying [SourceFilesAndFolders] to destination folder ", destinationFolderPath.string(), ":\n");
   const string expectedFolderBackupResultSuccessMessage = Utils::String::ConcatStrings(
      "[Cloudundancy]   FolderBackupResult: Successfully copied [SourceFilesAndFolders] to ", destinationFolderPath.string());
   METALMOCK(_consoleMock->WriteLineColorMock.CalledAsFollows(
   {
      { expectedCopyingMessage, Color::Teal },
      { expectedFolderBackupResultSuccessMessage, Color::Green }
   }));
   const string expectedFolderBackupDurationMessage = Utils::String::ConcatStrings("[Cloudundancy] FolderBackupDuration: ", elapsedSeconds, " seconds");
   METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(expectedFolderBackupDurationMessage));
   const string expectedBackupSuccessfulLogFileMessage = Utils::String::ConcatStrings("Cloudundancy backup successful in ", elapsedSeconds, " seconds");
   METALMOCK(_cloudundancyLogFileWriterMock->AppendTextToCloudundancyLogFileInFolderMock.CalledAsFollows(
   {
      { destinationFolderPath, "Cloudundancy backup started" },
      { destinationFolderPath, expectedBackupSuccessfulLogFileMessage }
   }));
   METALMOCK(_stopwatchMock->StartMock.CalledOnce());
   METALMOCK(_memberForEacher_CopyFileFastOrFolderToFolderMock->CallConstMemberFunctionForEachElementMock.CalledOnceWith(
      cloudundancyIni.cloudundancyIniCopyInstructions,
      &CloudundancyFileCopier::CopyFileFastOrFolderToFolder,
      &_cloudundancyFileCopier, destinationFolderPath));
   METALMOCK(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce());
}

TEST(ExceptionHandlerForDoCopyFileFastsAndFoldersToDestinationFolder_WritesExceptionMessageToConsole_AppendsExceptionMessageToCloudundancyLogFile_RethrowsException)
{
   const string exceptionClassNameAndMessage = _call_Type_GetExceptionClassNameAndMessageMock.ReturnRandom();

   _cloudundancyLogFileWriterMock->AppendTextToCloudundancyLogFileInFolderMock.Expect();

   const string exceptionMessage = ZenUnit::Random<string>();
   const runtime_error ex(exceptionMessage);

   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   const CloudundancyIni cloudundancyIni = ZenUnit::Random<CloudundancyIni>();
   const pair<fs::path, CloudundancyIni> destinationFolderPath_cloudundancyIni = make_pair(destinationFolderPath, cloudundancyIni);
   //
   THROWS_EXCEPTION(_cloudundancyFileCopier.ExceptionHandlerForDoCopyFileFastsAndFoldersToDestinationFolder(
      ex, destinationFolderPath_cloudundancyIni),
      runtime_error, exceptionClassNameAndMessage);
   //
   METALMOCK(_call_Type_GetExceptionClassNameAndMessageMock.CalledOnceWith(&ex));
   const string expectedErrorMessage = Utils::String::ConcatStrings(
      "Exception thrown while copying files to destination folder ", destinationFolderPath.string(), ": ", exceptionClassNameAndMessage);
   METALMOCK(_cloudundancyLogFileWriterMock->AppendTextToCloudundancyLogFileInFolderMock.CalledOnceWith(
      destinationFolderPath, expectedErrorMessage));
}

TEST(CopyFileFastOrFolderToFolder_SourcePathHasAFileName_CallsCopyFileFastToFolder)
{
   _memberCaller_CopyFileFastFunctionsMock->CallConstMemberFunctionMock.Expect();
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   const CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction =
      ZenUnit::Random<CloudundancyIniCopyInstruction>();
   //
   _cloudundancyFileCopier.CopyFileFastOrFolderToFolder(cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   METALMOCK(_memberCaller_CopyFileFastFunctionsMock->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyFileCopier::CopyFileFastToFolder,
      &_cloudundancyFileCopier, cloudundancyIniCopyInstruction, destinationFolderPath));
}

TEST1X1(CopyFileFastOrFolderToFolder_SourcePathDoesNotHaveAFileNameMeaningItIsAFolder_CallsRecursivelyCopyNonIgnoredFilesToFolder,
   const fs::path& sourceFileOrFolderPath,
   "FolderNameA/",
   "FolderNameB\\")
{
   _memberCaller_CopyFileFastFunctionsMock->CallConstMemberFunctionMock.Expect();
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction = ZenUnit::Random<CloudundancyIniCopyInstruction>();
   cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath = sourceFileOrFolderPath;
   //
   _cloudundancyFileCopier.CopyFileFastOrFolderToFolder(cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   METALMOCK(_memberCaller_CopyFileFastFunctionsMock->CallConstMemberFunctionMock.CalledOnceWith(
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
   METALMOCK(_recursiveDirectoryIteratorMock->InitializeIteratorAtFolderPathMock.
      CalledOnceWith(cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath));
   METALMOCK(_recursiveDirectoryIteratorMock->NextNonIgnoredFilePathMock.CalledNTimes(3));
   METALMOCK(_memberCaller_CopyNestedFileToFolderMock->ConstCallMock.CalledAsFollows(
   {
      { &CloudundancyFileCopier::CopyNestedFileToFolder, &_cloudundancyFileCopier, nonIgnoredSourceFilePath1, cloudundancyIniCopyInstruction, destinationFolderPath },
      { &CloudundancyFileCopier::CopyNestedFileToFolder, &_cloudundancyFileCopier, nonIgnoredSourceFilePath2, cloudundancyIniCopyInstruction, destinationFolderPath }
   }));
}

TEST(CopyNestedFileToFolder_RelativeDestinationFolderPathIsDot_CopiesNestedFileToFolderWithSlashDotSlashNotPresentInTheDestinationFilePath)
{
   const fs::path sourceFilePathRelativeToSourceFolderPath = _call_String_ReplaceFirstMock.ReturnRandom();

   const Utils::FileCopyResult fileCopyResult = _memberCaller_CopyFileFastMock->CallConstMemberFunctionMock.ReturnRandom();

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
   METALMOCK(_memberCaller_CopyFileFastMock->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyFileCopier::CopyFileFast, &_cloudundancyFileCopier, sourceFilePath, expectedDestinationFilePath));
   METALMOCK(_memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyFileCopier::WriteCopiedMessageOrExitWithCode1IfCopyFailed, &_cloudundancyFileCopier, fileCopyResult, destinationFolderPath));
}

TEST(CopyNestedFileToFolder_RelativeDestinationFolderPathIsNotDot_CopiesNestedFileToFolderWithRelativeDestinationFolderPathPresentInTheDestinationFilePath)
{
   const fs::path sourceFilePathRelativeToSourceFolderPath = _call_String_ReplaceFirstMock.ReturnRandom();

   const Utils::FileCopyResult fileCopyResult = _memberCaller_CopyFileFastMock->CallConstMemberFunctionMock.ReturnRandom();

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
   METALMOCK(_memberCaller_CopyFileFastMock->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyFileCopier::CopyFileFast, &_cloudundancyFileCopier, sourceFilePath, expectedDestinationFilePath));
   METALMOCK(_memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyFileCopier::WriteCopiedMessageOrExitWithCode1IfCopyFailed, &_cloudundancyFileCopier, fileCopyResult, destinationFolderPath));
}

TEST(CopyFileFast_FileSizeIsGreaterThanOrEqualTo2GB_CopiesFileWithStdFilesystemCopyFileFast_ReturnsFileCopyResult)
{
   _consoleMock->WriteMock.Expect();

   _cloudundancyFileSystemMock->IsFileSizeGreaterThanOrEqualTo2GBMock.Return(true);

   const Utils::FileCopyResult fileCopyResult = ZenUnit::Random<Utils::FileCopyResult>();
   _rawFileSystemMock->CopyFileFastLargerThan2GBMock.Return(fileCopyResult);

   const fs::path sourceFilePath = ZenUnit::Random<fs::path>();
   const fs::path destinationFilePath = ZenUnit::Random<fs::path>();
   //
   const Utils::FileCopyResult returnedFileCopyResult = _cloudundancyFileCopier.CopyFileFast(sourceFilePath, destinationFilePath);
   //
   const string expectedCopyingFileMessage = Utils::String::ConcatStrings(
      "Copying ", sourceFilePath.string(), "\n",
      "     to ", destinationFilePath.string(), ". ");
   METALMOCK(_consoleMock->WriteMock.CalledOnceWith(expectedCopyingFileMessage));
   METALMOCK(_cloudundancyFileSystemMock->IsFileSizeGreaterThanOrEqualTo2GBMock.CalledOnceWith(sourceFilePath));
   METALMOCK(_rawFileSystemMock->CopyFileFastLargerThan2GBMock.CalledOnceWith(sourceFilePath, destinationFilePath));
   ARE_EQUAL(fileCopyResult, returnedFileCopyResult);
}

TEST(CopyFileFast_FileSizeIsLessThan2GB_CopiesFileWithCStyleCopyFileFast_ReturnsFileCopyResult)
{
   _consoleMock->WriteMock.Expect();

   _cloudundancyFileSystemMock->IsFileSizeGreaterThanOrEqualTo2GBMock.Return(false);
   const Utils::FileCopyResult fileCopyResult = _rawFileSystemMock->CopyFileFastMock.ReturnRandom();

   const fs::path sourceFilePath = ZenUnit::Random<fs::path>();
   const fs::path destinationFilePath = ZenUnit::Random<fs::path>();
   //
   const Utils::FileCopyResult returnedFileCopyResult = _cloudundancyFileCopier.CopyFileFast(sourceFilePath, destinationFilePath);
   //
   const string expectedCopyingFileMessage = Utils::String::ConcatStrings(
      "Copying ", sourceFilePath.string(), "\n",
      "     to ", destinationFilePath.string(), ". ");
   METALMOCK(_consoleMock->WriteMock.CalledOnceWith(expectedCopyingFileMessage));
   METALMOCK(_cloudundancyFileSystemMock->IsFileSizeGreaterThanOrEqualTo2GBMock.CalledOnceWith(sourceFilePath));
   METALMOCK(_rawFileSystemMock->CopyFileFastMock.CalledOnceWith(sourceFilePath, destinationFilePath));
   ARE_EQUAL(fileCopyResult, returnedFileCopyResult);
}

TEST(CopyFileFastToFolder_RelativeDestinationFolderPathIsADot_DoesNotJoinDotCharacter_CallsCopyFileFast)
{
   const Utils::FileCopyResult fileCopyResult = _memberCaller_CopyFileFastMock->CallConstMemberFunctionMock.ReturnRandom();

   _memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.Expect();

   CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction = ZenUnit::Random<CloudundancyIniCopyInstruction>();
   cloudundancyIniCopyInstruction.relativeDestinationFolderPath = ".";
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileCopier.CopyFileFastToFolder(cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   const fs::path& expectedSourceFilePath = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath;
   const fs::path expectedSourceFileName = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath.filename();
   const fs::path expectedDestinationFilePath = destinationFolderPath / expectedSourceFileName;
   METALMOCK(_memberCaller_CopyFileFastMock->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyFileCopier::CopyFileFast, &_cloudundancyFileCopier, expectedSourceFilePath, expectedDestinationFilePath));
   METALMOCK(_memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyFileCopier::WriteCopiedMessageOrExitWithCode1IfCopyFailed, &_cloudundancyFileCopier, fileCopyResult, destinationFolderPath));
}

TEST(CopyFileFastToFolder_RelativeDestinationFolderPathIsNotADot_JoinsRelativeDestinationFolder_CallsCopyFileFast)
{
   const Utils::FileCopyResult fileCopyResult = _memberCaller_CopyFileFastMock->CallConstMemberFunctionMock.ReturnRandom();

   _memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.Expect();

   const CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction = ZenUnit::Random<CloudundancyIniCopyInstruction>();
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileCopier.CopyFileFastToFolder(cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   const fs::path& expectedSourceFilePath = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath;
   const fs::path expectedSourceFileName = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath.filename();
   const fs::path expectedDestinationFilePath =
      destinationFolderPath / cloudundancyIniCopyInstruction.relativeDestinationFolderPath / expectedSourceFileName;
   METALMOCK(_memberCaller_CopyFileFastMock->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyFileCopier::CopyFileFast, &_cloudundancyFileCopier, expectedSourceFilePath, expectedDestinationFilePath));
   METALMOCK(_memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyFileCopier::WriteCopiedMessageOrExitWithCode1IfCopyFailed, &_cloudundancyFileCopier, fileCopyResult, destinationFolderPath));
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
   METALMOCK(_cloudundancyLogFileWriterMock->AppendTextToCloudundancyLogFileInFolderMock.CalledOnceWith(
      destinationFolderPath, expectedCopyFailedLogFileMessage));

   const string expectedCopyFailedConsoleMessage = Utils::String::ConcatValues(
      "Copy failed [", fileCopyResult.durationInMilliseconds, "ms]: ", fileCopyResult.copyFailureReason, "\n\n[Cloudundancy] ExitCode: 1");
   METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedCopyFailedConsoleMessage, Color::Red));

   METALMOCK(_call_exitMock.CalledOnceWith(1));
}

RUN_TESTS(CloudundancyFileCopierTests)
