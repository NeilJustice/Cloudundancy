#include "pch.h"
#include "libCloudundancy/Components/FileSystem/PassthroughFileSystem.h"

PassthroughFileSystem::~PassthroughFileSystem()
{
}

unsigned long long PassthroughFileSystem::remove_all(const fs::path& p) const
{
   const unsigned long long numberOfFilesRemoved = fs::remove_all(p);
   return numberOfFilesRemoved;
}

unsigned long long PassthroughFileSystem::file_size(const fs::path& p) const
{
   unsigned long long fileSize = fs::file_size(p);
   return fileSize;
}
