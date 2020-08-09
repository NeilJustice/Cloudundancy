#pragma once
#include "libCloudundancy/Components/CloudundancyFileCopier.h"

class CloudundancyFileCopierMock : public Zen::Mock<CloudundancyFileCopier>
{
public:
   ZENMOCK_VOID1_CONST(CopyFilesAndFoldersToMultipleFolders, const fs::path&)
   ZENMOCK_VOID1_CONST(DeleteFolder, const fs::path&)
};
