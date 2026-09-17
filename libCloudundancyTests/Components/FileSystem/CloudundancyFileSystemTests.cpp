#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyFileSystem.h"
#include "libCloudundancyTests/Components/FileSystem/MetalMock/PassthroughFileSystemMock.h"
#include "libCloudundancyTests/Components/Iteration/ForEach/MetalMock/OneArgMemberFunctionForEacherMock.h"

TESTS(CloudundancyFileSystemTests)
AFACT(DefaultConstructor_NewsComponents)

AFACT(DeleteFolder_FolderDoesNotExist_DoesNothing)
AFACT(DeleteFolder_FolderExists_DoesSo)

AFACT(DeleteMultipleFolders_DoesSo)

FACTS(FileSizeIsGreaterThanOrEqualTo2GB_FileSizeIsLessThan2GB_ReturnsFalse)
FACTS(FileSizeIsGreaterThanOrEqualTo2GB_FileSizeIsGreaterThanOrEqualTo2GB_ReturnsTrue)
EVIDENCE

CloudundancyFileSystem _cloudundancyFileSystem;
// Function Pointers
METALMOCK_NONVOID1_STATIC_OR_FREE(bool, _call_fs_exists, const fs::path&)
// Function Callers
using _forEacher_DeleteFolderMockType = Utils::OneArgMemberFunctionForEacherMock<CloudundancyFileSystem, fs::path>;
_forEacher_DeleteFolderMockType* _forEacher_DeleteFolderMock = nullptr;
// Constant Components
Utils::ConsoleMock* _consoleMock = nullptr;
Utils::FileSystemMock* _fileSystemMock = nullptr;
PassthroughFileSystemMock* _passthroughFileSystemMock = nullptr;

STARTUP
{
   // Function Pointers
   _cloudundancyFileSystem._call_fs_exists = BIND_1ARG_METALMOCK_OBJECT(_call_fs_existsMock);
   // Function Callers
   _cloudundancyFileSystem._forEacher_DeleteFolder.reset(_forEacher_DeleteFolderMock = new _forEacher_DeleteFolderMockType);
   // Constant Components
   _cloudundancyFileSystem._console.reset(_consoleMock = new Utils::ConsoleMock);
   _cloudundancyFileSystem._fileSystem.reset(_fileSystemMock = new Utils::FileSystemMock);
   _cloudundancyFileSystem._passthroughFileSystem.reset(_passthroughFileSystemMock = new PassthroughFileSystemMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   const CloudundancyFileSystem cloudundancyFileSystem;
   // Function Pointers
#ifdef _WIN32
   STD_FUNCTION_TARGETS_OVERLOAD(CloudundancyFileSystem::fs_exists_FunctionOverloadType, fs::exists, cloudundancyFileSystem._call_fs_exists);
#endif
}

TEST(DeleteFolder_FolderDoesNotExist_DoesNothing)
{
   _call_fs_existsMock.Return(false);
   const fs::path folderPath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileSystem.DeleteFolder(folderPath);
   //
   METALMOCK(_call_fs_existsMock.CalledOnceWith(folderPath));
}

TEST(DeleteFolder_FolderExists_DoesSo)
{
   _call_fs_existsMock.Return(true);
   _fileSystemMock->DeleteFolderMock.Expect();
   _consoleMock->WriteLineMock.Expect();
   const fs::path folderPath = ZenUnit::Random<fs::path>();
   //
   _cloudundancyFileSystem.DeleteFolder(folderPath);
   //
   const string expectedDeletedFolderMessage = Utils::String::ConcatStrings("[Cloudundancy] Deleted folder ", folderPath.string());
   METALMOCKTHEN(_call_fs_existsMock.CalledOnceWith(folderPath)).Then(
   METALMOCKTHEN(_fileSystemMock->DeleteFolderMock.CalledOnceWith(folderPath))).Then(
   METALMOCKTHEN(_consoleMock->WriteLineMock.CalledOnceWith(expectedDeletedFolderMessage)));
}

TEST(DeleteMultipleFolders_DoesSo)
{
   _forEacher_DeleteFolderMock->CallConstMemberFunctionWithEachElementMock.Expect();
   const vector<fs::path> folderPaths = ZenUnit::RandomVector<fs::path>();
   //
   _cloudundancyFileSystem.DeleteMultipleFolders(folderPaths);
   //
   METALMOCK(_forEacher_DeleteFolderMock->CallConstMemberFunctionWithEachElementMock.CalledOnceWith(
      folderPaths,
      &_cloudundancyFileSystem, &CloudundancyFileSystem::DeleteFolder));
}

TEST1X1(FileSizeIsGreaterThanOrEqualTo2GB_FileSizeIsLessThan2GB_ReturnsFalse,
   size_t fileSizeInBytes,
   2ULL * 1024ULL * 1024ULL * 1024ULL - 2ULL,
   2ULL * 1024ULL * 1024ULL * 1024ULL - 1ULL)
{
   _passthroughFileSystemMock->file_sizeMock.Return(fileSizeInBytes);
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const bool fileSizeIsGreaterThanOrEqualTo2GB = _cloudundancyFileSystem.FileSizeIsGreaterThanOrEqualTo2GB(filePath);
   //
   METALMOCK(_passthroughFileSystemMock->file_sizeMock.CalledOnceWith(filePath));
   IS_FALSE(fileSizeIsGreaterThanOrEqualTo2GB);
}

TEST1X1(FileSizeIsGreaterThanOrEqualTo2GB_FileSizeIsGreaterThanOrEqualTo2GB_ReturnsTrue,
   size_t fileSizeInBytes,
   2ULL * 1024ULL * 1024ULL * 1024ULL,
   2ULL * 1024ULL * 1024ULL * 1024ULL + 1ULL,
   2ULL * 1024ULL * 1024ULL * 1024ULL + 2ULL)
{
   _passthroughFileSystemMock->file_sizeMock.Return(fileSizeInBytes);
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const bool fileSizeIsGreaterThanOrEqualTo2GB = _cloudundancyFileSystem.FileSizeIsGreaterThanOrEqualTo2GB(filePath);
   //
   METALMOCK(_passthroughFileSystemMock->file_sizeMock.CalledOnceWith(filePath));
   IS_TRUE(fileSizeIsGreaterThanOrEqualTo2GB);
}

RUN_TESTS(CloudundancyFileSystemTests)
