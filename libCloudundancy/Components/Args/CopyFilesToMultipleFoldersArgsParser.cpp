#include "pch.h"
#include "libCloudundancy/Components/Args/CopyFilesToMultipleFoldersArgsParser.h"
#include "libCloudundancy/Components/Docopt/DocoptParser.h"

CloudundancyArgs CopyFilesToMultipleFoldersArgsParser::ParseDocoptArgs(const map<string, docopt::value>& docoptArgs) const
{
   CloudundancyArgs cloudundancyArgs;
   cloudundancyArgs.programMode = ProgramMode::CopyFilesToMultipleFolders;

   cloudundancyArgs.iniInputFilePath = p_docoptParser->GetRequiredFilePathWhichMustExist(
      docoptArgs, "--ini-file");

   cloudundancyArgs.deleteDestinationFoldersFirst = p_docoptParser->GetOptionalBool(
      docoptArgs, "--delete-destination-folders-first");
   return cloudundancyArgs;
}
