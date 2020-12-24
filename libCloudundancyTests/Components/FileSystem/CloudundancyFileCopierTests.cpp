#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyFileCopier.h"
#include "libCloudundancyTests/Components/FileSystem/MetalMock/CloudundancyLogFileWriterMock.h"
#include "libCloudundancyTests/Components/IniFile/MetalMock/CloudundancyIniFileReaderMock.h"

TESTS(CloudundancyFileCopierTests)
AFACT(DefaultConstructor_SetsFunctionsAndNewsComponents)
AFACT(CopyFilesAndFoldersToMultipleDestinationFolders_DeleteDestinationFoldersFirstIsTrue_DeletesDestinationFolders_CopiesFilesAndFoldersToFolders)
// Private Functions
AFACT(CopyFilesAndFoldersToDestinationFolder_TryCatchCallsDoCopyFilesAndFoldersToDestinationFolder)
AFACT(DoCopyFilesAndFoldersToDestinationFolder_AppendBackupStartedToLogFile_CopiesNonSkippedSourceFilesToDestinationFolder_AppendBackupSuccessfulToLogFile)
AFACT(DoCopyFilesAndFoldersToDestinationFolder_AppendBackupStartedToLogFile_CopiesNonSkippedSourceFilesToDestinationFolder_AppendBackupSuccessfulToLogFile)
AFACT(ExceptionHandlerForDoCopyFilesAndFoldersToDestinationFolder_WritesExceptionMessageToConsole_AppendsExceptionMessageToCloudundancyLogFile_RethrowsException)
AFACT(CopyFileOrFolderToFolder_SourcePathHasAFileName_CallsCopyFileToFolder)
FACTS(CopyFileOrFolderToFolder_SourcePathDoesNotHaveAFileNameMeaningItIsAFolder_CallsRecursivelyCopyNonIgnoredFilesToFolder)
AFACT(CopyNonIgnoredFilesInAndBelowFolderToFolder_CopiesNonIgnoredFilesToFolderUntilRecursiveDirectoryIteratorReturnsNoMoreFiles)
AFACT(CopyNestedFileToFolder_RelativeDestinationFolderPathIsDot_CopiesNestedFileToFolderWithSlashDotSlashNotPresentInTheDestinationFilePath)
AFACT(CopyNestedFileToFolder_RelativeDestinationFolderPathIsNotDot_CopiesNestedFileToFolderWithRelativeDestinationFolderPathPresentInTheDestinationFilePath)
AFACT(TryCopyFile_FileSizeIsGreaterThanOrEqualTo2GB_CopiesFileWithStdFilesystemCopyFile_ReturnsFileCopyResult)
AFACT(TryCopyFile_FileSizeIsLessThan2GB_CopiesFileWithCStyleCopyFile_ReturnsFileCopyResult)
AFACT(TryCopyFileToFolder_RelativeDestinationFolderPathIsADot_DoesNotJoinDotCharacter_CallsTryCopyFile)
AFACT(TryCopyFileToFolder_RelativeDestinationFolderPathIsNotADot_JoinsRelativeDestinationFolder_CallsTryCopyFile)
AFACT(WriteCopiedMessageOrExitWithCode1IfCopyFailed_CopySucceeded_WritesCopiedAndDurationInMilliseconds)
AFACT(WriteCopiedMessageOrExitWithCode1IfCopyFailed_CopyFailed_WritesCopyFailedAndDurationInMillisecondsAndCopyFailureReason_AppendsErrorToCloudundancyLog_ExitsProgramWithCode1)
EVIDENCE

CloudundancyFileCopier _cloudundancyFileCopier;

// Function Pointers
METALMOCK_VOID1_FREE(exit, int)
METALMOCK_NONVOID3_STATIC(string, String, ReplaceFirst, const string&, const string&, const string&)
METALMOCK_NONVOID1_STATIC(string, Type, GetExceptionClassNameAndMessage, const exception*)

// Function Callers
using _memberCaller_CopyFileFunctionsMockType = VoidTwoArgMemberFunctionCallerMock<
   CloudundancyFileCopier, const CloudundancyIniCopyInstruction&, const fs::path&>;
_memberCaller_CopyFileFunctionsMockType* _memberCaller_CopyFileFunctionsMock = nullptr;

