#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyFileCopier.h"
#include "libCloudundancy/Components/SubPrograms/BackupFilesToMultipleFoldersSubProgram.h"

BackupFilesToMultipleFoldersSubProgram::BackupFilesToMultipleFoldersSubProgram()
   : _cloudundancyFileCopier(make_unique<CloudundancyFileCopier>())
{
}

BackupFilesToMultipleFoldersSubProgram::~BackupFilesToMultipleFoldersSubProgram()
{
}

int BackupFilesToMultipleFoldersSubProgram::Run(const CloudundancyArgs& args)
{
   _cloudundancyFileCopier->CopyFilesAndFoldersToMultipleDestinationFolders(
      args.iniFilePath, args.deleteDestinationFoldersFirst);
   _console->WriteLine("\n[Cloudundancy] OverallBackupResult: Successfully copied all [SourceFilesAndFolders] to all [DestinationFolders]");
   return 0;
}
