#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/CopyFilesToMultipleFoldersSubProgram.h"
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgramFactory.h"
#include "libCloudundancy/Components/SubPrograms/SevenZipSubProgram.h"
#include "libCloudundancy/Components/SubPrograms/ExampleLinuxIniFileSubProgram.h"
#include "libCloudundancy/Components/SubPrograms/ExampleWindowsIniFileSubProgram.h"

shared_ptr<CloudundancySubProgram> CloudundancySubProgramFactory::NewCloudundancySubProgram(ProgramMode programMode) const
{
   switch (programMode)
   {
   case ProgramMode::CopyFilesAndFoldersToMultipleFolders:
   {
      return make_shared<CopyFilesToMultipleFoldersSubProgram>();
   }
   case ProgramMode::SevenZip:
   {
      return make_shared<SevenZipSubProgram>();
   }
   case ProgramMode::ExampleLinuxIniFile:
   {
      return make_shared<ExampleLinuxIniFileSubProgram>();
   }
   case ProgramMode::ExampleWindowsIniFile:
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