using _memberCaller_CopyNestedFileToFolderMockType = const VoidThreeArgMemberFunctionCallerMock<
   CloudundancyFileCopier, const fs::path&, const CloudundancyIniCopyInstruction&, const fs::path&>;
_memberCaller_CopyNestedFileToFolderMockType* _memberCaller_CopyNestedFileToFolderMock = nullptr;

using _memberCaller_TryCopyFileMockType = NonVoidTwoArgMemberFunctionCallerMock<
   FileCopyResult, CloudundancyFileCopier, const fs::path&, const fs::path&>;
_memberCaller_TryCopyFileMockType* _memberCaller_TryCopyFileMock = nullptr;

using _memberForEacher_CopyEachFileOrFolderToFolderMockType = OneExtraArgMemberFunctionForEacherMock<
   CloudundancyFileCopier, fs::path, const CloudundancyIni&>;
_memberForEacher_CopyEachFileOrFolderToFolderMockType* _memberForEacher_CopyEachFileOrFolderToFolderMock = nullptr;

using _memberForEacher_CopyFileOrFolderToFolderMockType = OneExtraArgMemberFunctionForEacherMock<
   CloudundancyFileCopier, CloudundancyIniCopyInstruction, const fs::path&>;
_memberForEacher_CopyFileOrFolderToFolderMockType* _memberForEacher_CopyFileOrFolderToFolderMock = nullptr;

using _memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMockType = VoidTwoArgMemberFunctionCallerMock<
   CloudundancyFileCopier, const FileCopyResult&, const fs::path&>;
_memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMockType* _memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock = nullptr;

// Constant Components
CloudundancyIniFileReaderMock* _cloudundancyIniFileReaderMock = nullptr;
CloudundancyLogFileWriterMock* _cloudundancyLogFileWriterMock = nullptr;
ConsoleMock* _consoleMock = nullptr;
FileSystemMock* _fileSystemMock = nullptr;
using TryCatchCallerMockType = TryCatchCallerMock<CloudundancyFileCopier, const pair<fs::path, CloudundancyIni>&>;
TryCatchCallerMockType* _tryCatchCallerMock = nullptr;

// Mutable Components
RecursiveDirectoryIteratorMock* _recursiveDirectoryIteratorMock = nullptr;
StopwatchMock* _stopwatchMock = nullptr;

STARTUP
{
   // Function Pointers
   _cloudundancyFileCopier._call_exit = BIND_1ARG_METALMOCK_OBJECT(exitMock);
   _cloudundancyFileCopier._call_String_ReplaceFirst = BIND_3ARG_METALMOCK_OBJECT(ReplaceFirstMock);
   _cloudundancyFileCopier._call_Type_GetExceptionClassNameAndMessage = BIND_1ARG_METALMOCK_OBJECT(GetExceptionClassNameAndMessageMock);
   // Function Callers
   _cloudundancyFileCopier._memberCaller_CopyFileFunctions.reset(_memberCaller_CopyFileFunctionsMock = new _memberCaller_CopyFileFunctionsMockType);
   _cloudundancyFileCopier._memberCaller_CopyNestedFileToFolder.reset(_memberCaller_CopyNestedFileToFolderMock = new _memberCaller_CopyNestedFileToFolderMockType);
   _cloudundancyFileCopier._memberCaller_TryCopyFile.reset(_memberCaller_TryCopyFileMock = new _memberCaller_TryCopyFileMockType);
   _cloudundancyFileCopier._memberForEacher_CopyEachFileOrFolderToFolder.reset(_memberForEacher_CopyEachFileOrFolderToFolderMock = new _memberForEacher_CopyEachFileOrFolderToFolderMockType);
   _cloudundancyFileCopier._memberForEacher_CopyFileOrFolderToFolder.reset(_memberForEacher_CopyFileOrFolderToFolderMock = new _memberForEacher_CopyFileOrFolderToFolderMockType);
   _cloudundancyFileCopier._memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailed.reset(_memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock = new _memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMockType);
   // Components
   _cloudundancyFileCopier._cloudundancyIniFileReader.reset(_cloudundancyIniFileReaderMock = new CloudundancyIniFileReaderMock);
   _cloudundancyFileCopier._cloudundancyLogFileWriter.reset(_cloudundancyLogFileWriterMock = new CloudundancyLogFileWriterMock);
   _cloudundancyFileCopier._console.reset(_consoleMock = new ConsoleMock);
   _cloudundancyFileCopier._fileSystem.reset(_fileSystemMock = new FileSystemMock);
   _cloudundancyFileCopier._tryCatchCaller.reset(_tryCatchCallerMock = new TryCatchCallerMockType);
   // Mutable Components
   _cloudundancyFileCopier._recursiveDirectoryIterator.reset(_recursiveDirectoryIteratorMock = new RecursiveDirectoryIteratorMock);
   _cloudundancyFileCopier._stopwatch.reset(_stopwatchMock = new StopwatchMock);
}

