#include "pch.h"
#include "libCloudundancy/ValueTypes/AbsoluteFilePathToRelativeDestinationFolderPath.h"
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"
#include "libCloudundancy/ValueTypes/CloudundancyIni.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyFileCopier.h"
#include "libCloudundancyTests/Components/Console/MetalMock/ConsoleMock.h"
#include "libCloudundancyTests/Components/FileSystem/MetalMock/FileSystemMock.h"
#include "libCloudundancyTests/Components/FileSystem/MetalMock/RecursiveDirectoryIteratorMock.h"
#include "libCloudundancyTests/Components/IniFile/MetalMock/CloudundancyIniFileReaderMock.h"
#include "libCloudundancyTests/Components/Iteration/ForEach/MetalMock/OneExtraArgMemberFunctionForEacherMock.h"
#include "libCloudundancyTests/Components/FunctionCallers/MemberFunctions/MetalMock/VoidOneArgMemberFunctionCallerMock.h"
#include "libCloudundancyTests/Components/FunctionCallers/MemberFunctions/MetalMock/VoidTwoArgMemberFunctionCallerMock.h"
#include "libCloudundancyTests/Components/FunctionCallers/MemberFunctions/MetalMock/VoidThreeArgMemberFunctionCallerMock.h"
#include "libCloudundancyTests/Components/Time/MetalMock/StopwatchMock.h"

TESTS(CloudundancyFileCopierTests)
AFACT(DefaultConstructor_SetsFunctionsAndNewsComponents)
AFACT(CopyFilesAndFoldersToMultipleFolders_CopiesFilesAndFoldersToFolders)
AFACT(DeleteFolder_CallsFileSystemDeleteFolderOnFolderPath)
// Private Functions
AFACT(CopyFilesAndFoldersToSingleFolder_CopiesNonSkippedSourceFilesToDestinationFolder)
AFACT(CopyFileOrFolderToFolder_SourcePathHasAFileName_CallsCopyFileToFolder)
FACTS(CopyFileOrFolderToFolder_SourcePathDoesNotHaveAFileNameMeaningItIsAFolder_CallsRecursivelyCopyNonIgnoredFilesToFolder)
AFACT(CopyNonIgnoredFilesInAndBelowFolderToFolder_CopiesNonIgnoredFilesToFolderUntilRecursiveDirectoryIteratorReturnsNoMoreFiles)
AFACT(CopyNestedFileToFolder_RelativeDestinationFolderPathIsDot_CopiesNestedFileToFolderWithSlashDotSlashNotPresentInTheDestinationFilePath)
AFACT(CopyNestedFileToFolder_RelativeDestinationFolderPathIsNotDot_CopiesNestedFileToFolderWithRelativeDestinationFolderPathPresentInTheDestinationFilePath)
AFACT(TryCopyFile_FileSizeIsGreaterThanOrEqualTo2GB_CopiesFileWithStdFilesystemCopyFile_WritesCopiedIfCopySucceeded_WritesCopyFailedIfCopyFailed)
AFACT(TryCopyFile_FileSizeIsLessThan2GB_CopiesFileWithCStyleCopyFile_WritesCopiedIfCopySucceeded_WritesCopyFailedIfCopyFailed)
AFACT(TryCopyFileToFolder_RelativeDestinationFolderPathIsADot_DoesNotJoinDotCharacter_CallsTryCopyFile)
AFACT(TryCopyFileToFolder_RelativeDestinationFolderPathIsNotADot_JoinsRelativeDestinationFolder_CallsTryCopyFile)
FACTS(WriteCopiedOrCopyFailedMessage_WritesCopiedIfCopySucceeded_WritesCopyFailedIfCopyFailed)
EVIDENCE

CloudundancyFileCopier _cloudundancyFileCopier;
// Function Callers
METALMOCK_NONVOID3_STATIC(string, String, ReplaceFirst, const string&, const string&, const string&)

