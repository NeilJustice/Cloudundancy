#pragma once
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgram.h"
class CloudundancyFileCopier;

class CopyFileToFilesToMultipleFoldersSubProgram : public CloudundancySubProgram
{
   friend class CopyFileToFilesToMultipleFoldersSubProgramTests;
private:
   // Constant Components
   unique_ptr<const CloudundancyFileCopier> _cloudundancyFileCopier;
public:
   CopyFileToFilesToMultipleFoldersSubProgram();
   virtual ~CopyFileToFilesToMultipleFoldersSubProgram() override;
   int Run(const CloudundancyArgs& args) override;
};