TEST(DefaultConstructor_SetsFunctionsAndNewsComponents)
{
   CloudundancyFileCopier cloudundancyFileCopier;
   // Function Pointers
   STD_FUNCTION_TARGETS(exit, cloudundancyFileCopier._call_exit);
   STD_FUNCTION_TARGETS(String::ReplaceFirst, cloudundancyFileCopier._call_String_ReplaceFirst);
   STD_FUNCTION_TARGETS(Type::GetExceptionClassNameAndMessage, cloudundancyFileCopier._call_Type_GetExceptionClassNameAndMessage);
   // Function Callers
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._memberCaller_CopyFileFunctions);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._memberCaller_CopyNestedFileToFolder);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._memberCaller_TryCopyFile);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._memberForEacher_CopyEachFileOrFolderToFolder);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._memberForEacher_CopyFileOrFolderToFolder);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailed);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._cloudundancyIniFileReader);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._console);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._fileSystem);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._tryCatchCaller);
   // Mutable Components
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._recursiveDirectoryIterator);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileCopier._stopwatch);
}

TEST(CopyFilesAndFoldersToMultipleDestinationFolders_DeleteDestinationFoldersFirstIsTrue_DeletesDestinationFolders_CopiesFilesAndFoldersToFolders)
{
   const CloudundancyIni cloudundancyIni = _cloudundancyIniFileReaderMock->ReadIniFileMock.ReturnRandom();

   _consoleMock->WriteLineMock.Expect();
   _consoleMock->WriteLineColorMock.Expect();
   _consoleMock->WriteLinesMock.Expect();

   _recursiveDirectoryIteratorMock->SetFileSubpathsToIgnoreMock.Expect();

   _memberForEacher_CopyEachFileOrFolderToFolderMock->CallConstMemberFunctionForEachElementMock.Expect();

   _fileSystemMock->DeleteFoldersExceptForFileMock.Expect();

   const fs::path iniFilePath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileCopier.CopyFilesAndFoldersToMultipleDestinationFolders(iniFilePath, true);
   //
   METALMOCK(_cloudundancyIniFileReaderMock->ReadIniFileMock.CalledOnceWith(iniFilePath));
   const string expectedCopyingMessage = String::Concat(
      "[Cloudundancy] Copying [SourceFilesAndFolders] to [DestinationFolders] as listed in ", iniFilePath.string(), ":\n");
   METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedCopyingMessage, Color::Teal));
   METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(
      "[Cloudundancy] Deleting [DestinationFolders] first because --delete-destination-folders-first is specified"));
   METALMOCK(_fileSystemMock->DeleteFoldersExceptForFileMock.CalledOnceWith(cloudundancyIni.destinationFolderPaths, "Cloudundancy.log"));
   METALMOCK(_consoleMock->WriteLinesMock.CalledOnceWith(cloudundancyIni.iniFileLines));
   METALMOCK(_recursiveDirectoryIteratorMock->SetFileSubpathsToIgnoreMock.CalledOnceWith(cloudundancyIni.fileSubpathsToNotCopy));
   METALMOCK(_memberForEacher_CopyEachFileOrFolderToFolderMock->CallConstMemberFunctionForEachElementMock.CalledOnceWith(
      cloudundancyIni.destinationFolderPaths,
      &CloudundancyFileCopier::CopyFilesAndFoldersToDestinationFolder,
      &_cloudundancyFileCopier, cloudundancyIni));
}

