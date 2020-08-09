#pragma once
#include "libCloudundancy/Components/RecursiveDirectoryIterator.h"

class RecursiveDirectoryIteratorMock : public Zen::Mock<RecursiveDirectoryIterator>
{
public:
   ZENMOCK_VOID1(SetFileSubpathsToNotCopy, const vector<string>&)
   ZENMOCK_VOID1(InitializeIteratorAtFolderPath, const fs::path&)
   ZENMOCK_NONVOID0(fs::path, NextNonIgnoredFilePath)
};