using OneExtraArgMemberFunctionForEacherOfCopyInstructionsMockType = const OneExtraArgMemberFunctionForEacherMock<
   fs::path, void(CloudundancyFileCopier::*)(const fs::path&, const CloudundancyIni&) const,
   CloudundancyFileCopier, const CloudundancyIni&>;
OneExtraArgMemberFunctionForEacherOfCopyInstructionsMockType* _caller_CopyEachFileOrFolderToFolderMock = nullptr;

using OneExtraArgMemberFunctionForEacherOfDestinationFolderPathsMockType = const OneExtraArgMemberFunctionForEacherMock<
   AbsoluteFileOrFolderPathToRelativeFolderPath,
   void(CloudundancyFileCopier::*)(const AbsoluteFileOrFolderPathToRelativeFolderPath&, const fs::path&) const,
   CloudundancyFileCopier,
   const fs::path&>;
OneExtraArgMemberFunctionForEacherOfDestinationFolderPathsMockType* _caller_CopyFileOrFolderToFolderMock = nullptr;

using VoidTwoArgMemberFunctionCallerMockType = const VoidTwoArgMemberFunctionCallerMock<
   CloudundancyFileCopier, const AbsoluteFileOrFolderPathToRelativeFolderPath&, const fs::path&>;
VoidTwoArgMemberFunctionCallerMockType* _caller_CopyFileFunctionsMock = nullptr;

using CallerMockType_CopyNestedFileToFolder = const VoidThreeArgMemberFunctionCallerMock<
   CloudundancyFileCopier, const fs::path&, const AbsoluteFileOrFolderPathToRelativeFolderPath&, const fs::path&>;
CallerMockType_CopyNestedFileToFolder* _caller_CopyNestedFileToFolderMock = nullptr;

using VoidTryCopyFileCallerMockType = const VoidTwoArgMemberFunctionCallerMock<
   CloudundancyFileCopier, const fs::path&, const fs::path&>;
VoidTryCopyFileCallerMockType* _caller_TryCopyFileMock = nullptr;

using _caller_WriteCopiedOrCopyFailedMessageMockType = VoidOneArgMemberFunctionCallerMock<
   CloudundancyFileCopier, const FileCopyResult&>;
_caller_WriteCopiedOrCopyFailedMessageMockType* _caller_WriteCopiedOrCopyFailedMessageMock = nullptr;

// Constant Components
CloudundancyIniFileReaderMock* _cloudundancyIniFileReaderMock = nullptr;
ConsoleMock* _consoleMock = nullptr;
FileSystemMock* _fileSystemMock = nullptr;

// Mutable Components
RecursiveDirectoryIteratorMock* _recursiveDirectoryIteratorMock = nullptr;
StopwatchMock* _stopwatchMock = nullptr;

STARTUP
{
   // Function Callers
   _cloudundancyFileCopier._call_String_ReplaceFirst = BIND_3ARG_METALMOCK_OBJECT(ReplaceFirstMock);
   _cloudundancyFileCopier._caller_CopyEachFileOrFolderToFolder.reset(_caller_CopyEachFileOrFolderToFolderMock = new OneExtraArgMemberFunctionForEacherOfCopyInstructionsMockType);
   _cloudundancyFileCopier._caller_CopyFileOrFolderToFolder.reset(_caller_CopyFileOrFolderToFolderMock = new OneExtraArgMemberFunctionForEacherOfDestinationFolderPathsMockType);
   _cloudundancyFileCopier._caller_CopyFileFunctions.reset(_caller_CopyFileFunctionsMock = new VoidTwoArgMemberFunctionCallerMockType);
   _cloudundancyFileCopier._caller_CopyNestedFileToFolder.reset(_caller_CopyNestedFileToFolderMock = new CallerMockType_CopyNestedFileToFolder);
   _cloudundancyFileCopier._caller_TryCopyFile.reset(_caller_TryCopyFileMock = new VoidTryCopyFileCallerMockType);
   _cloudundancyFileCopier._caller_WriteCopiedOrCopyFailedMessage.reset(_caller_WriteCopiedOrCopyFailedMessageMock = new _caller_WriteCopiedOrCopyFailedMessageMockType);
   // Components
   _cloudundancyFileCopier._cloudundancyIniFileReader.reset(_cloudundancyIniFileReaderMock = new CloudundancyIniFileReaderMock);
   _cloudundancyFileCopier._console.reset(_consoleMock = new ConsoleMock);
   _cloudundancyFileCopier._fileSystem.reset(_fileSystemMock = new FileSystemMock);
   // Mutable Components
   _cloudundancyFileCopier._recursiveDirectoryIterator.reset(_recursiveDirectoryIteratorMock = new RecursiveDirectoryIteratorMock);
   _cloudundancyFileCopier._stopwatch.reset(_stopwatchMock = new StopwatchMock);
}