TEST(CopyFilesAndFoldersToMultipleDestinationFolders_DeleteDestinationFoldersFirstIsFalse_DoesNotDeleteDestinationFolders_CopiesFilesAndFoldersToFolders)
{
   const CloudundancyIni cloudundancyIni = _cloudundancyIniFileReaderMock->ReadIniFileMock.ReturnRandom();

   _consoleMock->WriteLineMock.Expect();
   _consoleMock->WriteLinesMock.Expect();

   _recursiveDirectoryIteratorMock->SetFileSubpathsToIgnoreMock.Expect();

   _memberForEacher_CopyEachFileOrFolderToFolderMock->CallConstMemberFunctionForEachElementMock.Expect();

   const fs::path iniFilePath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileCopier.CopyFilesAndFoldersToMultipleDestinationFolders(iniFilePath, false);
   //
   METALMOCK(_cloudundancyIniFileReaderMock->ReadIniFileMock.CalledOnceWith(iniFilePath));
   const string expectedCopyingMessage = String::Concat(
      "[Cloudundancy] Copying [SourceFilesAndFolders] to [DestinationFolders] as listed in ", iniFilePath.string(), ":\n");
   METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedCopyingMessage, Color::Teal));
   METALMOCK(_consoleMock->WriteLinesMock.CalledOnceWith(cloudundancyIni.iniFileLines));
   METALMOCK(_recursiveDirectoryIteratorMock->SetFileSubpathsToIgnoreMock.CalledOnceWith(cloudundancyIni.fileSubpathsToNotCopy));
   METALMOCK(_memberForEacher_CopyEachFileOrFolderToFolderMock->CallConstMemberFunctionForEachElementMock.CalledOnceWith(
      cloudundancyIni.destinationFolderPaths,
      &CloudundancyFileCopier::CopyFilesAndFoldersToDestinationFolder,
      &_cloudundancyFileCopier, cloudundancyIni));
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
   const string expectedCopyingMessage = String::Concat(
      "\n[Cloudundancy] Copying [SourceFilesAndFolders] to destination folder ", destinationFolderPath.string(), ":\n");
   const string expectedFolderBackupResultSuccessMessage = String::Concat(
      "[Cloudundancy]   FolderBackupResult: Successfully copied [SourceFilesAndFolders] to ", destinationFolderPath.string());
   METALMOCK(_consoleMock->WriteLineColorMock.CalledAsFollows(
   {
      { expectedCopyingMessage, Color::Teal },
      { expectedFolderBackupResultSuccessMessage, Color::Green }
   }));
   const string expectedFolderBackupDurationMessage = String::Concat(
      "[Cloudundancy] FolderBackupDuration: ", elapsedSeconds, " seconds");
   METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(expectedFolderBackupDurationMessage));
   const string expectedBackupSuccessfulLogFileMessage = String::Concat(
      "Cloudundancy backup successful in ", elapsedSeconds, " seconds");
   METALMOCK(_cloudundancyLogFileWriterMock->AppendTextToCloudundancyLogFileInFolderMock.CalledAsFollows(
   {
      { destinationFolderPath, "Cloudundancy backup started" },
      { destinationFolderPath, expectedBackupSuccessfulLogFileMessage }
   }));
   METALMOCK(_stopwatchMock->StartMock.CalledOnce());
   METALMOCK(_memberForEacher_CopyFileOrFolderToFolderMock->CallConstMemberFunctionForEachElementMock.CalledOnceWith(
      cloudundancyIni.cloudundancyIniCopyInstructions,
      &CloudundancyFileCopier::CopyFileOrFolderToFolder,
      &_cloudundancyFileCopier, destinationFolderPath));
   METALMOCK(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce());
}

