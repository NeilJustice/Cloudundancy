#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/CopyFilesToMultipleFoldersSubProgram.h"
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgramFactory.h"
#include "libCloudundancy/Components/SubPrograms/SevenZipSubProgram.h"
#include "libCloudundancy/Components/SubPrograms/PrintExampleLinuxIniFileSubProgram.h"
#include "libCloudundancy/Components/SubPrograms/PrintExampleWindowsIniFileSubProgram.h"

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
   case ProgramMode::PrintExampleLinuxIniFile:
   {
      return make_shared<PrintExampleLinuxIniFileSubProgram>();
   }
   case ProgramMode::PrintExampleWindowsIniFile:
   {
      return make_shared<PrintExampleWindowsIniFileSubProgram>();
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
