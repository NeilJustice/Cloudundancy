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

int CopyFileToFilesToMultipleFoldersSubProgram::Run()
{
   _cloudundancyFileCopier->CopyFilteredFilesAndFoldersToDestinationFolders(
      p_args.iniInputFilePath, p_args.deleteDestinationFoldersFirst);

   p_console->WriteLineColor(
      "\n[Cloudundancy] OverallBackupResult: Successfully copied all [SourceFilesAndFolders] to all [DestinationFolders]",
      Utils::Color::Green);
   return 0;
}
