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
   _cloudundancyFileCopier->CopyFilesAndFoldersToMultipleDestinationFolders(args.iniFilePath);
   _console->WriteLine("[Cloudundancy] OverallBackupResult: Successfully backed up all files and folders to all destination folders");
   return 0;
}
