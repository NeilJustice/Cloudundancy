#include "pch.h"
#include "libCloudundancy/Components/Args/CloudundancyArgsParser.h"
#include "libCloudundancy/Components/Args/ProgramModeDeterminer.h"

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
   const bool isCopyFilesToMultipleFoldersMode = _docoptParser->GetRequiredBool(docoptArgs, "copy-files-to-multiple-folders");
   const bool is7ZipMode = _docoptParser->GetRequiredBool(docoptArgs, "7zip-files-then-copy-the-7zip-file-to-multiple-folders");
   const bool isExampleLinuxIniFileMode = _docoptParser->GetRequiredBool(docoptArgs, "example-linux-ini-file");
   const bool isExampleWindowsIniFileMode = _docoptParser->GetRequiredBool(docoptArgs, "example-windows-ini-file");
   cloudundancyArgs.programMode = _programModeDeterminer->DetermineProgramMode(
      isCopyFilesToMultipleFoldersMode,
      is7ZipMode,
      isExampleLinuxIniFileMode,
      isExampleWindowsIniFileMode);

   cloudundancyArgs.iniFilePath = _docoptParser->GetRequiredString(docoptArgs, "--ini-file");

   cloudundancyArgs.deleteDestinationFoldersFirst = _docoptParser->GetOptionalBool(
      docoptArgs, "--delete-destination-folders-first");

   cloudundancyArgs.sevenZipModeIniFilePath = _docoptParser->GetProgramModeSpecificRequiredString(docoptArgs,
      static_cast<int>(cloudundancyArgs.programMode),
      static_cast<int>(ProgramMode::SevenZip),
      "--ini-file-to-copy-files-to-7zip-staging-folder");

   cloudundancyArgs.sevenZipStagingFolderPath = _docoptParser->GetProgramModeSpecificRequiredString(docoptArgs,
      static_cast<int>(cloudundancyArgs.programMode),
      static_cast<int>(ProgramMode::SevenZip),
      "--7zip-staging-folder");

   cloudundancyArgs.sevenZipFileCopyingIniFilePath = _docoptParser->GetProgramModeSpecificRequiredString(docoptArgs,
      static_cast<int>(cloudundancyArgs.programMode),
      static_cast<int>(ProgramMode::SevenZip),
      "--ini-file-to-copy-7zip-file-from-staging-folder-to-multiple-folders");

   _fileSystem->ThrowIfFilePathIsNotEmptyAndDoesNotExist(cloudundancyArgs.iniFilePath);
   _fileSystem->ThrowIfFilePathIsNotEmptyAndDoesNotExist(cloudundancyArgs.sevenZipModeIniFilePath);
   _fileSystem->ThrowIfFilePathIsNotEmptyAndDoesNotExist(cloudundancyArgs.sevenZipFileCopyingIniFilePath);
   if (is7ZipMode)
   {
      _console->WriteLine("[Cloudundancy] Running program 7z to confirm 7z is present on the PATH");
      _processRunner->FailFastRun("7z", "", false);
      _console->WriteLine("[Cloudundancy] 7z ran and exited with code 0 and is therefore confirmed to be present on the PATH\n");
   }
   return cloudundancyArgs;
}
