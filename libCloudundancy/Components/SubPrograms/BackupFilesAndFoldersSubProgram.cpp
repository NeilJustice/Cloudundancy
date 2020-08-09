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

void BackupFilesAndFoldersSubProgram::Run(const CloudundancyArgs& args)
{
   _cloudundancyFileCopier->CopyFilesAndFoldersToMultipleFolders(args.iniFilePath);
}
