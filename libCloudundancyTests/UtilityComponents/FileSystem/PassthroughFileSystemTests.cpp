#include "pch.h"
#include "libCloudundancy/UtilityComponents/FileSystem/PassthroughFileSystem.h"

TESTS(PassthroughFileSystemTests)
AFACT(DefaultConstructor_CodeCoverage)
EVIDENCE

TEST(DefaultConstructor_CodeCoverage)
{
   PassthroughFileSystem passthroughFileSystem{};
}

RUN_TESTS(PassthroughFileSystemTests)
