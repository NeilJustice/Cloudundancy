#include "pch.h"
#include "libCloudundancy/ValueTypes/AbsoluteFilePathToRelativeDestinationFolderPath.h"
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"
#include "libCloudundancy/ValueTypes/CloudundancyIni.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyFileCopier.h"
#include "libCloudundancyTests/UtilityComponents/Console/MetalMock/ConsoleMock.h"
#include "libCloudundancyTests/UtilityComponents/FileSystem/MetalMock/FileSystemMock.h"
#include "libCloudundancyTests/Components/FileSystem/MetalMock/CloudundancyLogFileAppenderMock.h"
#include "libCloudundancyTests/UtilityComponents/FileSystem/MetalMock/RecursiveDirectoryIteratorMock.h"
#include "libCloudundancyTests/Components/IniFile/MetalMock/CloudundancyIniFileReaderMock.h"
#include "libCloudundancyTests/UtilityComponents/FunctionCallers/MemberFunctions/MetalMock/VoidOneArgMemberFunctionCallerMock.h"
#include "libCloudundancyTests/UtilityComponents/FunctionCallers/MemberFunctions/MetalMock/VoidTwoArgMemberFunctionCallerMock.h"
#include "libCloudundancyTests/UtilityComponents/FunctionCallers/MemberFunctions/MetalMock/VoidThreeArgMemberFunctionCallerMock.h"
#include "libCloudundancyTests/UtilityComponents/Time/MetalMock/StopwatchMock.h"

TESTS(CloudundancyFileCopierTests)
AFACT(DefaultConstructor_SetsFunctionsAndNewsComponents)
AFACT(CopyFilesAndFoldersToMultipleDestinationFolders_CopiesFilesAndFoldersToFolders)
// Private Functions
AFACT(CopyFilesAndFoldersToDestinationFolder_AppendBackupStartedToLogFile_CopiesNonSkippedSourceFilesToDestinationFolder_AppendBackupSuccessfulToLogFile)
AFACT(CopyFileOrFolderToFolder_SourcePathHasAFileName_CallsCopyFileToFolder)
FACTS(CopyFileOrFolderToFolder_SourcePathDoesNotHaveAFileNameMeaningItIsAFolder_CallsRecursivelyCopyNonIgnoredFilesToFolder)
AFACT(CopyNonIgnoredFilesInAndBelowFolderToFolder_CopiesNonIgnoredFilesToFolderUntilRecursiveDirectoryIteratorReturnsNoMoreFiles)
AFACT(CopyNestedFileToFolder_RelativeDestinationFolderPathIsDot_CopiesNestedFileToFolderWithSlashDotSlashNotPresentInTheDestinationFilePath)
AFACT(CopyNestedFileToFolder_RelativeDestinationFolderPathIsNotDot_CopiesNestedFileToFolderWithRelativeDestinationFolderPathPresentInTheDestinationFilePath)
AFACT(TryCopyFile_FileSizeIsGreaterThanOrEqualTo2GB_CopiesFileWithStdFilesystemCopyFile_WritesCopiedIfCopySucceeded_WritesCopyFailedIfCopyFailed)
AFACT(TryCopyFile_FileSizeIsLessThan2GB_CopiesFileWithCStyleCopyFile_WritesCopiedIfCopySucceeded_WritesCopyFailedIfCopyFailed)
AFACT(TryCopyFileToFolder_RelativeDestinationFolderPathIsADot_DoesNotJoinDotCharacter_CallsTryCopyFile)
AFACT(TryCopyFileToFolder_RelativeDestinationFolderPathIsNotADot_JoinsRelativeDestinationFolder_CallsTryCopyFile)
AFACT(WriteCopiedMessageOrExitWithCode1IfCopyFailed_CopySucceeded_WritesCopiedAndDurationInMilliseconds)
AFACT(WriteCopiedMessageOrExitWithCode1IfCopyFailed_CopyFailed_WritesCopyFailedAndDurationInMillisecondsAndCopyFailureReason_ExitsProgramWithCode1)
EVIDENCE

CloudundancyFileCopier _cloudundancyFileCopier;

// Function Pointers
METALMOCK_VOID1_FREE(exit, int)
METALMOCK_NONVOID3_STATIC(string, String, ReplaceFirst, const string&, const string&, const string&)

// Function Callers
using _memberCaller_CopyFileFunctionsMockType = VoidTwoArgMemberFunctionCallerMock<
   CloudundancyFileCopier, const CloudundancyIniCopyInstruction&, const fs::path&>;
