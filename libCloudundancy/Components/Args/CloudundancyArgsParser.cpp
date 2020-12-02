#include "pch.h"
#include "libCloudundancy/Components/Args/ProgramModeDeterminer.h"
#include "libCloudundancy/Components/Args/CloudundancyArgsParser.h"

CloudundancyArgsParser::CloudundancyArgsParser()
   // Constant Components
   : _console(make_unique<Console>())
   , _docoptParser(make_unique<DocoptParser>())
   , _fileSystem(make_unique<FileSystem>())
   , _processRunner(make_unique<ProcessRunner>())
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
   const bool isBackupFilesToMultipleFoldersMode = _docoptParser->GetRequiredBool(docoptArgs, "backup-files-to-multiple-folders");
   const bool isBackupFilesAndFoldersTo7zFileMode = _docoptParser->GetRequiredBool(docoptArgs, "backup-files-and-folders-to-7z-file");
   cloudundancyArgs.programMode = _programModeDeterminer->DetermineProgramMode(
      isPrintExampleLinuxIniFileMode,
      isPrintExampleWindowsIniFileMode,
      isBackupFilesToMultipleFoldersMode,
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

   if (isBackupFilesAndFoldersTo7zFileMode)
   {
      _console->WriteLine("[Cloudundancy] Running 7z to confirm 7z is present on the PATH");
      _processRunner->FailFastRun("7z", "", false);
      _console->WriteLine("[Cloudundancy] 7z ran and exited with code 0 and is therefore confirmed to be present on the PATH\n");
   }

   return cloudundancyArgs;
}
