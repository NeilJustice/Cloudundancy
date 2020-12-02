#pragma once
#include "libCloudundancy/Components/FileSystem/CloudundancyFileCopier.h"

class CloudundancyFileCopierMock : public Metal::Mock<CloudundancyFileCopier>
{
public:
   METALMOCK_VOID1_CONST(CopyFilesAndFoldersToMultipleDestinationFolders, const fs::path&)
};
