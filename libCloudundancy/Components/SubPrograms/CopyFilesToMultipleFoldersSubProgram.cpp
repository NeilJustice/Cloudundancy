#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyFileCopier.h"
#include "libCloudundancy/Components/SubPrograms/CopyFilesToMultipleFoldersSubProgram.h"

CopyFileFastsToMultipleFoldersSubProgram::CopyFileFastsToMultipleFoldersSubProgram()
   // Constant Components
   : _cloudundancyFileCopier(make_unique<CloudundancyFileCopier>())
{
}

CopyFileFastsToMultipleFoldersSubProgram::~CopyFileFastsToMultipleFoldersSubProgram()
{
}

int CopyFileFastsToMultipleFoldersSubProgram::Run(const CloudundancyArgs& args)
{
   _cloudundancyFileCopier->CopyFileFastsAndFoldersToMultipleDestinationFolders(args.iniFilePath, args.deleteDestinationFoldersFirst);
   _console->WriteLineColor("\n[Cloudundancy] OverallBackupResult: Successfully copied all [SourceFilesAndFolders] to all [DestinationFolders]", Color::Green);
   return 0;
}
