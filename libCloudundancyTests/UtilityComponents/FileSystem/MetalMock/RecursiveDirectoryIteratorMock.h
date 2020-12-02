#pragma once
#include "libCloudundancy/UtilityComponents/FileSystem/RecursiveDirectoryIterator.h"

class RecursiveDirectoryIteratorMock : public Metal::Mock<RecursiveDirectoryIterator>
{
public:
   METALMOCK_VOID1(SetFileSubpathsToNotCopy, const vector<string>&)
   METALMOCK_VOID1(InitializeIteratorAtFolderPath, const fs::path&)
   METALMOCK_NONVOID0(fs::path, NextNonIgnoredFilePath)
};
