#include "pch.h"
#include "libCloudundancy/ValueTypes/FilePathLineNumberLineText.h"
#include "libCloudundancy/Components/IniFile/CloudundancyIniFileReader.h"
#include "libCloudundancyTests/Components/FileSystem/MetalMock/FileSystemMock.h"
#include "libCloudundancyTests/Components/FunctionCallers/Member/MetalMock/NonVoidOneArgMemberFunctionCallerMock.h"
#include "libCloudundancyTests/Components/FunctionCallers/Member/MetalMock/VoidTwoArgMemberFunctionCallerMock.h"
#include "libCloudundancyTests/Components/IniFile/MetalMock/CloudundancyIniValidatorMock.h"

TESTS(CloudundancyIniFileReaderTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(ReadIniFile_ParsesCloudundancyIniFile_ValidatesCloudundancyIni_ReturnsExpectedCloudundancyIni)
FACTS(ParseFileCopyInstructionLine_LineDoesNotContainSpaceArrowSpace_OrLineContainsMoreThanOneSpaceArrowSpace_ThrowsFileSystemException)
FACTS(ParseFileCopyInstructionLine_LineContainsOneSpaceArrowSpace_ReturnsExpectedFileCopyInstruction)
AFACT(ThrowIfSourceFileOrFolderDoesNotExist_SourceFileOrFolderPathExists_DoesNotThrowException)
AFACT(ThrowIfSourceFileOrFolderDoesNotExist_SourceFileOrFolderPathDoesNotExist_ThrowsFileSystemException)
EVIDENCE

CloudundancyIniFileReader _cloudundancyIniFile;

// Function Callers
using NonVoidOneArgMemberFunctionCallerMockMockType = NonVoidOneArgMemberFunctionCallerMock<
   AbsoluteFileOrFolderPathToRelativeFolderPath, CloudundancyIniFileReader, const FilePathLineNumberLineText&>;
NonVoidOneArgMemberFunctionCallerMockMockType* _callerMock_ParseFileCopyInstructionLine = nullptr;

using VoidTwoArgMemberFunctionCallerMockType = VoidTwoArgMemberFunctionCallerMock<
   CloudundancyIniFileReader, const AbsoluteFileOrFolderPathToRelativeFolderPath&, const FilePathLineNumberLineText&>;
VoidTwoArgMemberFunctionCallerMockType* _callerMock_ThrowIfSourceFileOrFolderDoesNotExist = nullptr;

// Constant Components
CloudundancyIniValidatorMock* _cloudundancyIniValidatorMock = nullptr;
FileSystemMock* _fileSystemMock = nullptr;

STARTUP
{
   // Function Callers
   _cloudundancyIniFile._caller_ParseFileCopyInstructionLine.reset(
      _callerMock_ParseFileCopyInstructionLine = new NonVoidOneArgMemberFunctionCallerMockMockType);
   _cloudundancyIniFile._caller_ThrowIfSourceFileOrFolderDoesNotExist.reset(
      _callerMock_ThrowIfSourceFileOrFolderDoesNotExist = new VoidTwoArgMemberFunctionCallerMockType);
   // Constant Components
   _cloudundancyIniFile._cloudundancyIniValidator.reset(_cloudundancyIniValidatorMock = new CloudundancyIniValidatorMock);
   _cloudundancyIniFile._fileSystem.reset(_fileSystemMock = new FileSystemMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   CloudundancyIniFileReader cloudundancyIniFile;
   // Function Callers
   DELETE_TO_ASSERT_NEWED(cloudundancyIniFile._caller_ParseFileCopyInstructionLine);
   DELETE_TO_ASSERT_NEWED(cloudundancyIniFile._caller_ThrowIfSourceFileOrFolderDoesNotExist);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(cloudundancyIniFile._cloudundancyIniValidator);
   DELETE_TO_ASSERT_NEWED(cloudundancyIniFile._fileSystem);
}

TEST(ReadIniFile_ParsesCloudundancyIniFile_ValidatesCloudundancyIni_ReturnsExpectedCloudundancyIni)
{
   const string folderPathA = ZenUnit::Random<string>();
   const string folderPathC = ZenUnit::Random<string>();
   const string filePathA = ZenUnit::Random<string>();
   const string filePathB = ZenUnit::Random<string>();
   const string filePathIgnoreSubstring1 = ZenUnit::Random<string>();
   const string filePathIgnoreSubstring2 = ZenUnit::Random<string>();
   const vector<string> lines =
   {
      "",
      "[DestinationFolders]",
      folderPathA,
      "#FolderPathB",
      " \t" + folderPathC + "\t ",
      " \t ",
      "[SourceFilesAndFolders]",
      "#Comment",
      filePathA + " -> SuffixA",
      filePathB + "\t ->  SuffixB",
      "",
      "[FileSubpathsToNotCopy]",
      filePathIgnoreSubstring1,
      filePathIgnoreSubstring2
   };
   _fileSystemMock->ReadAsciiFileLinesWhichMustBeNonEmptyMock.Return(lines);

   const AbsoluteFileOrFolderPathToRelativeFolderPath fileCopyInstruction1
      = ZenUnit::Random<AbsoluteFileOrFolderPathToRelativeFolderPath>();
   const AbsoluteFileOrFolderPathToRelativeFolderPath fileCopyInstruction2
      = ZenUnit::Random<AbsoluteFileOrFolderPathToRelativeFolderPath>();
   _callerMock_ParseFileCopyInstructionLine->CallConstMemberFunctionMock.ReturnValues(fileCopyInstruction1, fileCopyInstruction2);

   _cloudundancyIniValidatorMock->ValidateCloudundancyIniMock.Expect();

   const fs::path cloudundancyIniPath = ZenUnit::Random<string>();
   //
   const CloudundancyIni cloudundancyIni = _cloudundancyIniFile.ReadIniFile(cloudundancyIniPath);
   //
   METALMOCK(_fileSystemMock->ReadAsciiFileLinesWhichMustBeNonEmptyMock.CalledOnceWith(cloudundancyIniPath));
   CloudundancyIni expectedCloudundancyIni;
   expectedCloudundancyIni.destinationFolderPaths =
   {
      fs::path(folderPathA),
      fs::path(folderPathC)
   };
   expectedCloudundancyIni.absoluteFileOrFolderPathAndRelativeFolderPaths =
   {
      fileCopyInstruction1,
      fileCopyInstruction2
   };
   expectedCloudundancyIni.fileSubpathsToNotCopy =
   {
      filePathIgnoreSubstring1,
      filePathIgnoreSubstring2
   };
   const FilePathLineNumberLineText expectedFilePathLineNumberLineText1(cloudundancyIniPath, 9, filePathA + " -> SuffixA");
   const FilePathLineNumberLineText expectedFilePathLineNumberLineText2(cloudundancyIniPath, 10, filePathB + "\t ->  SuffixB");
   METALMOCK(_callerMock_ParseFileCopyInstructionLine->CallConstMemberFunctionMock.CalledAsFollows(
   {
      { &CloudundancyIniFileReader::ParseFileCopyInstructionLine, &_cloudundancyIniFile, expectedFilePathLineNumberLineText1 },
      { &CloudundancyIniFileReader::ParseFileCopyInstructionLine, &_cloudundancyIniFile, expectedFilePathLineNumberLineText2 }
   }));
   METALMOCK(_cloudundancyIniValidatorMock->ValidateCloudundancyIniMock.CalledOnceWith(cloudundancyIni, cloudundancyIniPath));
   ARE_EQUAL(expectedCloudundancyIni, cloudundancyIni);
}

TEST1X1(ParseFileCopyInstructionLine_LineDoesNotContainSpaceArrowSpace_OrLineContainsMoreThanOneSpaceArrowSpace_ThrowsFileSystemException,
   string_view lineText,
   "Line",
   "Source->DestSuffix",
   "Source -> DestSuffix -> DestSuffix")
{
   FilePathLineNumberLineText filePathLineNumberLineText;
   filePathLineNumberLineText.filePath = ZenUnit::RandomRelativeFilePath();
   filePathLineNumberLineText.lineNumber = ZenUnit::Random<size_t>();
   filePathLineNumberLineText.lineText = lineText;
   //
   const string exceptionMessage = String::Concat("Cloudundancy .ini file line does not contain required substring \" -> \"");
   FileSystemException expectedFileSystemException(FileSystemExceptionType::MalformedFile,
      filePathLineNumberLineText.filePath, filePathLineNumberLineText.lineNumber, exceptionMessage);
   const string expectedExceptionMessage = expectedFileSystemException.what();
   THROWS_EXCEPTION(_cloudundancyIniFile.ParseFileCopyInstructionLine(filePathLineNumberLineText),
      FileSystemException, expectedExceptionMessage);
}

TEST1X1(ParseFileCopyInstructionLine_LineContainsOneSpaceArrowSpace_ReturnsExpectedFileCopyInstruction,
   const string& middleArrowPart,
   " -> ",
   "  ->  ",
   " \t -> \t ")
{
   _callerMock_ThrowIfSourceFileOrFolderDoesNotExist->ConstCallMock.Expect();
   FilePathLineNumberLineText filePathLineNumberLineText;
   filePathLineNumberLineText.filePath = ZenUnit::RandomRelativeFilePath();
   filePathLineNumberLineText.lineNumber = ZenUnit::Random<size_t>();
   const string sourceFilePath = ZenUnit::Random<string>();
   const string relativeDestinationFolderPath = ZenUnit::Random<string>();
   filePathLineNumberLineText.lineText = sourceFilePath + middleArrowPart + relativeDestinationFolderPath;
   //
   const AbsoluteFileOrFolderPathToRelativeFolderPath cloudundancyIniCopyInstruction =
      _cloudundancyIniFile.ParseFileCopyInstructionLine(filePathLineNumberLineText);
   //
   AbsoluteFileOrFolderPathToRelativeFolderPath expectedFileCopyInstruction;
   expectedFileCopyInstruction.absoluteSourceFileOrFolderPath = sourceFilePath;
   expectedFileCopyInstruction.relativeDestinationFolderPath = relativeDestinationFolderPath;
   METALMOCK(_callerMock_ThrowIfSourceFileOrFolderDoesNotExist->ConstCallMock.CalledOnceWith(
      &_cloudundancyIniFile, &CloudundancyIniFileReader::ThrowIfSourceFileOrFolderDoesNotExist,
      cloudundancyIniCopyInstruction, filePathLineNumberLineText));
   ARE_EQUAL(expectedFileCopyInstruction, cloudundancyIniCopyInstruction);
}

TEST(ThrowIfSourceFileOrFolderDoesNotExist_SourceFileOrFolderPathExists_DoesNotThrowException)
{
   _fileSystemMock->FileOrFolderExistsMock.Return(true);
   const AbsoluteFileOrFolderPathToRelativeFolderPath cloudundancyIniCopyInstruction =
      ZenUnit::Random<AbsoluteFileOrFolderPathToRelativeFolderPath>();
   const FilePathLineNumberLineText filePathLineNumberLineText = ZenUnit::Random<FilePathLineNumberLineText>();
   //
   _cloudundancyIniFile.ThrowIfSourceFileOrFolderDoesNotExist(cloudundancyIniCopyInstruction, filePathLineNumberLineText);
   //
   METALMOCK(_fileSystemMock->FileOrFolderExistsMock.CalledOnceWith(cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath));
}

TEST(ThrowIfSourceFileOrFolderDoesNotExist_SourceFileOrFolderPathDoesNotExist_ThrowsFileSystemException)
{
   _fileSystemMock->FileOrFolderExistsMock.Return(false);

   const AbsoluteFileOrFolderPathToRelativeFolderPath cloudundancyIniCopyInstruction =
      ZenUnit::Random<AbsoluteFileOrFolderPathToRelativeFolderPath>();

   FileSystemException expectedFileSystemException(FileSystemExceptionType::FileOrFolderDoesNotExist,
      cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath);
   const string expectedExceptionMessage = expectedFileSystemException.what();

   const FilePathLineNumberLineText filePathLineNumberLineText = ZenUnit::Random<FilePathLineNumberLineText>();
   //
   THROWS_EXCEPTION(_cloudundancyIniFile.ThrowIfSourceFileOrFolderDoesNotExist(cloudundancyIniCopyInstruction, filePathLineNumberLineText),
      FileSystemException, expectedExceptionMessage);
   //
   METALMOCK(_fileSystemMock->FileOrFolderExistsMock.CalledOnceWith(cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath));
}

RUN_TESTS(CloudundancyIniFileReaderTests)