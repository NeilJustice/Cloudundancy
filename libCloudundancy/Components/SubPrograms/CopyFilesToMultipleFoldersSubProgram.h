#pragma once
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgram.h"
class CloudundancyFileCopier;

class CopyFileFastsToMultipleFoldersSubProgram : public CloudundancySubProgram
{
   friend class CopyFileFastsToMultipleFoldersSubProgramTests;
private:
   // Constant Components
   unique_ptr<const CloudundancyFileCopier> _cloudundancyFileCopier;
public:
   CopyFileFastsToMultipleFoldersSubProgram();
   virtual ~CopyFileFastsToMultipleFoldersSubProgram();
   int Run(const CloudundancyArgs& args) override;
};
