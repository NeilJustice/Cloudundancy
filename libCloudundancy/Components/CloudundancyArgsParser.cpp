#include "pch.h"
#include "libCloudundancy/Components/CloudundancyArgsParser.h"
#include "libCloudundancy/Components/Docopt/DocoptParser.h"
#include "libCloudundancy/Components/FileSystem/FileSystem.h"

CloudundancyArgsParser::CloudundancyArgsParser()
   // Constant Components
   : _docoptParser(make_unique<DocoptParser>())
   , _fileSystem(make_unique<FileSystem>())
   // Function Callers
   , _call_GetProgramMode(CloudundancyArgsParser::GetProgramMode)
{
}

CloudundancyArgsParser::~CloudundancyArgsParser()
{
}

CloudundancyArgs CloudundancyArgsParser::ParseStringArgs(const vector<string>& stringArgs) const
{
   const map<string, docopt::Value> docoptArgs = _docoptParser->ParseArgs(CloudundancyArgs::CommandLineUsage, stringArgs);
   CloudundancyArgs cloudundancyArgs;
   const bool isBackupFilesAndFoldersMode = _docoptParser->GetRequiredBool(docoptArgs, "backup-files-and-folders");
   const bool is7ZipBackupMode = _docoptParser->GetRequiredBool(docoptArgs, "backup-files-and-folders-to-7z-file");
   cloudundancyArgs.programMode = _call_GetProgramMode(isBackupFilesAndFoldersMode, is7ZipBackupMode);
   cloudundancyArgs.iniFilePath = _docoptParser->GetRequiredString(docoptArgs, "--ini-file");
   cloudundancyArgs.sevenZipIniFilePath = _docoptParser->GetProgramModeSpecificRequiredString(docoptArgs,
      static_cast<int>(cloudundancyArgs.programMode),
      static_cast<int>(ProgramMode::BackupFilesAndFoldersWith7Zip), "--7z-ini-file");
   cloudundancyArgs.backupStagingFolderPath = _docoptParser->GetProgramModeSpecificRequiredString(docoptArgs,
      static_cast<int>(cloudundancyArgs.programMode),
      static_cast<int>(ProgramMode::BackupFilesAndFoldersWith7Zip), "--backup-staging-folder");
   _fileSystem->ThrowIfFilePathIsNotEmptyAndDoesNotExist(cloudundancyArgs.iniFilePath);
   _fileSystem->ThrowIfFilePathIsNotEmptyAndDoesNotExist(cloudundancyArgs.sevenZipIniFilePath);
   return cloudundancyArgs;
}

ProgramMode CloudundancyArgsParser::GetProgramMode(bool isBackupFilesAndFoldersMode, bool is7ZipBackupMode)
{
   if (isBackupFilesAndFoldersMode)
   {
      release_assert(!is7ZipBackupMode);
      return ProgramMode::BackupFilesAndFolders;
   }
   if (is7ZipBackupMode)
   {
      release_assert(!isBackupFilesAndFoldersMode);
      return ProgramMode::BackupFilesAndFoldersWith7Zip;
   }
   throw invalid_argument("CloudundancyArgsParser::GetProgramMode(): isBackupFilesAndFoldersMode and is7ZipBackupMode are unexpectedly both false");
}
