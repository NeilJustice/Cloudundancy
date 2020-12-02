#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/BackupFilesAndFoldersTo7zFileSubProgram.h"
#include "libCloudundancy/Components/SubPrograms/BackupFilesAndFoldersSubProgram.h"
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgramFactory.h"
#include "libCloudundancy/Components/SubPrograms/ExampleLinuxIniFileSubProgram.h"
#include "libCloudundancy/Components/SubPrograms/ExampleWindowsIniFileSubProgram.h"

shared_ptr<CloudundancySubProgram> CloudundancySubProgramFactory::NewCloudundancySubProgram(ProgramMode programMode) const
{
   switch (programMode)
   {
   case ProgramMode::BackupFilesAndFolders:
   {
      return make_shared<BackupFilesAndFoldersSubProgram>();
   }
   case ProgramMode::BackupFilesAndFoldersTo7zFile:
   {
      return make_shared<BackupFilesAndFoldersTo7zFileSubProgram>();
   }
   case ProgramMode::PrintExampleLinuxIniFile:
   {
      return make_shared<ExampleLinuxIniFileSubProgram>();
   }
   case ProgramMode::PrintExampleWindowsIniFile:
   {
      return make_shared<ExampleWindowsIniFileSubProgram>();
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
