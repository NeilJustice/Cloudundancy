#include "pch.h"
#include "libCloudundancy/Components/Args/ProgramModeDeterminer.h"
#include "libCloudundancy/Components/Args/CloudundancyArgsParser.h"

CloudundancyArgsParser::CloudundancyArgsParser()
   // Constant Components
   : _docoptParser(make_unique<DocoptParser>())
   , _fileSystem(make_unique<FileSystem>())
   , _programModeDeterminer(make_unique<ProgramModeDeterminer>())
{
}

CloudundancyArgsParser::~CloudundancyArgsParser()
{
}

CloudundancyArgs CloudundancyArgsParser::ParseStringArgs(const vector<string>& stringArgs) const
{
   const map<string, docopt::Value> docoptArgs = _docoptParser->ParseArgs(CloudundancyArgs::CommandLineUsage, stringArgs);
   CloudundancyArgs cloudundancyArgs;
   const bool isPrintExampleLinuxIniFileMode = _docoptParser->GetRequiredBool(docoptArgs, "print-example-linux-ini-file");
   const bool isPrintExampleWindowsIniFileMode = _docoptParser->GetRequiredBool(docoptArgs, "print-example-windows-ini-file");
   const bool isBackupFilesAndFoldersMode = _docoptParser->GetRequiredBool(docoptArgs, "backup-files-and-folders");
   const bool isBackupFilesAndFoldersTo7zFileMode = _docoptParser->GetRequiredBool(docoptArgs, "backup-files-and-folders-to-7z-file");
   cloudundancyArgs.programMode = _programModeDeterminer->DetermineProgramMode(
      isPrintExampleLinuxIniFileMode,
      isPrintExampleWindowsIniFileMode,
      isBackupFilesAndFoldersMode,
      isBackupFilesAndFoldersTo7zFileMode);

   cloudundancyArgs.iniFilePath = _docoptParser->GetRequiredString(docoptArgs, "--ini-file");

   cloudundancyArgs.sevenZipIniFilePath = _docoptParser->GetProgramModeSpecificRequiredString(docoptArgs,
      static_cast<int>(cloudundancyArgs.programMode),
      static_cast<int>(ProgramMode::BackupFilesAndFoldersTo7zFile), "--7z-ini-file");

   cloudundancyArgs.backupStagingFolderPath = _docoptParser->GetProgramModeSpecificRequiredString(docoptArgs,
      static_cast<int>(cloudundancyArgs.programMode),
      static_cast<int>(ProgramMode::BackupFilesAndFoldersTo7zFile), "--backup-staging-folder");

   _fileSystem->ThrowIfFilePathIsNotEmptyAndDoesNotExist(cloudundancyArgs.iniFilePath);
   _fileSystem->ThrowIfFilePathIsNotEmptyAndDoesNotExist(cloudundancyArgs.sevenZipIniFilePath);
   return cloudundancyArgs;
}
