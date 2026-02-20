#include "pch.h"
#include "libCloudundancy/Components/Args/SevenZipArgsParser.h"

SevenZipArgsParser::SevenZipArgsParser()
{
}

SevenZipArgsParser::~SevenZipArgsParser()
{
}

CloudundancyArgs SevenZipArgsParser::ParseDocoptArgs(const map<string, docopt::value>& /*docoptArgs*/) const
{
   CloudundancyArgs cloudundancyArgs;

   //cloudundancyArgs.sevenZipModeIniFilePath = _docoptParser->GetProgramModeSpecificRequiredString(docoptArgs,
   //   static_cast<int>(cloudundancyArgs.programMode),
   //   static_cast<int>(ProgramMode::SevenZip),
   //   "--ini-file-to-copy-files-to-7zip-staging-folder");

   //cloudundancyArgs.sevenZipStagingFolderPath = _docoptParser->GetProgramModeSpecificRequiredString(docoptArgs,
   //   static_cast<int>(cloudundancyArgs.programMode),
   //   static_cast<int>(ProgramMode::SevenZip),
   //   "--7zip-staging-folder");

   //cloudundancyArgs.sevenZipFileCopyingIniFilePath = _docoptParser->GetProgramModeSpecificRequiredString(docoptArgs,
   //   static_cast<int>(cloudundancyArgs.programMode),
   //   static_cast<int>(ProgramMode::SevenZip),
   //   "--ini-file-to-copy-7zip-file-from-staging-folder-to-multiple-folders");

   //_fileSystem->ThrowIfFilePathIsNotEmptyPathAndFileDoesNotExist(cloudundancyArgs.sevenZipModeIniFilePath);
   //_fileSystem->ThrowIfFilePathIsNotEmptyPathAndFileDoesNotExist(cloudundancyArgs.sevenZipFileCopyingIniFilePath);
   //if (is7ZipMode)
   //{
   //   _console->WriteLine("[Cloudundancy] Running program 7z to confirm 7z is present on the PATH");
   //   _processRunner->FailFastRun("7z", "", false);
   //   _console->WriteLine("[Cloudundancy] 7z ran and exited with code 0 and is therefore confirmed to be present on the PATH\n");
   //}

   return cloudundancyArgs;
}
