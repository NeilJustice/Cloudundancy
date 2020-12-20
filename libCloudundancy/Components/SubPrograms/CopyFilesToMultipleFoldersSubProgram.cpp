#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyFileCopier.h"
#include "libCloudundancy/Components/SubPrograms/CopyFilesToMultipleFoldersSubProgram.h"

CopyFilesToMultipleFoldersSubProgram::CopyFilesToMultipleFoldersSubProgram()
   : _cloudundancyFileCopier(make_unique<CloudundancyFileCopier>())
{
}

CopyFilesToMultipleFoldersSubProgram::~CopyFilesToMultipleFoldersSubProgram()
{
}

int CopyFilesToMultipleFoldersSubProgram::Run(const CloudundancyArgs& args)
{
   _cloudundancyFileCopier->CopyFilesAndFoldersToMultipleDestinationFolders(
      args.iniFilePath, args.deleteDestinationFoldersFirst);
   _console->WriteLineColor(
      "\n[Cloudundancy] OverallBackupResult: Successfully copied all [SourceFilesAndFolders] to all [DestinationFolders]",
      Color::Green);
   return 0;
}
