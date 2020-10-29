#pragma once
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgram.h"
class CloudundancyFileCopier;
struct CloudundancyArgs;

class BackupFilesAndFoldersSubProgram : public CloudundancySubProgram
{
   friend class BackupFilesAndFoldersSubProgramTests;
private:
   unique_ptr<const CloudundancyFileCopier> _cloudundancyFileCopier;
public:
   BackupFilesAndFoldersSubProgram();
   virtual ~BackupFilesAndFoldersSubProgram();
   virtual int Run(const CloudundancyArgs& args);
};