TEST(DefaultConstructor_SetsFunctionsAndNewsComponents)
{
   CloudundancyFileCopier fileCopier;
   // Function Callers
   STD_FUNCTION_TARGETS(String::ReplaceFirst, fileCopier._call_String_ReplaceFirst);
   DELETE_TO_ASSERT_NEWED(fileCopier._caller_CopyEachFileOrFolderToFolder);
   DELETE_TO_ASSERT_NEWED(fileCopier._caller_CopyFileOrFolderToFolder);
   DELETE_TO_ASSERT_NEWED(fileCopier._caller_CopyFileFunctions);
   DELETE_TO_ASSERT_NEWED(fileCopier._caller_CopyNestedFileToFolder);
   DELETE_TO_ASSERT_NEWED(fileCopier._caller_TryCopyFile);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(fileCopier._cloudundancyIniFileReader);
   DELETE_TO_ASSERT_NEWED(fileCopier._console);
   DELETE_TO_ASSERT_NEWED(fileCopier._fileSystem);
   // Mutable Components
   DELETE_TO_ASSERT_NEWED(fileCopier._recursiveDirectoryIterator);
   DELETE_TO_ASSERT_NEWED(fileCopier._stopwatch);
}

TEST(CopyFilesAndFoldersToMultipleFolders_CopiesFilesAndFoldersToFolders)
{
   const CloudundancyIni cloudundancyIni = _cloudundancyIniFileReaderMock->ReadIniFileMock.ReturnRandom();
   _recursiveDirectoryIteratorMock->SetFileSubpathsToNotCopyMock.Expect();
   _caller_CopyEachFileOrFolderToFolderMock->OneExtraArgMemberFunctionForEachMock.Expect();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   _cloudundancyFileCopier.CopyFilesAndFoldersToMultipleFolders(args.iniFilePath);
   //
   METALMOCK(_cloudundancyIniFileReaderMock->ReadIniFileMock.CalledOnceWith(args.iniFilePath));
   METALMOCK(_recursiveDirectoryIteratorMock->SetFileSubpathsToNotCopyMock.CalledOnceWith(cloudundancyIni.fileSubpathsToNotCopy));
   METALMOCK(_caller_CopyEachFileOrFolderToFolderMock->OneExtraArgMemberFunctionForEachMock.CalledOnceWith(
      cloudundancyIni.destinationFolderPaths,
      &CloudundancyFileCopier::CopyFilesAndFoldersToSingleFolder,
      &_cloudundancyFileCopier, cloudundancyIni));
}

TEST(DeleteFolder_CallsFileSystemDeleteFolderOnFolderPath)
{
   _fileSystemMock->DeleteFolderMock.Expect();
   const fs::path folderPath = ZenUnit::RandomRelativeFilePath();
   //
   _cloudundancyFileCopier.DeleteFolder(folderPath);
   //
   METALMOCK(_fileSystemMock->DeleteFolderMock.CalledOnceWith(folderPath));
}

