#pragma once
#include "libCloudundancy/Components/FileSystem/CloudundancyFileSystem.h"

class CloudundancyFileSystemMock : public Metal::Mock<CloudundancyFileSystem>
{
public:
   METALMOCK_VOID2_CONST(DeleteMultipleFolderContentsExceptForFile, const vector<fs::path>&, string_view)
   METALMOCK_VOID2_CONST(DeleteFolderContentsExceptForFile, const fs::path&, string_view)
   METALMOCK_NONVOID1_CONST(bool, FileSizeIsGreaterThanOrEqualTo2GB, const fs::path&)
};