TEST(ExceptionHandlerForDoCopyFilesAndFoldersToDestinationFolder_WritesExceptionMessageToConsole_AppendsExceptionMessageToCloudundancyLogFile_RethrowsException)
{
   const string exceptionClassNameAndMessage = GetExceptionClassNameAndMessageMock.ReturnRandom();

   _consoleMock->WriteLineMock.Expect();

   _cloudundancyLogFileWriterMock->AppendTextToCloudundancyLogFileInFolderMock.Expect();

   const string exceptionMessage = ZenUnit::Random<string>();
   const runtime_error ex(exceptionMessage);

   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   const CloudundancyIni cloudundancyIni = ZenUnit::Random<CloudundancyIni>();
   const pair<fs::path, CloudundancyIni> destinationFolderPath_cloudundancyIni = make_pair(destinationFolderPath, cloudundancyIni);
   //
   THROWS_EXCEPTION(_cloudundancyFileCopier.ExceptionHandlerForDoCopyFilesAndFoldersToDestinationFolder(
      ex, destinationFolderPath_cloudundancyIni),
      exception, exceptionMessage);
   //
   METALMOCK(GetExceptionClassNameAndMessageMock.CalledOnceWith(&ex));
   const string expectedErrorMessage = String::Concat(
      "\n[Cloudundancy]     Error: Exception thrown while copying files to destination folder ",
      destinationFolderPath, ": ", exceptionClassNameAndMessage, ". Rethrowing exception.");
   METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(expectedErrorMessage));
   METALMOCK(_cloudundancyLogFileWriterMock->AppendTextToCloudundancyLogFileInFolderMock.CalledOnceWith(
      destinationFolderPath, expectedErrorMessage));
}

TEST(CopyFileOrFolderToFolder_SourcePathHasAFileName_CallsCopyFileToFolder)
{
   _memberCaller_CopyFileFunctionsMock->CallConstMemberFunctionMock.Expect();
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   const CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction =
      ZenUnit::Random<CloudundancyIniCopyInstruction>();
   //
   _cloudundancyFileCopier.CopyFileOrFolderToFolder(cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   METALMOCK(_memberCaller_CopyFileFunctionsMock->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyFileCopier::TryCopyFileToFolder,
      &_cloudundancyFileCopier, cloudundancyIniCopyInstruction, destinationFolderPath));
}

