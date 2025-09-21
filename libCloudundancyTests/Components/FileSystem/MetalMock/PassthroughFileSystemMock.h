#pragma once
#include "libCloudundancy/Components/FileSystem/PassthroughFileSystem.h"

class PassthroughFileSystemMock : public Metal::Mock<PassthroughFileSystem>
{
public:
   METALMOCK_NONVOID1_CONST(unsigned long long, remove_all, const fs::path&)
   METALMOCK_NONVOID1_CONST(unsigned long long, file_size, const fs::path&)
};
