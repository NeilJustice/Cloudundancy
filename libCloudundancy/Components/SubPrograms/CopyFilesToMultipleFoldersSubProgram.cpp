#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyFileCopier.h"
#include "libCloudundancy/Components/SubPrograms/CopyFilesToMultipleFoldersSubProgram.h"

CopyFileToFilesToMultipleFoldersSubProgram::CopyFileToFilesToMultipleFoldersSubProgram()
   // Constant Components
   : _cloudundancyFileCopier(make_unique<CloudundancyFileCopier>())
{
}

CopyFileToFilesToMultipleFoldersSubProgram::~CopyFileToFilesToMultipleFoldersSubProgram()
{
}

int CopyFileToFilesToMultipleFoldersSubProgram::Run(const CloudundancyArgs& args)
{
   _cloudundancyFileCopier->CopyFileToFilesAndFoldersToMultipleDestinationFolders(args.iniFilePath, args.deleteDestinationFoldersFirst);
   _console->WriteLineColor("\n[Cloudundancy] OverallBackupResult: Successfully copied all [SourceFilesAndFolders] to all [DestinationFolders]", Color::Green);
   return 0;
}