TEST1X1(CopyFileOrFolderToFolder_SourcePathDoesNotHaveAFileNameMeaningItIsAFolder_CallsRecursivelyCopyNonIgnoredFilesToFolder,
   const fs::path& sourceFileOrFolderPath,
   "FolderNameA/",
   "FolderNameB\\")
{
   _memberCaller_CopyFileFunctionsMock->CallConstMemberFunctionMock.Expect();
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction = ZenUnit::Random<CloudundancyIniCopyInstruction>();
   cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath = sourceFileOrFolderPath;
   //
   _cloudundancyFileCopier.CopyFileOrFolderToFolder(cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   METALMOCK(_memberCaller_CopyFileFunctionsMock->CallConstMemberFunctionMock.CalledOnceWith(
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
   const fs::path sourceFilePathRelativeToSourceFolderPath = ReplaceFirstMock.ReturnRandom();

   const FileCopyResult fileCopyResult = _memberCaller_TryCopyFileMock->CallConstMemberFunctionMock.ReturnRandom();

   _memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.Expect();

   const fs::path sourceFilePath = ZenUnit::Random<fs::path>();
   CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction = ZenUnit::Random<CloudundancyIniCopyInstruction>();
   cloudundancyIniCopyInstruction.relativeDestinationFolderPath = ".";
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileCopier.CopyNestedFileToFolder(sourceFilePath, cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   METALMOCK(ReplaceFirstMock.CalledOnceWith(
      sourceFilePath.string(), cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath.string(), ""));
   const fs::path expectedDestinationFilePath =
      destinationFolderPath /
      sourceFilePathRelativeToSourceFolderPath;
   METALMOCK(_memberCaller_TryCopyFileMock->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyFileCopier::TryCopyFile, &_cloudundancyFileCopier, sourceFilePath, expectedDestinationFilePath));
   METALMOCK(_memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyFileCopier::WriteCopiedMessageOrExitWithCode1IfCopyFailed, &_cloudundancyFileCopier, fileCopyResult, destinationFolderPath));
}

TEST(CopyNestedFileToFolder_RelativeDestinationFolderPathIsNotDot_CopiesNestedFileToFolderWithRelativeDestinationFolderPathPresentInTheDestinationFilePath)
{
   const fs::path sourceFilePathRelativeToSourceFolderPath = ReplaceFirstMock.ReturnRandom();

   const FileCopyResult fileCopyResult = _memberCaller_TryCopyFileMock->CallConstMemberFunctionMock.ReturnRandom();

   _memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.Expect();

   const fs::path sourceFilePath = ZenUnit::Random<fs::path>();
   const CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction = ZenUnit::Random<CloudundancyIniCopyInstruction>();
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileCopier.CopyNestedFileToFolder(sourceFilePath, cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   METALMOCK(ReplaceFirstMock.CalledOnceWith(
      sourceFilePath.string(), cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath.string(), ""));
   const fs::path expectedDestinationFilePath =
      destinationFolderPath /
      cloudundancyIniCopyInstruction.relativeDestinationFolderPath /
      sourceFilePathRelativeToSourceFolderPath;
   METALMOCK(_memberCaller_TryCopyFileMock->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyFileCopier::TryCopyFile, &_cloudundancyFileCopier, sourceFilePath, expectedDestinationFilePath));
   METALMOCK(_memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyFileCopier::WriteCopiedMessageOrExitWithCode1IfCopyFailed, &_cloudundancyFileCopier, fileCopyResult, destinationFolderPath));
}

TEST(TryCopyFile_FileSizeIsGreaterThanOrEqualTo2GB_CopiesFileWithStdFilesystemCopyFile_ReturnsFileCopyResult)
{
   _consoleMock->WriteMock.Expect();

   _fileSystemMock->IsFileSizeGreaterThanOrEqualTo2GBMock.Return(true);

   const FileCopyResult fileCopyResult = ZenUnit::Random<FileCopyResult>();
   _fileSystemMock->TryCopyFileWithStdFilesystemCopyFileMock.Return(fileCopyResult);

   const fs::path sourceFilePath = ZenUnit::Random<fs::path>();
   const fs::path destinationFilePath = ZenUnit::Random<fs::path>();
   //
   const FileCopyResult returnedFileCopyResult = _cloudundancyFileCopier.TryCopyFile(sourceFilePath, destinationFilePath);
   //
   const string expectedCopyingFileMessage = String::Concat(
      "Copying ", sourceFilePath.string(), '\n',
      "     to ", destinationFilePath.string(), ". ");
   METALMOCK(_consoleMock->WriteMock.CalledOnceWith(expectedCopyingFileMessage));
   METALMOCK(_fileSystemMock->IsFileSizeGreaterThanOrEqualTo2GBMock.CalledOnceWith(sourceFilePath));
   METALMOCK(_fileSystemMock->TryCopyFileWithStdFilesystemCopyFileMock.CalledOnceWith(sourceFilePath, destinationFilePath));
   ARE_EQUAL(fileCopyResult, returnedFileCopyResult);
}

TEST(TryCopyFile_FileSizeIsLessThan2GB_CopiesFileWithCStyleCopyFile_ReturnsFileCopyResult)
{
   _consoleMock->WriteMock.Expect();

   _fileSystemMock->IsFileSizeGreaterThanOrEqualTo2GBMock.Return(false);

   const FileCopyResult fileCopyResult = ZenUnit::Random<FileCopyResult>();
   _fileSystemMock->TryCopyFileMock.Return(fileCopyResult);

   const fs::path sourceFilePath = ZenUnit::Random<fs::path>();
   const fs::path destinationFilePath = ZenUnit::Random<fs::path>();
   //
   const FileCopyResult returnedFileCopyResult = _cloudundancyFileCopier.TryCopyFile(sourceFilePath, destinationFilePath);
   //
   const string expectedCopyingFileMessage = String::Concat(
      "Copying ", sourceFilePath.string(), '\n',
      "     to ", destinationFilePath.string(), ". ");
   METALMOCK(_consoleMock->WriteMock.CalledOnceWith(expectedCopyingFileMessage));
   METALMOCK(_fileSystemMock->IsFileSizeGreaterThanOrEqualTo2GBMock.CalledOnceWith(sourceFilePath));
   METALMOCK(_fileSystemMock->TryCopyFileMock.CalledOnceWith(sourceFilePath, destinationFilePath));
   ARE_EQUAL(fileCopyResult, returnedFileCopyResult);
}

TEST(TryCopyFileToFolder_RelativeDestinationFolderPathIsADot_DoesNotJoinDotCharacter_CallsTryCopyFile)
{
   const FileCopyResult fileCopyResult = _memberCaller_TryCopyFileMock->CallConstMemberFunctionMock.ReturnRandom();

   _memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.Expect();

   CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction = ZenUnit::Random<CloudundancyIniCopyInstruction>();
   cloudundancyIniCopyInstruction.relativeDestinationFolderPath = ".";
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileCopier.TryCopyFileToFolder(cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   const fs::path& expectedSourceFilePath = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath;
   const fs::path expectedSourceFileName = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath.filename();
   const fs::path expectedDestinationFilePath = destinationFolderPath / expectedSourceFileName;
   METALMOCK(_memberCaller_TryCopyFileMock->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyFileCopier::TryCopyFile, &_cloudundancyFileCopier, expectedSourceFilePath, expectedDestinationFilePath));
   METALMOCK(_memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyFileCopier::WriteCopiedMessageOrExitWithCode1IfCopyFailed, &_cloudundancyFileCopier, fileCopyResult, destinationFolderPath));
}

