#pragma once
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgram.h"
class CloudundancyFileCopier;

class BackupFilesToMultipleFoldersSubProgram : public CloudundancySubProgram
{
   friend class BackupFilesToMultipleFoldersSubProgramTests;
private:
   unique_ptr<const CloudundancyFileCopier> _cloudundancyFileCopier;
public:
   BackupFilesToMultipleFoldersSubProgram();
   virtual ~BackupFilesToMultipleFoldersSubProgram();
   virtual int Run(const CloudundancyArgs& args);
};