_memberCaller_CopyFileFunctionsMockType* _memberCaller_CopyFileFunctionsMock = nullptr;

using _memberCaller_CopyNestedFileToFolderMockType = const VoidThreeArgMemberFunctionCallerMock<
   CloudundancyFileCopier, const fs::path&, const CloudundancyIniCopyInstruction&, const fs::path&>;
_memberCaller_CopyNestedFileToFolderMockType* _memberCaller_CopyNestedFileToFolderMock = nullptr;

using _memberCaller_TryCopyFileMockType = VoidTwoArgMemberFunctionCallerMock<
   CloudundancyFileCopier, const fs::path&, const fs::path&>;
_memberCaller_TryCopyFileMockType* _memberCaller_TryCopyFileMock = nullptr;

using _memberForEacher_CopyEachFileOrFolderToFolderMockType = OneExtraArgMemberFunctionForEacherMock<
   CloudundancyFileCopier, fs::path, const CloudundancyIni&>;
_memberForEacher_CopyEachFileOrFolderToFolderMockType* _memberForEacher_CopyEachFileOrFolderToFolderMock = nullptr;

using _memberForEacher_CopyFileOrFolderToFolderMockType = OneExtraArgMemberFunctionForEacherMock<
   CloudundancyFileCopier, CloudundancyIniCopyInstruction, const fs::path&>;
_memberForEacher_CopyFileOrFolderToFolderMockType* _memberForEacher_CopyFileOrFolderToFolderMock = nullptr;

using _memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMockType = VoidOneArgMemberFunctionCallerMock<
   CloudundancyFileCopier, const FileCopyResult&>;
_memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMockType* _memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock = nullptr;

// Constant Components
CloudundancyIniFileReaderMock* _cloudundancyIniFileReaderMock = nullptr;
CloudundancyLogFileAppenderMock* _cloudundancyLogFileAppenderMock = nullptr;
ConsoleMock* _consoleMock = nullptr;
FileSystemMock* _fileSystemMock = nullptr;

// Mutable Components
RecursiveDirectoryIteratorMock* _recursiveDirectoryIteratorMock = nullptr;
StopwatchMock* _stopwatchMock = nullptr;

STARTUP
{
   // Function Pointers
   _cloudundancyFileCopier._call_exit = BIND_1ARG_METALMOCK_OBJECT(exitMock);
   _cloudundancyFileCopier._call_String_ReplaceFirst = BIND_3ARG_METALMOCK_OBJECT(ReplaceFirstMock);
   // Function Callers
   _cloudundancyFileCopier._memberCaller_CopyFileFunctions.reset(_memberCaller_CopyFileFunctionsMock = new _memberCaller_CopyFileFunctionsMockType);
   _cloudundancyFileCopier._memberCaller_CopyNestedFileToFolder.reset(_memberCaller_CopyNestedFileToFolderMock = new _memberCaller_CopyNestedFileToFolderMockType);
   _cloudundancyFileCopier._memberCaller_TryCopyFile.reset(_memberCaller_TryCopyFileMock = new _memberCaller_TryCopyFileMockType);
   _cloudundancyFileCopier._memberForEacher_CopyEachFileOrFolderToFolder.reset(_memberForEacher_CopyEachFileOrFolderToFolderMock = new _memberForEacher_CopyEachFileOrFolderToFolderMockType);
   _cloudundancyFileCopier._memberForEacher_CopyFileOrFolderToFolder.reset(_memberForEacher_CopyFileOrFolderToFolderMock = new _memberForEacher_CopyFileOrFolderToFolderMockType);
   _cloudundancyFileCopier._memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailed.reset(_memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock = new _memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMockType);
   // Components
   _cloudundancyFileCopier._cloudundancyIniFileReader.reset(_cloudundancyIniFileReaderMock = new CloudundancyIniFileReaderMock);
   _cloudundancyFileCopier._cloudundancyLogFileAppender.reset(_cloudundancyLogFileAppenderMock = new CloudundancyLogFileAppenderMock);
   _cloudundancyFileCopier._console.reset(_consoleMock = new ConsoleMock);
   _cloudundancyFileCopier._fileSystem.reset(_fileSystemMock = new FileSystemMock);
   // Mutable Components
   _cloudundancyFileCopier._recursiveDirectoryIterator.reset(_recursiveDirectoryIteratorMock = new RecursiveDirectoryIteratorMock);
   _cloudundancyFileCopier._stopwatch.reset(_stopwatchMock = new StopwatchMock);
}

