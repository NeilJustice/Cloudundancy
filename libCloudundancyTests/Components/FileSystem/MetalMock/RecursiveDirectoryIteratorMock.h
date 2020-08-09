#pragma once
#include "libCloudundancy/Components/FileSystem/RecursiveDirectoryIterator.h"

class RecursiveDirectoryIteratorMock : public Zen::Mock<RecursiveDirectoryIterator>
{
public:
   METALMOCK_VOID1(SetFileSubpathsToNotCopy, const vector<string>&)
   METALMOCK_VOID1(SetRecursiveDirectoryIterator, const fs::path&)
   METALMOCK_NONVOID0(fs::path, NextNonIgnoredFilePath)
};
