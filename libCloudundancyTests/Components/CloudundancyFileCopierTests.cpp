#include "pch.h"
#include "libCloudundancy/Components/CloudundancyFileCopier.h"
#include "libCloudundancy/ValueTypes/AbsoluteFilePathToRelativeDestinationFolderPath.h"
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"
#include "libCloudundancy/ValueTypes/CloudundancyIni.h"
#include "libCloudundancyTests/Components/MetalMock/CloudundancyIniFileReaderMock.h"
#include "libCloudundancyTests/Components/MetalMock/RecursiveDirectoryIteratorMock.h"

TESTS(CloudundancyFileCopierTests)
AFACT(DefaultConstructor_NewsComponentsAndSetsFunctions)
AFACT(CopyFilesAndFoldersToMultipleFolders_CopiesFilesAndFoldersToFolders)
AFACT(DeleteFolder_CallsFileSystemDelete)
// Private Functions
AFACT(CopyFilesAndFoldersToSingleFolder_CopiesNonSkippedSourceFilesToDestinationFolder)
AFACT(CopyFileOrFolderToFolder_SourcePathHasAFileName_CallsCopyFileToFolder)
FACTS(CopyFileOrFolderToFolder_SourcePathDoesNotHaveAFileNameMeaningItIsAFolder_CallsRecursivelyCopyNonIgnoredFilesToFolder)
AFACT(CopyNonIgnoredFilesInAndBelowFolderToFolder_CopiesNonIgnoredFilesToFolderUntilRecursiveDirectoryIteratorReturnsNoMoreFiles)
AFACT(CopyNestedFileToFolder_RelativeDestinationFolderPathIsDot_CopiesNestedFileToFolderWithSlashDotSlashNotPresentInTheDestinationFilePath)
AFACT(CopyNestedFileToFolder_RelativeDestinationFolderPathIsNotDot_CopiesNestedFileToFolderWithRelativeDestinationFolderPathPresentInTheDestinationFilePath)
FACTS(TryCopyFile_CopiesFile_WritesCopiedIfCopySucceeds_WritesCopyFailedIfCopyFails)
AFACT(TryCopyFileToFolder_RelativeDestinationFolderPathIsADot_DoesNotJoinDotCharacter_CallsTryCopyFile)
AFACT(TryCopyFileToFolder_RelativeDestinationFolderPathIsNotADot_JoinsRelativeDestinationFolder_CallsTryCopyFile)
EVIDENCE

CloudundancyFileCopier _cloudundancyFileCopier;
// Function Callers
METALMOCK_NONVOID3_STATIC(string, String, ReplaceFirst, const string&, const string&, const string&)

using OneExtraArgMemberForEacherOfCopyInstructionsMockType = const OneExtraArgMemberForEacherMock<
   fs::path, CloudundancyFileCopier,
   void(CloudundancyFileCopier::*)(const fs::path&, const CloudundancyIni&) const,
   const CloudundancyIni&>;
OneExtraArgMemberForEacherOfCopyInstructionsMockType* _callerMock_CopyEachFileOrFolderToFolder = nullptr;

using OneExtraArgMemberForEacherOfDestinationFolderPathsMockType = const OneExtraArgMemberForEacherMock<
   AbsoluteFileOrFolderPathToRelativeFolderPath, CloudundancyFileCopier,
   void(CloudundancyFileCopier::*)(const AbsoluteFileOrFolderPathToRelativeFolderPath&, const fs::path&) const,
   const fs::path&>;
OneExtraArgMemberForEacherOfDestinationFolderPathsMockType* _callerMock_CopyFileOrFolderToFolder = nullptr;

using VoidTwoArgMemberFunctionCallerMockType = const VoidTwoArgMemberFunctionCallerMock<
   CloudundancyFileCopier, const AbsoluteFileOrFolderPathToRelativeFolderPath&, const fs::path&>;
VoidTwoArgMemberFunctionCallerMockType* _callerMock_CopyFileFunctions = nullptr;

using CallerMockType_CopyNestedFileToFolder = const VoidThreeArgMemberFunctionCallerMock<
   CloudundancyFileCopier, const fs::path&, const AbsoluteFileOrFolderPathToRelativeFolderPath&, const fs::path&>;
CallerMockType_CopyNestedFileToFolder* _callerMock_CopyNestedFileToFolder = nullptr;

using VoidTryCopyFileCallerMockType = const VoidTwoArgMemberFunctionCallerMock<
   CloudundancyFileCopier, const fs::path&, const fs::path&>;