TEST(DefaultConstructor_SetsFunctionsAndNewsComponents)
{
   CloudundancyFileCopier fileCopier;
   // Function Pointers
   STD_FUNCTION_TARGETS(exit, fileCopier._call_exit);
   STD_FUNCTION_TARGETS(String::ReplaceFirst, fileCopier._call_String_ReplaceFirst);
   // Function Callers
   DELETE_TO_ASSERT_NEWED(fileCopier._memberCaller_CopyFileFunctions);
   DELETE_TO_ASSERT_NEWED(fileCopier._memberCaller_CopyNestedFileToFolder);
   DELETE_TO_ASSERT_NEWED(fileCopier._memberCaller_TryCopyFile);
   DELETE_TO_ASSERT_NEWED(fileCopier._memberForEacher_CopyEachFileOrFolderToFolder);
   DELETE_TO_ASSERT_NEWED(fileCopier._memberForEacher_CopyFileOrFolderToFolder);
   DELETE_TO_ASSERT_NEWED(fileCopier._memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailed);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(fileCopier._cloudundancyIniFileReader);
   DELETE_TO_ASSERT_NEWED(fileCopier._console);
   DELETE_TO_ASSERT_NEWED(fileCopier._fileSystem);
   // Mutable Components
   DELETE_TO_ASSERT_NEWED(fileCopier._recursiveDirectoryIterator);
   DELETE_TO_ASSERT_NEWED(fileCopier._stopwatch);
}

TEST(CopyFilesAndFoldersToMultipleDestinationFolders_CopiesFilesAndFoldersToFolders)
{
   const CloudundancyIni cloudundancyIni = _cloudundancyIniFileReaderMock->ReadIniFileMock.ReturnRandom();
   _recursiveDirectoryIteratorMock->SetFileSubpathsToNotCopyMock.Expect();
   _memberForEacher_CopyEachFileOrFolderToFolderMock->CallConstMemberFunctionForEachElementMock.Expect();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   _cloudundancyFileCopier.CopyFilesAndFoldersToMultipleDestinationFolders(args.iniFilePath);
   //
   METALMOCK(_cloudundancyIniFileReaderMock->ReadIniFileMock.CalledOnceWith(args.iniFilePath));
   METALMOCK(_recursiveDirectoryIteratorMock->SetFileSubpathsToNotCopyMock.CalledOnceWith(cloudundancyIni.fileSubpathsToNotCopy));
   METALMOCK(_memberForEacher_CopyEachFileOrFolderToFolderMock->CallConstMemberFunctionForEachElementMock.CalledOnceWith(
      cloudundancyIni.destinationFolderPaths,
      &CloudundancyFileCopier::CopyFilesAndFoldersToDestinationFolder,
      &_cloudundancyFileCopier, cloudundancyIni));
}

// Private Functions

