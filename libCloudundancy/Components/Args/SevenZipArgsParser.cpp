#include "pch.h"
#include "libCloudundancy/Components/Args/SevenZipArgsParser.h"
#include "libCloudundancy/Components/Console/Console.h"
#include "libCloudundancy/Components/Docopt/DocoptParser.h"
#include "libCloudundancy/Components/Process/ProcessRunner.h"

SevenZipArgsParser::SevenZipArgsParser()
   // Constant Components
   : _console(make_unique<Utils::Console>())
   , _processRunner(make_unique<Utils::ProcessRunner>())
{
}

SevenZipArgsParser::~SevenZipArgsParser()
{
}

CloudundancyArgs SevenZipArgsParser::ParseDocoptArgs(const map<string, docopt::value>& docoptArgs) const
{
   CloudundancyArgs cloudundancyArgs;
   cloudundancyArgs.programMode = ProgramMode::SevenZip;

   cloudundancyArgs.sevenZipModeIniInputFilePath = p_docoptParser->GetRequiredFilePathWhichMustExist(
      docoptArgs, "--ini-file-to-copy-files-to-7zip-staging-folder");

   cloudundancyArgs.sevenZipStagingFolderPath = p_docoptParser->GetRequiredFolderPathWhichNeedNotExist(
      docoptArgs, "--7zip-staging-folder");

   cloudundancyArgs.sevenZipFileCopyingIniInputFilePath = p_docoptParser->GetRequiredFilePathWhichMustExist(
      docoptArgs, "--ini-file-to-copy-7zip-file-from-staging-folder-to-multiple-folders");

   _console->WriteLine("[Cloudundancy] Running program 7z to confirm 7z is present on the PATH");
   _processRunner->FailFastRun("7z", "", false);
   _console->WriteLine("[Cloudundancy] 7z ran and exited with code 0 and is therefore confirmed to be present on the PATH\n");
   return cloudundancyArgs;
}