// Private Functions

TEST(CopyFilesAndFoldersToSingleFolder_CopiesNonSkippedSourceFilesToDestinationFolder)
{
   _stopwatchMock->StartMock.Expect();

   _caller_CopyFileOrFolderToFolderMock->OneExtraArgMemberFunctionForEachMock.Expect();

   const string elapsedSeconds = _stopwatchMock->StopAndGetElapsedSecondsMock.ReturnRandom();

   _consoleMock->WriteLineMock.Expect();

   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   const CloudundancyIni cloudundancyIni = ZenUnit::Random<CloudundancyIni>();
   //
   _cloudundancyFileCopier.CopyFilesAndFoldersToSingleFolder(destinationFolderPath, cloudundancyIni);
   //
   METALMOCK(_stopwatchMock->StartMock.CalledOnce());
   METALMOCK(_caller_CopyFileOrFolderToFolderMock->OneExtraArgMemberFunctionForEachMock.CalledOnceWith(
      cloudundancyIni.absoluteFileOrFolderPathAndRelativeFolderPaths,
      &CloudundancyFileCopier::CopyFileOrFolderToFolder,
      &_cloudundancyFileCopier, destinationFolderPath));
   METALMOCK(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce());
   const string expectedFolderBackedUpMessage =
      "[Cloudundancy]   FolderBackupResult: All files copied to " + destinationFolderPath.string() + "\n" +
      "[Cloudundancy] FolderBackupDuration: " + elapsedSeconds + " seconds\n";
   METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(expectedFolderBackedUpMessage));
}

