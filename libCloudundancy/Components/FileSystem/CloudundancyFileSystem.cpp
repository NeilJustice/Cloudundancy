#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyFileSystem.h"
#include "libCloudundancy/UtilityComponents/FileSystem/FileSystem.h"
#include "libCloudundancy/UtilityComponents/FileSystem/PassthroughFileSystem.h"

CloudundancyFileSystem::CloudundancyFileSystem()
   // Function Pointers
   : _call_fs_exists_as_assignable_function_overload_pointer(fs::exists)
   // Function Callers
   , _forEacher_DeleteContentsOfFolderExceptForFileName(make_unique<_forEacher_DeleteContentsOfFolderExceptForFileNameType>())
   // Constant Components
   , _console(make_unique<Time::Console>())
   , _fileSystem(make_unique<Utils::FileSystem>())
   , _passthroughFileSystem(make_unique<PassthroughFileSystem>())
{
   _call_fs_exists = _call_fs_exists_as_assignable_function_overload_pointer;
}

CloudundancyFileSystem::~CloudundancyFileSystem()
{
}

void CloudundancyFileSystem::DeleteMultipleFolderContentsExceptForFile(const vector<fs::path>& folderPaths, string_view exceptFileName) const
{
   _forEacher_DeleteContentsOfFolderExceptForFileName->CallConstMemberFunctionWithEachElement(
      folderPaths, this, &CloudundancyFileSystem::DeleteFolderContentsExceptForFile, exceptFileName);
}

void CloudundancyFileSystem::DeleteFolderContentsExceptForFile(const fs::path& folderPath, string_view exceptFileName) const
{
   const bool folderPathExists = _call_fs_exists(folderPath);
   if (!folderPathExists)
   {
      return;
   }
   const fs::path exceptFilePath = folderPath / exceptFileName;
   const string textOfExceptFile = _fileSystem->ReadFileText(exceptFilePath);
   _fileSystem->DeleteFolder(folderPath);
   _fileSystem->CreateTextFileIfDoesNotExist(exceptFilePath, textOfExceptFile);
   const string deletedFolderMessage = Utils::String::ConcatStrings(
      "[Cloudundancy] Deleted folder ", folderPath.string(), " except for ", exceptFileName);
   _console->WriteLine(deletedFolderMessage);
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