VoidTryCopyFileCallerMockType* _callerMock_TryCopyFile = nullptr;

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
   _cloudundancyFileCopier._caller_CopyEachFileOrFolderToFolder.reset(_callerMock_CopyEachFileOrFolderToFolder = new OneExtraArgMemberForEacherOfCopyInstructionsMockType);
   _cloudundancyFileCopier._caller_CopyFileOrFolderToFolder.reset(_callerMock_CopyFileOrFolderToFolder = new OneExtraArgMemberForEacherOfDestinationFolderPathsMockType);
   _cloudundancyFileCopier._caller_CopyFileFunctions.reset(_callerMock_CopyFileFunctions = new VoidTwoArgMemberFunctionCallerMockType);
   _cloudundancyFileCopier._caller_CopyNestedFileToFolder.reset(_callerMock_CopyNestedFileToFolder = new CallerMockType_CopyNestedFileToFolder);
   _cloudundancyFileCopier._caller_TryCopyFile.reset(_callerMock_TryCopyFile = new VoidTryCopyFileCallerMockType);
   // Components
   _cloudundancyFileCopier._cloudundancyIniFileReader.reset(_cloudundancyIniFileReaderMock = new CloudundancyIniFileReaderMock);
   _cloudundancyFileCopier._console.reset(_consoleMock = new ConsoleMock);
   _cloudundancyFileCopier._fileSystem.reset(_fileSystemMock = new FileSystemMock);
   // Mutable Components
   _cloudundancyFileCopier._recursiveDirectoryIterator.reset(_recursiveDirectoryIteratorMock = new RecursiveDirectoryIteratorMock);
   _cloudundancyFileCopier._stopwatch.reset(_stopwatchMock = new StopwatchMock);
}

TEST(DefaultConstructor_NewsComponentsAndSetsFunctions)
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
   _callerMock_CopyEachFileOrFolderToFolder->OneExtraArgMemberForEachMock.Expect();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   _cloudundancyFileCopier.CopyFilesAndFoldersToMultipleFolders(args.iniFilePath);
   //
   METALMOCK(_cloudundancyIniFileReaderMock->ReadIniFileMock.CalledOnceWith(args.iniFilePath));
   METALMOCK(_recursiveDirectoryIteratorMock->SetFileSubpathsToNotCopyMock.CalledOnceWith(cloudundancyIni.fileSubpathsToNotCopy));
   METALMOCK(_callerMock_CopyEachFileOrFolderToFolder->OneExtraArgMemberForEachMock.CalledOnceWith(
      cloudundancyIni.destinationFolderPaths, &_cloudundancyFileCopier, &CloudundancyFileCopier::CopyFilesAndFoldersToSingleFolder, cloudundancyIni));
}

TEST(DeleteFolder_CallsFileSystemDelete)
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

   _callerMock_CopyFileOrFolderToFolder->OneExtraArgMemberForEachMock.Expect();

   const string elapsedSeconds = _stopwatchMock->StopAndGetElapsedSecondsMock.ReturnRandom();

   _consoleMock->WriteLineMock.Expect();

   const fs::path destinationFolderPath = ZenUnit::Random<fs::path>();
   const CloudundancyIni cloudundancyIni = ZenUnit::Random<CloudundancyIni>();
   //
   _cloudundancyFileCopier.CopyFilesAndFoldersToSingleFolder(destinationFolderPath, cloudundancyIni);
   //
   METALMOCK(_stopwatchMock->StartMock.CalledOnce());
   METALMOCK(_callerMock_CopyFileOrFolderToFolder->OneExtraArgMemberForEachMock.CalledOnceWith(
      cloudundancyIni.absoluteFileOrFolderPathAndRelativeFolderPaths, &_cloudundancyFileCopier, &CloudundancyFileCopier::CopyFileOrFolderToFolder, destinationFolderPath));
   METALMOCK(_stopwatchMock->StopAndGetElapsedSecondsMock.CalledOnce());
   const string expectedFolderBackedUpMessage =
      "[Cloudundancy]  FolderBackupResult: All files copied to " + destinationFolderPath.string() + "\n" +
      "[Cloudundancy]   FolderElapsedTime: " + elapsedSeconds + " seconds\n";
   METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(expectedFolderBackedUpMessage));
}