TEST(CopyFileOrFolderToFolder_SourcePathHasAFileName_CallsCopyFileToFolder)
{
   _caller_CopyFileFunctionsMock->ConstCallMock.Expect();
   const fs::path destinationFolderPath = ZenUnit::RandomRelativeFilePath();
   const AbsoluteFileOrFolderPathToRelativeFolderPath cloudundancyIniCopyInstruction =
      ZenUnit::Random<AbsoluteFileOrFolderPathToRelativeFolderPath>();
   //
   _cloudundancyFileCopier.CopyFileOrFolderToFolder(cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   METALMOCK(_caller_CopyFileFunctionsMock->ConstCallMock.CalledOnceWith(
      &CloudundancyFileCopier::TryCopyFileToFolder,
      &_cloudundancyFileCopier, cloudundancyIniCopyInstruction, destinationFolderPath));
}

TEST1X1(CopyFileOrFolderToFolder_SourcePathDoesNotHaveAFileNameMeaningItIsAFolder_CallsRecursivelyCopyNonIgnoredFilesToFolder,
   const fs::path& sourceFileOrFolderPath,
   "FolderNameA/",
   "FolderNameB\\")
{
   _caller_CopyFileFunctionsMock->ConstCallMock.Expect();
   const fs::path destinationFolderPath = ZenUnit::RandomRelativeFilePath();
   AbsoluteFileOrFolderPathToRelativeFolderPath cloudundancyIniCopyInstruction = ZenUnit::Random<AbsoluteFileOrFolderPathToRelativeFolderPath>();
   cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath = sourceFileOrFolderPath;
   //
   _cloudundancyFileCopier.CopyFileOrFolderToFolder(cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   METALMOCK(_caller_CopyFileFunctionsMock->ConstCallMock.CalledOnceWith(
      &CloudundancyFileCopier::CopyNonIgnoredFilesInAndBelowFolderToFolder,
      &_cloudundancyFileCopier, cloudundancyIniCopyInstruction, destinationFolderPath));
}

TEST(CopyNonIgnoredFilesInAndBelowFolderToFolder_CopiesNonIgnoredFilesToFolderUntilRecursiveDirectoryIteratorReturnsNoMoreFiles)
{
   _recursiveDirectoryIteratorMock->InitializeIteratorAtFolderPathMock.Expect();

   const fs::path nonIgnoredSourceFilePath1 = ZenUnit::RandomRelativeFilePath();
   const fs::path nonIgnoredSourceFilePath2 = ZenUnit::RandomRelativeFilePath();
   const fs::path terminatorFilePath;
   _recursiveDirectoryIteratorMock->NextNonIgnoredFilePathMock.ReturnValues(
      nonIgnoredSourceFilePath1, nonIgnoredSourceFilePath2, terminatorFilePath);

   _caller_CopyNestedFileToFolderMock->ConstCallMock.Expect();

   const AbsoluteFileOrFolderPathToRelativeFolderPath cloudundancyIniCopyInstruction = ZenUnit::Random<AbsoluteFileOrFolderPathToRelativeFolderPath>();
   const fs::path destinationFolderPath = ZenUnit::RandomRelativeFilePath();
   //
   _cloudundancyFileCopier.CopyNonIgnoredFilesInAndBelowFolderToFolder(cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   METALMOCK(_recursiveDirectoryIteratorMock->InitializeIteratorAtFolderPathMock.
      CalledOnceWith(cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath));
   METALMOCK(_recursiveDirectoryIteratorMock->NextNonIgnoredFilePathMock.CalledNTimes(3));
   METALMOCK(_caller_CopyNestedFileToFolderMock->ConstCallMock.CalledAsFollows(
   {
      { &CloudundancyFileCopier::CopyNestedFileToFolder, &_cloudundancyFileCopier, nonIgnoredSourceFilePath1, cloudundancyIniCopyInstruction, destinationFolderPath },
      { &CloudundancyFileCopier::CopyNestedFileToFolder, &_cloudundancyFileCopier, nonIgnoredSourceFilePath2, cloudundancyIniCopyInstruction, destinationFolderPath }
   }));
}

TEST(CopyNestedFileToFolder_RelativeDestinationFolderPathIsDot_CopiesNestedFileToFolderWithSlashDotSlashNotPresentInTheDestinationFilePath)
{
   const fs::path sourceFilePathRelativeToSourceFolderPath = ReplaceFirstMock.ReturnRandom();

   _caller_TryCopyFileMock->ConstCallMock.Expect();

   const fs::path sourceFilePath = ZenUnit::RandomRelativeFilePath();
   AbsoluteFileOrFolderPathToRelativeFolderPath cloudundancyIniCopyInstruction = ZenUnit::Random<AbsoluteFileOrFolderPathToRelativeFolderPath>();
   cloudundancyIniCopyInstruction.relativeDestinationFolderPath = ".";
   const fs::path destinationFolderPath = ZenUnit::RandomRelativeFilePath();
   //
   _cloudundancyFileCopier.CopyNestedFileToFolder(sourceFilePath, cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   METALMOCK(ReplaceFirstMock.CalledOnceWith(
      sourceFilePath.string(), cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath.string(), ""));
   const fs::path expectedDestinationFilePath =
      destinationFolderPath /
      sourceFilePathRelativeToSourceFolderPath;
   METALMOCK(_caller_TryCopyFileMock->ConstCallMock.CalledOnceWith(
      &CloudundancyFileCopier::TryCopyFile, &_cloudundancyFileCopier, sourceFilePath, expectedDestinationFilePath));
}

TEST(CopyNestedFileToFolder_RelativeDestinationFolderPathIsNotDot_CopiesNestedFileToFolderWithRelativeDestinationFolderPathPresentInTheDestinationFilePath)
{
   const fs::path sourceFilePathRelativeToSourceFolderPath = ReplaceFirstMock.ReturnRandom();

   _caller_TryCopyFileMock->ConstCallMock.Expect();

   const fs::path sourceFilePath = ZenUnit::RandomRelativeFilePath();
   const AbsoluteFileOrFolderPathToRelativeFolderPath cloudundancyIniCopyInstruction = ZenUnit::Random<AbsoluteFileOrFolderPathToRelativeFolderPath>();
   const fs::path destinationFolderPath = ZenUnit::RandomRelativeFilePath();
   //
   _cloudundancyFileCopier.CopyNestedFileToFolder(sourceFilePath, cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   METALMOCK(ReplaceFirstMock.CalledOnceWith(
      sourceFilePath.string(), cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath.string(), ""));
   const fs::path expectedDestinationFilePath =
      destinationFolderPath /
      cloudundancyIniCopyInstruction.relativeDestinationFolderPath /
      sourceFilePathRelativeToSourceFolderPath;
   METALMOCK(_caller_TryCopyFileMock->ConstCallMock.CalledOnceWith(
      &CloudundancyFileCopier::TryCopyFile, &_cloudundancyFileCopier, sourceFilePath, expectedDestinationFilePath));
}

TEST(TryCopyFile_FileSizeIsGreaterThanOrEqualTo2GB_CopiesFileWithStdFilesystemCopyFile_WritesCopiedIfCopySucceeded_WritesCopyFailedIfCopyFailed)
{
   _consoleMock->WriteMock.Expect();

   _fileSystemMock->IsFileSizeGreaterThanOrEqualTo2GBMock.Return(true);

   const FileCopyResult fileCopyResult = ZenUnit::Random<FileCopyResult>();
   _fileSystemMock->TryCopyFileWithStdFilesystemCopyFileMock.Return(fileCopyResult);

   _caller_WriteCopiedOrCopyFailedMessageMock->CallConstMemberFunctionMock.Expect();

   const fs::path sourceFilePath = ZenUnit::RandomRelativeFilePath();
   const fs::path destinationFilePath = ZenUnit::RandomRelativeFilePath();
   //
   _cloudundancyFileCopier.TryCopyFile(sourceFilePath, destinationFilePath);
   //
   const string expectedCopyingFileMessage = String::Concat(
      "Copying ", sourceFilePath.string(), '\n',
      "     to ", destinationFilePath.string(), ". ");
   METALMOCK(_consoleMock->WriteMock.CalledOnceWith(expectedCopyingFileMessage));
   METALMOCK(_fileSystemMock->IsFileSizeGreaterThanOrEqualTo2GBMock.CalledOnceWith(sourceFilePath));
   METALMOCK(_fileSystemMock->TryCopyFileWithStdFilesystemCopyFileMock.CalledOnceWith(sourceFilePath, destinationFilePath));
   METALMOCK(_caller_WriteCopiedOrCopyFailedMessageMock->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyFileCopier::WriteCopiedOrCopyFailedMessage, &_cloudundancyFileCopier, fileCopyResult));
}

TEST(TryCopyFile_FileSizeIsLessThan2GB_CopiesFileWithCStyleCopyFile_WritesCopiedIfCopySucceeded_WritesCopyFailedIfCopyFailed)
{
   _consoleMock->WriteMock.Expect();

   _fileSystemMock->IsFileSizeGreaterThanOrEqualTo2GBMock.Return(false);

   const FileCopyResult fileCopyResult = ZenUnit::Random<FileCopyResult>();
   _fileSystemMock->TryCopyFileMock.Return(fileCopyResult);

   _caller_WriteCopiedOrCopyFailedMessageMock->CallConstMemberFunctionMock.Expect();

   const fs::path sourceFilePath = ZenUnit::RandomRelativeFilePath();
   const fs::path destinationFilePath = ZenUnit::RandomRelativeFilePath();
   //
   _cloudundancyFileCopier.TryCopyFile(sourceFilePath, destinationFilePath);
   //
   const string expectedCopyingFileMessage = String::Concat(
      "Copying ", sourceFilePath.string(), '\n',
      "     to ", destinationFilePath.string(), ". ");
   METALMOCK(_consoleMock->WriteMock.CalledOnceWith(expectedCopyingFileMessage));
   METALMOCK(_fileSystemMock->IsFileSizeGreaterThanOrEqualTo2GBMock.CalledOnceWith(sourceFilePath));
   METALMOCK(_fileSystemMock->TryCopyFileMock.CalledOnceWith(sourceFilePath, destinationFilePath));
   METALMOCK(_caller_WriteCopiedOrCopyFailedMessageMock->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyFileCopier::WriteCopiedOrCopyFailedMessage, &_cloudundancyFileCopier, fileCopyResult));
}

TEST(TryCopyFileToFolder_RelativeDestinationFolderPathIsADot_DoesNotJoinDotCharacter_CallsTryCopyFile)
{
   _caller_TryCopyFileMock->ConstCallMock.Expect();
   AbsoluteFileOrFolderPathToRelativeFolderPath cloudundancyIniCopyInstruction = ZenUnit::Random<AbsoluteFileOrFolderPathToRelativeFolderPath>();
   cloudundancyIniCopyInstruction.relativeDestinationFolderPath = ".";
   const fs::path destinationFolderPath = ZenUnit::RandomRelativeFilePath();
   //
   _cloudundancyFileCopier.TryCopyFileToFolder(cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   const fs::path& expectedSourceFilePath = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath;
   const fs::path expectedSourceFileName = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath.filename();
   const fs::path expectedDestinationFilePath = destinationFolderPath / expectedSourceFileName;
   METALMOCK(_caller_TryCopyFileMock->ConstCallMock.CalledOnceWith(
      &CloudundancyFileCopier::TryCopyFile, &_cloudundancyFileCopier, expectedSourceFilePath, expectedDestinationFilePath));
}

TEST(TryCopyFileToFolder_RelativeDestinationFolderPathIsNotADot_JoinsRelativeDestinationFolder_CallsTryCopyFile)
{
   _caller_TryCopyFileMock->ConstCallMock.Expect();
   const AbsoluteFileOrFolderPathToRelativeFolderPath cloudundancyIniCopyInstruction = ZenUnit::Random<AbsoluteFileOrFolderPathToRelativeFolderPath>();
   const fs::path destinationFolderPath = ZenUnit::RandomRelativeFilePath();
   //
   _cloudundancyFileCopier.TryCopyFileToFolder(cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   const fs::path& expectedSourceFilePath = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath;
   const fs::path expectedSourceFileName = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath.filename();
   const fs::path expectedDestinationFilePath =
      destinationFolderPath / cloudundancyIniCopyInstruction.relativeDestinationFolderPath / expectedSourceFileName;
   METALMOCK(_caller_TryCopyFileMock->ConstCallMock.CalledOnceWith(
      &CloudundancyFileCopier::TryCopyFile, &_cloudundancyFileCopier, expectedSourceFilePath, expectedDestinationFilePath));
}

TEST3X3(WriteCopiedOrCopyFailedMessage_WritesCopiedIfCopySucceeded_WritesCopyFailedIfCopyFailed,
   bool copySucceeded, string_view expectedWriteLine, Color expectedColor,
   true, "Copied [durationInMillisecondsms]\n", Color::Green,
   false, "Copy failed [durationInMillisecondsms]\n", Color::Red)
{
   _consoleMock->WriteLineColorMock.Expect();
   FileCopyResult fileCopyResult = ZenUnit::Random<FileCopyResult>();
   fileCopyResult.copySucceeded = copySucceeded;
   //
   _cloudundancyFileCopier.WriteCopiedOrCopyFailedMessage(fileCopyResult);
   //
   const string expectedWriteLineWithMilliseconds =
      String::ReplaceFirst(expectedWriteLine, "durationInMilliseconds", to_string(fileCopyResult.durationInMilliseconds));
   METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedWriteLineWithMilliseconds, expectedColor));
}

RUN_TESTS(CloudundancyFileCopierTests)
