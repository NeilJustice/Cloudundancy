#include "pch.h"
#include "libCloudundancy/Components/FileSystem/FileSystem.h"
#include "libCloudundancy/Components/FunctionCallers/Member/NonVoidOneArgMemberFunctionCaller.h"
#include "libCloudundancy/Components/FunctionCallers/Member/VoidThreeArgMemberFunctionCaller.h"
#include "libCloudundancy/Components/FunctionCallers/Member/VoidTwoArgMemberFunctionCaller.h"
#include "libCloudundancy/Components/IniFile/CloudundancyIniFileReader.h"
#include "libCloudundancy/Components/IniFile/CloudundancyIniValidator.h"

CloudundancyIniFileReader::CloudundancyIniFileReader() noexcept
   // Function Callers
   : _caller_ParseFileCopyInstructionLine(make_unique<NonVoidOneArgMemberFunctionCallerType>())
   , _caller_ThrowIfSourceFileOrFolderDoesNotExist(make_unique<VoidTwoArgMemberFunctionCallerType>())
   // Constant Components
   , _cloudundancyIniValidator(make_unique<CloudundancyIniValidator>())
   , _fileSystem(make_unique<FileSystem>())
{
}

CloudundancyIniFileReader::~CloudundancyIniFileReader()
{
}

CloudundancyIni CloudundancyIniFileReader::ReadIniFile(const fs::path& cloudundancyIniPath) const
{
   vector<string> iniFileLines = _fileSystem->ReadAsciiFileLinesWhichMustBeNonEmpty(cloudundancyIniPath);
   bool inDestinationFoldersSection = false;
   bool inSourceFilesAndFoldersToCopySection = false;
   bool inFileSubpathsToNotCopySection = false;
   CloudundancyIni cloudundancyIni;
   const size_t numberOfIniFileLines = iniFileLines.size();
   for (size_t lineNumber = 1; lineNumber <= numberOfIniFileLines; ++lineNumber)
   {
      const string iniFileLine = String::TrimWhitespace(iniFileLines[lineNumber - 1]);
      if (iniFileLine.empty() || String::StartsWith(iniFileLine, "#"))
      {
         continue;
      }
      if (iniFileLine == "[DestinationFolders]")
      {
         inDestinationFoldersSection = true;
         inSourceFilesAndFoldersToCopySection = false;
         inFileSubpathsToNotCopySection = false;
         continue;
      }
      if (iniFileLine == "[SourceFilesAndFolders]")
      {
         inDestinationFoldersSection = false;
         inSourceFilesAndFoldersToCopySection = true;
         inFileSubpathsToNotCopySection = false;
         continue;
      }
      if (iniFileLine == "[FileSubpathsToNotCopy]")
      {
         inDestinationFoldersSection = false;
         inSourceFilesAndFoldersToCopySection = false;
         inFileSubpathsToNotCopySection = true;
         continue;
      }
      if (inDestinationFoldersSection)
      {
         cloudundancyIni.destinationFolderPaths.emplace_back(iniFileLine);
      }
      else if (inSourceFilesAndFoldersToCopySection)
      {
         const FilePathLineNumberLineText fileCopyInstructionLine(cloudundancyIniPath, lineNumber, iniFileLine);
         const AbsoluteFileOrFolderPathToRelativeFolderPath cloudundancyIniCopyInstruction =
            _caller_ParseFileCopyInstructionLine->CallConstMemberFunction(
               &CloudundancyIniFileReader::ParseFileCopyInstructionLine, this, fileCopyInstructionLine);
         cloudundancyIni.absoluteFileOrFolderPathAndRelativeFolderPaths.push_back(cloudundancyIniCopyInstruction);
      }
      else
      {
         release_assert(inFileSubpathsToNotCopySection);
         cloudundancyIni.fileSubpathsToNotCopy.push_back(iniFileLine);
      }
   }
   _cloudundancyIniValidator->ValidateCloudundancyIni(cloudundancyIni, cloudundancyIniPath);
   return cloudundancyIni;
}

AbsoluteFileOrFolderPathToRelativeFolderPath CloudundancyIniFileReader::ParseFileCopyInstructionLine(
   const FilePathLineNumberLineText& fileCopyInstructionLine) const
{
   const string pipeReplacedLine = String::RegexReplace(fileCopyInstructionLine.lineText, R"(\s+->\s+)", "|");
   const vector<string> pipeSplitLine = String::Split(pipeReplacedLine, '|');
   if (pipeSplitLine.size() != 2)
   {
      const string exceptionMessage = String::Concat("Cloudundancy .ini file line does not contain required substring \" -> \"");
      throw FileSystemException(FileSystemExceptionType::MalformedFile,
         fileCopyInstructionLine.filePath, fileCopyInstructionLine.lineNumber, exceptionMessage);
   }
   AbsoluteFileOrFolderPathToRelativeFolderPath cloudundancyIniCopyInstruction;
   cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath = pipeSplitLine[0];
   cloudundancyIniCopyInstruction.relativeDestinationFolderPath = pipeSplitLine[1];
   _caller_ThrowIfSourceFileOrFolderDoesNotExist->ConstCall(
      this, &CloudundancyIniFileReader::ThrowIfSourceFileOrFolderDoesNotExist, cloudundancyIniCopyInstruction, fileCopyInstructionLine);
   return cloudundancyIniCopyInstruction;
}

void CloudundancyIniFileReader::ThrowIfSourceFileOrFolderDoesNotExist(
   const AbsoluteFileOrFolderPathToRelativeFolderPath& cloudundancyIniCopyInstruction,
   const FilePathLineNumberLineText& /*filePathLineNumberLineText*/) const
{
   bool sourceFileOrFolderExists = _fileSystem->FileOrFolderExists(cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath);
   if (!sourceFileOrFolderExists)
   {
      throw FileSystemException(FileSystemExceptionType::FileOrFolderDoesNotExist,
         cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath);
   }
}