TEST(CopyFileOrFolderToFolder_SourcePathHasAFileName_CallsCopyFileToFolder)
{
   _callerMock_CopyFileFunctions->ConstCallMock.Expect();
   const fs::path destinationFolderPath = ZenUnit::RandomRelativeFilePath();
   const AbsoluteFileOrFolderPathToRelativeFolderPath cloudundancyIniCopyInstruction =
      ZenUnit::Random<AbsoluteFileOrFolderPathToRelativeFolderPath>();
   //
   _cloudundancyFileCopier.CopyFileOrFolderToFolder(cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   METALMOCK(_callerMock_CopyFileFunctions->ConstCallMock.CalledOnceWith(
      &_cloudundancyFileCopier, &CloudundancyFileCopier::TryCopyFileToFolder, cloudundancyIniCopyInstruction, destinationFolderPath));
}

TEST1X1(CopyFileOrFolderToFolder_SourcePathDoesNotHaveAFileNameMeaningItIsAFolder_CallsRecursivelyCopyNonIgnoredFilesToFolder,
   const fs::path& sourceFileOrFolderPath,
   "FolderNameA/",
   "FolderNameB\\")
{
   _callerMock_CopyFileFunctions->ConstCallMock.Expect();
   const fs::path destinationFolderPath = ZenUnit::RandomRelativeFilePath();
   AbsoluteFileOrFolderPathToRelativeFolderPath cloudundancyIniCopyInstruction = ZenUnit::Random<AbsoluteFileOrFolderPathToRelativeFolderPath>();
   cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath = sourceFileOrFolderPath;
   //
   _cloudundancyFileCopier.CopyFileOrFolderToFolder(cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   METALMOCK(_callerMock_CopyFileFunctions->ConstCallMock.CalledOnceWith(
      &_cloudundancyFileCopier, &CloudundancyFileCopier::CopyNonIgnoredFilesInAndBelowFolderToFolder,
      cloudundancyIniCopyInstruction, destinationFolderPath));
}

TEST(CopyNonIgnoredFilesInAndBelowFolderToFolder_CopiesNonIgnoredFilesToFolderUntilRecursiveDirectoryIteratorReturnsNoMoreFiles)
{
   _recursiveDirectoryIteratorMock->InitializeIteratorAtFolderPathMock.Expect();

   const fs::path nonIgnoredSourceFilePath1 = ZenUnit::RandomRelativeFilePath();
   const fs::path nonIgnoredSourceFilePath2 = ZenUnit::RandomRelativeFilePath();
   const fs::path terminatorFilePath;
   _recursiveDirectoryIteratorMock->NextNonIgnoredFilePathMock.ReturnValues(
      nonIgnoredSourceFilePath1, nonIgnoredSourceFilePath2, terminatorFilePath);

   _callerMock_CopyNestedFileToFolder->ConstCallMock.Expect();

   const AbsoluteFileOrFolderPathToRelativeFolderPath cloudundancyIniCopyInstruction = ZenUnit::Random<AbsoluteFileOrFolderPathToRelativeFolderPath>();
   const fs::path destinationFolderPath = ZenUnit::RandomRelativeFilePath();
   //
   _cloudundancyFileCopier.CopyNonIgnoredFilesInAndBelowFolderToFolder(cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   METALMOCK(_recursiveDirectoryIteratorMock->InitializeIteratorAtFolderPathMock.
      CalledOnceWith(cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath));
   METALMOCK(_recursiveDirectoryIteratorMock->NextNonIgnoredFilePathMock.CalledNTimes(3));
   METALMOCK(_callerMock_CopyNestedFileToFolder->ConstCallMock.CalledAsFollows(
   {
      { &_cloudundancyFileCopier, &CloudundancyFileCopier::CopyNestedFileToFolder, nonIgnoredSourceFilePath1, cloudundancyIniCopyInstruction, destinationFolderPath },
      { &_cloudundancyFileCopier, &CloudundancyFileCopier::CopyNestedFileToFolder, nonIgnoredSourceFilePath2, cloudundancyIniCopyInstruction, destinationFolderPath }
   }));
}

TEST(CopyNestedFileToFolder_RelativeDestinationFolderPathIsDot_CopiesNestedFileToFolderWithSlashDotSlashNotPresentInTheDestinationFilePath)
{
   const fs::path sourceFilePathRelativeToSourceFolderPath = ReplaceFirstMock.ReturnRandom();

   _callerMock_TryCopyFile->ConstCallMock.Expect();

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
   METALMOCK(_callerMock_TryCopyFile->ConstCallMock.CalledOnceWith(
      &_cloudundancyFileCopier, &CloudundancyFileCopier::TryCopyFile, sourceFilePath, expectedDestinationFilePath));
}

TEST(CopyNestedFileToFolder_RelativeDestinationFolderPathIsNotDot_CopiesNestedFileToFolderWithRelativeDestinationFolderPathPresentInTheDestinationFilePath)
{
   const fs::path sourceFilePathRelativeToSourceFolderPath = ReplaceFirstMock.ReturnRandom();

   _callerMock_TryCopyFile->ConstCallMock.Expect();

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
   METALMOCK(_callerMock_TryCopyFile->ConstCallMock.CalledOnceWith(
      &_cloudundancyFileCopier, &CloudundancyFileCopier::TryCopyFile, sourceFilePath, expectedDestinationFilePath));
}

TEST3X3(TryCopyFile_CopiesFile_WritesCopiedIfCopySucceeds_WritesCopyFailedIfCopyFails,
   bool copySucceeded, const string& expectedWriteLine, Color expectedColor,
   true, "Copied [durationInMillisecondsms]\n", Color::Green,
   false, "Copy failed [durationInMillisecondsms]\n", Color::Red)
{
   _consoleMock->WriteMock.Expect();

   FileCopyResult fileCopyResult;
   fileCopyResult.copySucceeded = copySucceeded;
   _fileSystemMock->TryCopyFileMock.Return(fileCopyResult);

   _consoleMock->WriteLineColorMock.Expect();

   const fs::path sourceFilePath = ZenUnit::RandomRelativeFilePath();
   const fs::path destinationFilePath = ZenUnit::RandomRelativeFilePath();
   //
   _cloudundancyFileCopier.TryCopyFile(sourceFilePath, destinationFilePath);
   //
   const string expectedCopyingFileMessage = String::Concat(
      "Copying ", sourceFilePath.string(), '\n', "     to ", destinationFilePath.string(), ". ");
   METALMOCK(_consoleMock->WriteMock.CalledOnceWith(expectedCopyingFileMessage));
   METALMOCK(_fileSystemMock->TryCopyFileMock.CalledOnceWith(sourceFilePath, destinationFilePath));
   const string expectedWriteLineWithMilliseconds =
      String::ReplaceFirst(expectedWriteLine, "durationInMilliseconds", to_string(fileCopyResult.durationInMilliseconds));
   METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith(expectedWriteLineWithMilliseconds, expectedColor));
}

TEST(TryCopyFileToFolder_RelativeDestinationFolderPathIsADot_DoesNotJoinDotCharacter_CallsTryCopyFile)
{
   _callerMock_TryCopyFile->ConstCallMock.Expect();
   AbsoluteFileOrFolderPathToRelativeFolderPath cloudundancyIniCopyInstruction = ZenUnit::Random<AbsoluteFileOrFolderPathToRelativeFolderPath>();
   cloudundancyIniCopyInstruction.relativeDestinationFolderPath = ".";
   const fs::path destinationFolderPath = ZenUnit::RandomRelativeFilePath();
   //
   _cloudundancyFileCopier.TryCopyFileToFolder(cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   const fs::path& expectedSourceFilePath = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath;
   const fs::path expectedSourceFileName = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath.filename();
   const fs::path expectedDestinationFilePath = destinationFolderPath / expectedSourceFileName;
   METALMOCK(_callerMock_TryCopyFile->ConstCallMock.CalledOnceWith(
      &_cloudundancyFileCopier, &CloudundancyFileCopier::TryCopyFile, expectedSourceFilePath, expectedDestinationFilePath));
}

TEST(TryCopyFileToFolder_RelativeDestinationFolderPathIsNotADot_JoinsRelativeDestinationFolder_CallsTryCopyFile)
{
   _callerMock_TryCopyFile->ConstCallMock.Expect();
   const AbsoluteFileOrFolderPathToRelativeFolderPath cloudundancyIniCopyInstruction = ZenUnit::Random<AbsoluteFileOrFolderPathToRelativeFolderPath>();
   const fs::path destinationFolderPath = ZenUnit::RandomRelativeFilePath();
   //
   _cloudundancyFileCopier.TryCopyFileToFolder(cloudundancyIniCopyInstruction, destinationFolderPath);
   //
   const fs::path& expectedSourceFilePath = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath;
   const fs::path expectedSourceFileName = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath.filename();
   const fs::path expectedDestinationFilePath =
      destinationFolderPath / cloudundancyIniCopyInstruction.relativeDestinationFolderPath / expectedSourceFileName;
   METALMOCK(_callerMock_TryCopyFile->ConstCallMock.CalledOnceWith(
      &_cloudundancyFileCopier, &CloudundancyFileCopier::TryCopyFile, expectedSourceFilePath, expectedDestinationFilePath));
}

RUN_TESTS(CloudundancyFileCopierTests)
