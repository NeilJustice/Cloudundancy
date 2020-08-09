#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/BackupCodeSubProgram.h"
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgramFactory.h"
#include "libCloudundancy/Components/SubPrograms/BackupFilesAndFoldersSubProgram.h"
#include "libCloudundancy/Enums/ProgramMode.h"

shared_ptr<CloudundancySubProgram> CloudundancySubProgramFactory::NewCloudundancySubProgram(ProgramMode programMode) const
{
   switch (programMode)
   {
   case ProgramMode::BackupFilesAndFolders:
   {
      return make_shared<BackupFilesAndFoldersSubProgram>();
   }
   case ProgramMode::BackupFilesAndFoldersWith7Zip:
   {
      return make_shared<BackupCodeSubProgram>();
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