TEST(CopyFilesAndFoldersToDestinationFolder_AppendBackupStartedToLogFile_CopiesNonSkippedSourceFilesToDestinationFolder_AppendBackupSuccessfulToLogFile)
{
   _cloudundancyLogFileAppenderMock->AppendTextToCloudundancyLogFileInFolderMock.Expect();

   _stopwatchMock->StartMock.Expect();

   _memberForEacher_CopyFileOrFolderToFolderMock->CallConstMemberFunctionForEachElementMock.Expect();

   const string elapsedSeconds = _stopwatchMock->StopAndGetElapsedSecondsMock.ReturnRandom();

   _consoleMock->WriteLineMock.Expect();

   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   const CloudundancyIni cloudundancyIni = ZenUnit::Random<CloudundancyIni>();
   //
   _cloudundancyFileCopier.CopyFilesAndFoldersToDestinationFolder(destinationFolderPath, cloudundancyIni);
   //
   const string expectedBackupSuccessfulLogFileMessage = String::Concat(
      "Cloudundancy backup successful in ", elapsedSeconds, " seconds");
   METALMOCK(_cloudundancyLogFileAppenderMock->AppendTextToCloudundancyLogFileInFolderMock.CalledAsFollows(
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
   const string expectedFolderBackedUpMessage = String::Concat(
      "[Cloudundancy]   FolderBackupResult: All files copied to ", destinationFolderPath.string(), '\n',
      "[Cloudundancy] FolderBackupDuration: ", elapsedSeconds, " seconds\n");
   METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(expectedFolderBackedUpMessage));
}

TEST(CopyFileOrFolderToFolder_SourcePathHasAFileName_CallsCopyFileToFolder)
{
   _memberCaller_CopyFileFunctionsMock->ConstCallMock.Expect();
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   const CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction =
      ZenUnit::Random<CloudundancyIniCopyInstruction>();
   //
   _cloudundancyFileCopier.CopyFileOrFolderToFolder(cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   METALMOCK(_memberCaller_CopyFileFunctionsMock->ConstCallMock.CalledOnceWith(
      &CloudundancyFileCopier::TryCopyFileToFolder,
      &_cloudundancyFileCopier, cloudundancyIniCopyInstruction, destinationFolderPath));
}

TEST1X1(CopyFileOrFolderToFolder_SourcePathDoesNotHaveAFileNameMeaningItIsAFolder_CallsRecursivelyCopyNonIgnoredFilesToFolder,
   const fs::path& sourceFileOrFolderPath,
   "FolderNameA/",
   "FolderNameB\\")
{
   _memberCaller_CopyFileFunctionsMock->ConstCallMock.Expect();
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction = ZenUnit::Random<CloudundancyIniCopyInstruction>();
   cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath = sourceFileOrFolderPath;
   //
   _cloudundancyFileCopier.CopyFileOrFolderToFolder(cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   METALMOCK(_memberCaller_CopyFileFunctionsMock->ConstCallMock.CalledOnceWith(
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

   _memberCaller_TryCopyFileMock->ConstCallMock.Expect();

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
   METALMOCK(_memberCaller_TryCopyFileMock->ConstCallMock.CalledOnceWith(
      &CloudundancyFileCopier::TryCopyFile, &_cloudundancyFileCopier, sourceFilePath, expectedDestinationFilePath));
}

TEST(CopyNestedFileToFolder_RelativeDestinationFolderPathIsNotDot_CopiesNestedFileToFolderWithRelativeDestinationFolderPathPresentInTheDestinationFilePath)
{
   const fs::path sourceFilePathRelativeToSourceFolderPath = ReplaceFirstMock.ReturnRandom();

   _memberCaller_TryCopyFileMock->ConstCallMock.Expect();

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
   METALMOCK(_memberCaller_TryCopyFileMock->ConstCallMock.CalledOnceWith(
      &CloudundancyFileCopier::TryCopyFile, &_cloudundancyFileCopier, sourceFilePath, expectedDestinationFilePath));
}

TEST(TryCopyFile_FileSizeIsGreaterThanOrEqualTo2GB_CopiesFileWithStdFilesystemCopyFile_WritesCopiedIfCopySucceeded_WritesCopyFailedIfCopyFailed)
{
   _consoleMock->WriteMock.Expect();

   _fileSystemMock->IsFileSizeGreaterThanOrEqualTo2GBMock.Return(true);

   const FileCopyResult fileCopyResult = ZenUnit::Random<FileCopyResult>();
   _fileSystemMock->TryCopyFileWithStdFilesystemCopyFileMock.Return(fileCopyResult);

   _memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.Expect();

   const fs::path sourceFilePath = ZenUnit::Random<fs::path>();
   const fs::path destinationFilePath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileCopier.TryCopyFile(sourceFilePath, destinationFilePath);
   //
   const string expectedCopyingFileMessage = String::Concat(
      "Copying ", sourceFilePath.string(), '\n',
      "     to ", destinationFilePath.string(), ". ");
   METALMOCK(_consoleMock->WriteMock.CalledOnceWith(expectedCopyingFileMessage));
   METALMOCK(_fileSystemMock->IsFileSizeGreaterThanOrEqualTo2GBMock.CalledOnceWith(sourceFilePath));
   METALMOCK(_fileSystemMock->TryCopyFileWithStdFilesystemCopyFileMock.CalledOnceWith(sourceFilePath, destinationFilePath));
   METALMOCK(_memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyFileCopier::WriteCopiedMessageOrExitWithCode1IfCopyFailed, &_cloudundancyFileCopier, fileCopyResult));
}

TEST(TryCopyFile_FileSizeIsLessThan2GB_CopiesFileWithCStyleCopyFile_WritesCopiedIfCopySucceeded_WritesCopyFailedIfCopyFailed)
{
   _consoleMock->WriteMock.Expect();

   _fileSystemMock->IsFileSizeGreaterThanOrEqualTo2GBMock.Return(false);

   const FileCopyResult fileCopyResult = ZenUnit::Random<FileCopyResult>();
   _fileSystemMock->TryCopyFileMock.Return(fileCopyResult);

   _memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.Expect();

   const fs::path sourceFilePath = ZenUnit::Random<fs::path>();
   const fs::path destinationFilePath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileCopier.TryCopyFile(sourceFilePath, destinationFilePath);
   //
   const string expectedCopyingFileMessage = String::Concat(
      "Copying ", sourceFilePath.string(), '\n',
      "     to ", destinationFilePath.string(), ". ");
   METALMOCK(_consoleMock->WriteMock.CalledOnceWith(expectedCopyingFileMessage));
   METALMOCK(_fileSystemMock->IsFileSizeGreaterThanOrEqualTo2GBMock.CalledOnceWith(sourceFilePath));
   METALMOCK(_fileSystemMock->TryCopyFileMock.CalledOnceWith(sourceFilePath, destinationFilePath));
   METALMOCK(_memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedMock->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyFileCopier::WriteCopiedMessageOrExitWithCode1IfCopyFailed, &_cloudundancyFileCopier, fileCopyResult));
}

TEST(TryCopyFileToFolder_RelativeDestinationFolderPathIsADot_DoesNotJoinDotCharacter_CallsTryCopyFile)
{
   _memberCaller_TryCopyFileMock->ConstCallMock.Expect();
   CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction = ZenUnit::Random<CloudundancyIniCopyInstruction>();
   cloudundancyIniCopyInstruction.relativeDestinationFolderPath = ".";
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileCopier.TryCopyFileToFolder(cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   const fs::path& expectedSourceFilePath = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath;
   const fs::path expectedSourceFileName = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath.filename();
   const fs::path expectedDestinationFilePath = destinationFolderPath / expectedSourceFileName;
   METALMOCK(_memberCaller_TryCopyFileMock->ConstCallMock.CalledOnceWith(
      &CloudundancyFileCopier::TryCopyFile, &_cloudundancyFileCopier, expectedSourceFilePath, expectedDestinationFilePath));
}

TEST(TryCopyFileToFolder_RelativeDestinationFolderPathIsNotADot_JoinsRelativeDestinationFolder_CallsTryCopyFile)
{
   _memberCaller_TryCopyFileMock->ConstCallMock.Expect();
   const CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction = ZenUnit::Random<CloudundancyIniCopyInstruction>();
   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileCopier.TryCopyFileToFolder(cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   const fs::path& expectedSourceFilePath = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath;
   const fs::path expectedSourceFileName = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath.filename();
   const fs::path expectedDestinationFilePath =
      destinationFolderPath / cloudundancyIniCopyInstruction.relativeDestinationFolderPath / expectedSourceFileName;
   METALMOCK(_memberCaller_TryCopyFileMock->ConstCallMock.CalledOnceWith(
      &CloudundancyFileCopier::TryCopyFile, &_cloudundancyFileCopier, expectedSourceFilePath, expectedDestinationFilePath));
}

TEST(WriteCopiedMessageOrExitWithCode1IfCopyFailed_CopySucceeded_WritesCopiedAndDurationInMilliseconds)
{
   _consoleMock->WriteLineColorMock.Expect();
   FileCopyResult fileCopyResult = ZenUnit::Random<FileCopyResult>();
   fileCopyResult.copySucceeded = true;
   //
   _cloudundancyFileCopier.WriteCopiedMessageOrExitWithCode1IfCopyFailed(fileCopyResult);
   //
   const string expectedCopiedMessage = String::Concat("Copied [", fileCopyResult.durationInMilliseconds, "ms]\n");
   METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedCopiedMessage, Color::Green));
}

TEST(WriteCopiedMessageOrExitWithCode1IfCopyFailed_CopyFailed_WritesCopyFailedAndDurationInMillisecondsAndCopyFailureReason_ExitsProgramWithCode1)
{
   _consoleMock->WriteLineColorMock.Expect();
   exitMock.Expect();
   FileCopyResult fileCopyResult = ZenUnit::Random<FileCopyResult>();
   fileCopyResult.copySucceeded = false;
   //
   _cloudundancyFileCopier.WriteCopiedMessageOrExitWithCode1IfCopyFailed(fileCopyResult);
   //
   const string expectedCopyFailedMessage = String::Concat(
      "Copy failed [", fileCopyResult.durationInMilliseconds, "ms]: ", fileCopyResult.copyFailureReason, '\n');
   METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedCopyFailedMessage, Color::Red));
   METALMOCK(exitMock.CalledOnceWith(1));
}

RUN_TESTS(CloudundancyFileCopierTests)
