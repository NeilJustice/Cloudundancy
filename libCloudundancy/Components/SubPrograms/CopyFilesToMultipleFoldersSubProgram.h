#pragma once
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgram.h"
class CloudundancyFileCopier;

class CopyFilesToMultipleFoldersSubProgram : public CloudundancySubProgram
{
   friend class CopyFilesToMultipleFoldersSubProgramTests;
private:
   // Constant Components
   unique_ptr<const CloudundancyFileCopier> _cloudundancyFileCopier;
public:
   CopyFilesToMultipleFoldersSubProgram();
   virtual ~CopyFilesToMultipleFoldersSubProgram();
   int Run(const CloudundancyArgs& args) override;
};