TEST(TryCopyFileToFolder_RelativeDestinationFolderPathIsNotADot_JoinsRelativeDestinationFolder_CallsTryCopyFile)
{
   const FileCopyResult fileCopyResult = _memberCaller_TryCopyFileMock->CallConstMemberFunctionMock.ReturnRandom();

   _memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.Expect();

   const CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction = ZenUnit::Random<CloudundancyIniCopyInstruction>();
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileCopier.TryCopyFileToFolder(cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   const fs::path& expectedSourceFilePath = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath;
   const fs::path expectedSourceFileName = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath.filename();
   const fs::path expectedDestinationFilePath =
      destinationFolderPath / cloudundancyIniCopyInstruction.relativeDestinationFolderPath / expectedSourceFileName;
   METALMOCK(_memberCaller_TryCopyFileMock->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyFileCopier::TryCopyFile, &_cloudundancyFileCopier, expectedSourceFilePath, expectedDestinationFilePath));
   METALMOCK(_memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyFileCopier::WriteCopiedMessageOrExitWithCode1IfCopyFailed, &_cloudundancyFileCopier, fileCopyResult, destinationFolderPath));
}

TEST(WriteCopiedMessageOrExitWithCode1IfCopyFailed_CopySucceeded_WritesCopiedAndDurationInMilliseconds)
{
   _consoleMock->WriteLineColorMock.Expect();
   FileCopyResult fileCopyResult = ZenUnit::Random<FileCopyResult>();
   fileCopyResult.copySucceeded = true;
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileCopier.WriteCopiedMessageOrExitWithCode1IfCopyFailed(fileCopyResult, destinationFolderPath);
   //
   const string expectedCopiedMessage = String::Concat("Copied [", fileCopyResult.durationInMilliseconds, "ms]\n");
   METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedCopiedMessage, Color::Green));
}

TEST(WriteCopiedMessageOrExitWithCode1IfCopyFailed_CopyFailed_WritesCopyFailedAndDurationInMillisecondsAndCopyFailureReason_AppendsErrorToCloudundancyLog_ExitsProgramWithCode1)
{
   _consoleMock->WriteLineColorMock.Expect();
   _cloudundancyLogFileWriterMock->AppendTextToCloudundancyLogFileInFolderMock.Expect();
   exitMock.Expect();
   FileCopyResult fileCopyResult = ZenUnit::Random<FileCopyResult>();
   fileCopyResult.copySucceeded = false;
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileCopier.WriteCopiedMessageOrExitWithCode1IfCopyFailed(fileCopyResult, destinationFolderPath);
   //
   const string expectedCopyFailedLogFileMessage = String::Concat("File copy failed: ",
      fileCopyResult.sourceFilePath.string(), " -> ", fileCopyResult.destinationFilePath.string(),
      ". Reason: ", fileCopyResult.copyFailureReason);
   METALMOCK(_cloudundancyLogFileWriterMock->AppendTextToCloudundancyLogFileInFolderMock.CalledOnceWith(
      destinationFolderPath, expectedCopyFailedLogFileMessage));

   const string expectedCopyFailedConsoleMessage = String::Concat(
      "Copy failed [", fileCopyResult.durationInMilliseconds, "ms]: ", fileCopyResult.copyFailureReason, '\n',
      '\n',
      "[Cloudundancy] ExitCode: 1");
   METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedCopyFailedConsoleMessage, Color::Red));

   METALMOCK(exitMock.CalledOnceWith(1));
}

RUN_TESTS(CloudundancyFileCopierTests)
