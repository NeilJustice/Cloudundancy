#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/PrintExampleLinuxIniFileSubProgram.h"
#include "libCloudundancy/Components/SubPrograms/PrintExampleWindowsIniFileSubProgram.h"
#include "libCloudundancy/Components/SubPrograms/BackupFilesAndFoldersTo7zFileSubProgram.h"
#include "libCloudundancy/Components/SubPrograms/BackupFilesToMultipleFoldersSubProgram.h"
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgramFactory.h"

shared_ptr<CloudundancySubProgram> CloudundancySubProgramFactory::NewCloudundancySubProgram(ProgramMode programMode) const
{
   switch (programMode)
   {
   case ProgramMode::PrintExampleLinuxIniFile:
   {
      return make_shared<PrintExampleLinuxIniFileSubProgram>();
   }
   case ProgramMode::PrintExampleWindowsIniFile:
   {
      return make_shared<PrintExampleWindowsIniFileSubProgram>();
   }
   case ProgramMode::BackupFilesAndFolders:
   {
      return make_shared<BackupFilesToMultipleFoldersSubProgram>();
   }
   case ProgramMode::BackupFilesAndFoldersTo7zFile:
   {
      return make_shared<BackupFilesAndFoldersTo7zFileSubProgram>();
   }
   default:
   {
      throw invalid_argument("Invalid Cloudundancy program mode: " + to_string(static_cast<int>(programMode)));
   }
   }
}

CloudundancySubProgramFactory::~CloudundancySubProgramFactory()
{
}
