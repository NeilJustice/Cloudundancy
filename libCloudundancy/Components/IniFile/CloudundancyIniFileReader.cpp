#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyLogFileWriter.h"
#include "libCloudundancy/Components/IniFile/CloudundancyIniFileReader.h"
#include "libCloudundancy/Components/IniFile/CloudundancyIniValidator.h"

CloudundancyIniFileReader::CloudundancyIniFileReader() noexcept
   // Function Callers
   : _caller_ParseFileCopyInstructionLine(make_unique<NonVoidOneArgMemberFunctionCallerType>())
   , _caller_ThrowIfSourceFileOrFolderDoesNotExist(make_unique<VoidOneArgMemberFunctionCallerType>())
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
   CloudundancyIni cloudundancyIni;
   cloudundancyIni.iniFileLines = _fileSystem->ReadFileLinesWhichMustBeNonEmpty(cloudundancyIniPath);
   bool inDestinationFoldersSection = false;
   bool inSourceFilesAndFoldersToCopySection = false;
   bool inFileSubpathsToNotCopySection = false;
   const size_t numberOfIniFileLines = cloudundancyIni.iniFileLines.size();
   for (size_t lineNumber = 1; lineNumber <= numberOfIniFileLines; ++lineNumber)
   {
      const string& untrimmedIniFileLine = cloudundancyIni.iniFileLines[lineNumber - 1];
      const string iniFileLine = String::TrimWhitespace(untrimmedIniFileLine);
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
         CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction =
            _caller_ParseFileCopyInstructionLine->CallConstMemberFunction(
               &CloudundancyIniFileReader::ParseFileCopyInstructionLine, this, fileCopyInstructionLine);
         cloudundancyIni.cloudundancyIniCopyInstructions.emplace_back(std::move(cloudundancyIniCopyInstruction));
      }
      else
      {
         release_assert(inFileSubpathsToNotCopySection);
         cloudundancyIni.fileSubpathsToNotCopy.emplace_back(iniFileLine);
      }
   }
   _cloudundancyIniValidator->ThrowIfZeroDestinationFolderPaths(cloudundancyIni, cloudundancyIniPath);
   return cloudundancyIni;
}

CloudundancyIniCopyInstruction CloudundancyIniFileReader::ParseFileCopyInstructionLine(
   const FilePathLineNumberLineText& fileCopyInstructionLine) const
{
   const string pipeReplacedLine = String::RegexReplace(fileCopyInstructionLine.lineText, R"(\s+->\s+)", "|");
   const vector<string> pipeSplitLine = String::Split(pipeReplacedLine, '|');
   if (pipeSplitLine.size() != 2)
   {
      const string exceptionMessage = "Cloudundancy .ini file line does not contain required substring \" -> \"";
      throw FileSystemException(FileSystemExceptionType::MalformedFile,
         fileCopyInstructionLine.filePath, fileCopyInstructionLine.lineNumber, exceptionMessage);
   }
   CloudundancyIniCopyInstruction cloudundancyIniCopyInstruction;
   cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath = pipeSplitLine[0];
   cloudundancyIniCopyInstruction.relativeDestinationFolderPath = pipeSplitLine[1];
   _caller_ThrowIfSourceFileOrFolderDoesNotExist->CallConstMemberFunction(
      &CloudundancyIniFileReader::ThrowIfSourceFileOrFolderDoesNotExist, this, cloudundancyIniCopyInstruction);
   return cloudundancyIniCopyInstruction;
}

void CloudundancyIniFileReader::ThrowIfSourceFileOrFolderDoesNotExist(
   const CloudundancyIniCopyInstruction& cloudundancyIniCopyInstruction) const
{
   bool sourceFileOrFolderExists = _fileSystem->FileOrFolderExists(cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath);
   if (!sourceFileOrFolderExists)
   {
      throw FileSystemException(FileSystemExceptionType::FileOrFolderDoesNotExist,
         cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath);
   }
}
