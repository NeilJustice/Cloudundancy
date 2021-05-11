#include "pch.h"
#include "libCloudundancy/Components/IniFile/CloudundancyIniFileReader.h"
#include "libCloudundancyTests/Components/IniFile/MetalMock/CloudundancyIniValidatorMock.h"

TESTS(CloudundancyIniFileReaderTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(ReadIniFile_ParsesCloudundancyIniFile_ValidatesCloudundancyIni_ReturnsCloudundancyIni)
FACTS(ParseFileCopyInstructionLine_LineDoesNotContainSpaceArrowSpace_OrLineContainsMoreThanOneSpaceArrowSpace_ThrowsFileSystemException)
FACTS(ParseFileCopyInstructionLine_LineContainsOneSpaceArrowSpace_ReturnsExpectedFileCopyInstruction)
AFACT(ThrowIfSourceFileOrFolderDoesNotExist_SourceFileOrFolderPathExists_DoesNotThrowException)
AFACT(ThrowIfSourceFileOrFolderDoesNotExist_SourceFileOrFolderPathDoesNotExist_ThrowsFileSystemException)
EVIDENCE

CloudundancyIniFileReader _cloudundancyIniFile;

// Function Callers
using NonVoidOneArgMemberFunctionCallerMockMockType = NonVoidOneArgMemberFunctionCallerMock<
   CloudundancyIniCopyInstruction, CloudundancyIniFileReader, const FilePathLineNumberLineText&>;
NonVoidOneArgMemberFunctionCallerMockMockType* _callerMock_ParseFileCopyInstructionLine = nullptr;

using VoidOneArgMemberFunctionCallerMockType = VoidOneArgMemberFunctionCallerMock<
   CloudundancyIniFileReader, const CloudundancyIniCopyInstruction&>;
VoidOneArgMemberFunctionCallerMockType* _callerMock_ThrowIfSourceFileOrFolderDoesNotExist = nullptr;

// Constant Components
CloudundancyIniValidatorMock* _cloudundancyIniValidatorMock = nullptr;
FileSystemMock* _fileSystemMock = nullptr;

STARTUP
{
   // Function Callers
   _cloudundancyIniFile._caller_ParseFileCopyInstructionLine.reset(
      _callerMock_ParseFileCopyInstructionLine = new NonVoidOneArgMemberFunctionCallerMockMockType);
   _cloudundancyIniFile._caller_ThrowIfSourceFileOrFolderDoesNotExist.reset(
      _callerMock_ThrowIfSourceFileOrFolderDoesNotExist = new VoidOneArgMemberFunctionCallerMockType);
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

TEST(ReadIniFile_ParsesCloudundancyIniFile_ValidatesCloudundancyIni_ReturnsCloudundancyIni)
{
   const string folderPathA = ZenUnit::Random<string>();
   const string folderPathC = ZenUnit::Random<string>();
   const string filePathA = ZenUnit::Random<string>();
   const string filePathB = ZenUnit::Random<string>();
   const string filePathIgnoreSubstring1 = ZenUnit::Random<string>();
   const string filePathIgnoreSubstring2 = ZenUnit::Random<string>();
   const vector<string> iniFileLines =
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
   _fileSystemMock->ReadFileLinesWhichMustBeNonEmptyMock.Return(iniFileLines);

   const CloudundancyIniCopyInstruction fileCopyInstruction1
      = ZenUnit::Random<CloudundancyIniCopyInstruction>();
   const CloudundancyIniCopyInstruction fileCopyInstruction2
      = ZenUnit::Random<CloudundancyIniCopyInstruction>();
   _callerMock_ParseFileCopyInstructionLine->CallConstMemberFunctionMock.ReturnValues(fileCopyInstruction1, fileCopyInstruction2);

   _cloudundancyIniValidatorMock->ThrowIfZeroDestinationFolderPathsMock.Expect();

   const fs::path cloudundancyIniPath = ZenUnit::Random<string>();
   //
   const CloudundancyIni cloudundancyIni = _cloudundancyIniFile.ReadIniFile(cloudundancyIniPath);
   //
   METALMOCK(_fileSystemMock->ReadFileLinesWhichMustBeNonEmptyMock.CalledOnceWith(cloudundancyIniPath));
   CloudundancyIni expectedCloudundancyIni;
   expectedCloudundancyIni.iniFileLines = iniFileLines;
   expectedCloudundancyIni.destinationFolderPaths =
   {
      fs::path(folderPathA),
      fs::path(folderPathC)
   };
   expectedCloudundancyIni.cloudundancyIniCopyInstructions =
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
   METALMOCK(_cloudundancyIniValidatorMock->ThrowIfZeroDestinationFolderPathsMock.CalledOnceWith(cloudundancyIni, cloudundancyIniPath));
   ARE_EQUAL(expectedCloudundancyIni, cloudundancyIni);
}

TEST1X1(ParseFileCopyInstructionLine_LineDoesNotContainSpaceArrowSpace_OrLineContainsMoreThanOneSpaceArrowSpace_ThrowsFileSystemException,
   string_view lineText,
   "Line",
   "Source->DestSuffix",
   "Source -> DestSuffix -> DestSuffix")
{
   FilePathLineNumberLineText filePathLineNumberLineText;
   filePathLineNumberLineText.filePath = ZenUnit::Random<fs::path>();
   filePathLineNumberLineText.lineNumber = ZenUnit::Random<size_t>();
   filePathLineNumberLineText.lineText = lineText;
   //
   const string exceptionMessage = "Cloudundancy .ini file line does not contain required substring \" -> \"";
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
   _callerMock_ThrowIfSourceFileOrFolderDoesNotExist->CallConstMemberFunctionMock.Expect();
   FilePathLineNumberLineText filePathLineNumberLineText;
   filePathLineNumberLineText.filePath = ZenUnit::Random<fs::path>();
   filePathLineNumberLineText.lineNumber = ZenUnit::Random<size_t>();
   const string sourceFilePath = ZenUnit::Random<string>();
   const string relativeDestinationFolderPath = ZenUnit::Random<string>();
   filePathLineNumberLineText.lineText = sourceFilePath + middleArrowPart + relativeDestinationFolderPath;
   //
   const CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction =
      _cloudundancyIniFile.ParseFileCopyInstructionLine(filePathLineNumberLineText);
   //
   CloudundancyIniCopyInstruction expectedFileCopyInstruction;
   expectedFileCopyInstruction.absoluteSourceFileOrFolderPath = sourceFilePath;
   expectedFileCopyInstruction.relativeDestinationFolderPath = relativeDestinationFolderPath;
   METALMOCK(_callerMock_ThrowIfSourceFileOrFolderDoesNotExist->CallConstMemberFunctionMock.CalledOnceWith(
      &CloudundancyIniFileReader::ThrowIfSourceFileOrFolderDoesNotExist, &_cloudundancyIniFile, expectedFileCopyInstruction));
   ARE_EQUAL(expectedFileCopyInstruction, cloudundancyIniCopyInstruction);
}

TEST(ThrowIfSourceFileOrFolderDoesNotExist_SourceFileOrFolderPathExists_DoesNotThrowException)
{
   _fileSystemMock->FileOrFolderExistsMock.Return(true);
   const CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction =
      ZenUnit::Random<CloudundancyIniCopyInstruction>();
   const FilePathLineNumberLineText filePathLineNumberLineText = ZenUnit::Random<FilePathLineNumberLineText>();
   //
   _cloudundancyIniFile.ThrowIfSourceFileOrFolderDoesNotExist(cloudundancyIniCopyInstruction);
   //
   METALMOCK(_fileSystemMock->FileOrFolderExistsMock.CalledOnceWith(cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath));
}

TEST(ThrowIfSourceFileOrFolderDoesNotExist_SourceFileOrFolderPathDoesNotExist_ThrowsFileSystemException)
{
   _fileSystemMock->FileOrFolderExistsMock.Return(false);

   const CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction =
      ZenUnit::Random<CloudundancyIniCopyInstruction>();

   FileSystemException expectedFileSystemException(FileSystemExceptionType::FileOrFolderDoesNotExist,
      cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath);
   const string expectedExceptionMessage = expectedFileSystemException.what();
   //
   THROWS_EXCEPTION(_cloudundancyIniFile.ThrowIfSourceFileOrFolderDoesNotExist(cloudundancyIniCopyInstruction),
      FileSystemException, expectedExceptionMessage);
   //
   METALMOCK(_fileSystemMock->FileOrFolderExistsMock.CalledOnceWith(cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath));
}

RUN_TESTS(CloudundancyIniFileReaderTests)
