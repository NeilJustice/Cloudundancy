#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyFileSystem.h"
#include "libCloudundancy/Components/FileSystem/FileSystem.h"
#include "libCloudundancy/Components/FileSystem/PassthroughFileSystem.h"
#include "libCloudundancy/Components/Iteration/ForEach/OneArgMemberFunctionForEacher.h"

CloudundancyFileSystem::CloudundancyFileSystem()
   // Function Pointers
   : _call_fs_exists_as_assignable_function_overload_pointer(fs::exists)
   , _call_fs_exists(_call_fs_exists_as_assignable_function_overload_pointer)
   // Function Callers
   , _forEacher_DeleteFolder(make_unique<_forEacher_DeleteFolderType>())
   // Constant Components
   , _console(make_unique<Utils::Console>())
   , _fileSystem(make_unique<Utils::FileSystem>())
   , _passthroughFileSystem(make_unique<PassthroughFileSystem>())
{
}

CloudundancyFileSystem::~CloudundancyFileSystem()
{
}

void CloudundancyFileSystem::DeleteFolder(const fs::path& folderPath) const
{
   const bool folderPathExists = _call_fs_exists(folderPath);
   if (!folderPathExists)
   {
      return;
   }
   _fileSystem->DeleteFolder(folderPath);
   const string deletedFolderMessage = Utils::String::ConcatStrings("[Cloudundancy] Deleted folder ", folderPath.string());
   _console->WriteLine(deletedFolderMessage);
}

void CloudundancyFileSystem::DeleteMultipleFolders(const vector<fs::path>& folderPaths) const
{
   _forEacher_DeleteFolder->CallConstMemberFunctionWithEachElement(
      folderPaths,
      this, &CloudundancyFileSystem::DeleteFolder);
}

bool CloudundancyFileSystem::FileSizeIsGreaterThanOrEqualTo2GB(const fs::path& filePath) const
{
   const size_t fileSizeInBytes = _passthroughFileSystem->file_size(filePath);
   constexpr size_t NumberOfBytesIn2GB = 2ULL * 1024ULL * 1024ULL * 1024ULL;
   static_assert(NumberOfBytesIn2GB == 2147483648);
   if (fileSizeInBytes >= NumberOfBytesIn2GB)
   {
      return true;
   }
   return false;
}
