#include "pch.h"
#include "libCloudundancy/Components/CloudundancyFileCopier.h"
#include "libCloudundancy/Components/SubPrograms/BackupFilesAndFoldersSubProgram.h"
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"

BackupFilesAndFoldersSubProgram::BackupFilesAndFoldersSubProgram()
   : _cloudundancyFileCopier(make_unique<CloudundancyFileCopier>())
{
}

BackupFilesAndFoldersSubProgram::~BackupFilesAndFoldersSubProgram()
{
}

int BackupFilesAndFoldersSubProgram::Run(const CloudundancyArgs& args)
{
   _cloudundancyFileCopier->CopyFilesAndFoldersToMultipleFolders(args.iniFilePath);
   _console->WriteLine("[Cloudundancy] OverallBackupResult: Successfully backed up all files and folders to all destination folders.");
   return 0;
}
