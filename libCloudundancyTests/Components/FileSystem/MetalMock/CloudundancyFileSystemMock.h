#pragma once
#include "libCloudundancy/Components/FileSystem/CloudundancyFileSystem.h"

class CloudundancyFileSystemMock : public Metal::Mock<CloudundancyFileSystem>
{
public:
   METALMOCK_VOID1_CONST(DeleteFolder, const fs::path&)

   METALMOCK_VOID1_CONST(DeleteMultipleFolders, const vector<fs::path>&)

   METALMOCK_NONVOID1_CONST(bool, FileSizeIsGreaterThanOrEqualTo2GB, const fs::path&)
};
