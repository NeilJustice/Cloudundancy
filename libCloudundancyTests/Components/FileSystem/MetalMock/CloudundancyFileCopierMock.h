#pragma once
#include "libCloudundancy/Components/FileSystem/CloudundancyFileCopier.h"

class CloudundancyFileCopierMock : public Metal::Mock<CloudundancyFileCopier>
{
public:
   METALMOCK_VOID2_CONST(CopyFileFastsAndFoldersToMultipleDestinationFolders, const fs::path&, bool)
};
