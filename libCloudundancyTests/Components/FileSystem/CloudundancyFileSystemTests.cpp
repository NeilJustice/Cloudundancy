#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyFileSystem.h"
#include "libCloudundancyTests/UtilityComponents/FileSystem/MetalMock/PassthroughFileSystemMock.h"

TESTS(CloudundancyFileSystemTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(DeleteFolderContentsExceptForFile_FolderDoesNotExist_DoesNothing)
AFACT(DeleteFolderContentsExceptForFile_FolderExists_DeletesFolderContentsExceptForFile)
AFACT(DeleteMultipleFolderContentsExceptForFile_CallsDeleteContentsOfFolderExceptForFileNameOnEachFolderPath)
FACTS(FileSizeIsGreaterThanOrEqualTo2GB_FileSizeIsLessThan2GB_ReturnsFalse)
FACTS(FileSizeIsGreaterThanOrEqualTo2GB_FileSizeIsGreaterThanOrEqualTo2GB_ReturnsTrue)
EVIDENCE

CloudundancyFileSystem _cloudundancyFileSystem;
// Function Pointers
METALMOCK_NONVOID1_FREE(bool, _call_fs_exists, const fs::path&)
// Function Callers
using _forEacher_DeleteContentsOfFolderExceptForFileNameMockType = Utils::TwoArgMemberFunctionForEacherMock<CloudundancyFileSystem, fs::path, string_view>;
_forEacher_DeleteContentsOfFolderExceptForFileNameMockType* _forEacher_DeleteContentsOfFolderExceptForFileNameMock = nullptr;
// Constant Components
Utils::ConsoleMock* _consoleMock = nullptr;
Utils::FileSystemMock* _fileSystemMock = nullptr;
PassthroughFileSystemMock* _passthroughFileSystemMock = nullptr;

STARTUP
{
   // Function Pointers
   _cloudundancyFileSystem._call_fs_exists = BIND_1ARG_METALMOCK_OBJECT(_call_fs_existsMock);
   // Function Callers
   _cloudundancyFileSystem._forEacher_DeleteContentsOfFolderExceptForFileName.reset(_forEacher_DeleteContentsOfFolderExceptForFileNameMock = new _forEacher_DeleteContentsOfFolderExceptForFileNameMockType);
   // Constant Components
   _cloudundancyFileSystem._console.reset(_consoleMock = new Utils::ConsoleMock);
   _cloudundancyFileSystem._fileSystem.reset(_fileSystemMock = new Utils::FileSystemMock);
   _cloudundancyFileSystem._passthroughFileSystem.reset(_passthroughFileSystemMock = new PassthroughFileSystemMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   CloudundancyFileSystem cloudundancyFileSystem;
   // Function Pointers
#ifdef _WIN32
   STD_FUNCTION_TARGETS_OVERLOAD(CloudundancyFileSystem::fs_exists_FunctionOverloadType, fs::exists, cloudundancyFileSystem._call_fs_exists);
#endif
   // Function Callers
   DELETE_TO_ASSERT_NEWED(cloudundancyFileSystem._forEacher_DeleteContentsOfFolderExceptForFileName);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(cloudundancyFileSystem._console);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileSystem._fileSystem);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileSystem._passthroughFileSystem);
}

TEST(DeleteFolderContentsExceptForFile_FolderDoesNotExist_DoesNothing)
{
   _call_fs_existsMock.Return(false);
   const fs::path folderPath = ZenUnit::Random<fs::path>();
   const string exceptFileName = ZenUnit::Random<string>();
   //
   _cloudundancyFileSystem.DeleteFolderContentsExceptForFile(folderPath, exceptFileName);
   //
   METALMOCK(_call_fs_existsMock.CalledOnceWith(folderPath));
}

TEST(DeleteFolderContentsExceptForFile_FolderExists_DeletesFolderContentsExceptForFile)
{
   _call_fs_existsMock.Return(true);

   const string textOfExceptFile = _fileSystemMock->ReadFileTextMock.ReturnRandom();

   _fileSystemMock->DeleteFolderMock.Expect();

   _fileSystemMock->CreateFileWithTextIfDoesNotExistMock.Expect();

   _consoleMock->WriteLineMock.Expect();

   const fs::path folderPath = ZenUnit::Random<fs::path>();
   const string exceptFileName = ZenUnit::Random<string>();
   //
   _cloudundancyFileSystem.DeleteFolderContentsExceptForFile(folderPath, exceptFileName);
   //
   const fs::path expectedExceptFilePath = folderPath / exceptFileName;
   const string expectedDeletedFolderMessage = Utils::String::ConcatStrings("[Cloudundancy] Deleted folder ", folderPath.string(), " except for ", exceptFileName);
   METALMOCKTHEN(_call_fs_existsMock.CalledOnceWith(folderPath)).Then(
   METALMOCKTHEN(_fileSystemMock->ReadFileTextMock.CalledOnceWith(expectedExceptFilePath))).Then(
   METALMOCKTHEN(_fileSystemMock->DeleteFolderMock.CalledOnceWith(folderPath))).Then(
   METALMOCKTHEN(_fileSystemMock->CreateFileWithTextIfDoesNotExistMock.CalledOnceWith(expectedExceptFilePath, textOfExceptFile))).Then(
   METALMOCKTHEN(_consoleMock->WriteLineMock.CalledOnceWith(expectedDeletedFolderMessage)));
}

TEST(DeleteMultipleFolderContentsExceptForFile_CallsDeleteContentsOfFolderExceptForFileNameOnEachFolderPath)
{
   _forEacher_DeleteContentsOfFolderExceptForFileNameMock->CallConstMemberFunctionWithEachElementMock.Expect();
   const vector<fs::path> folderPaths = ZenUnit::RandomVector<fs::path>();
   const string exceptFileName = ZenUnit::Random<string>();
   //
   _cloudundancyFileSystem.DeleteMultipleFolderContentsExceptForFile(folderPaths, exceptFileName);
   //
   METALMOCK(_forEacher_DeleteContentsOfFolderExceptForFileNameMock->CallConstMemberFunctionWithEachElementMock.CalledOnceWith(
      folderPaths, &_cloudundancyFileSystem, &CloudundancyFileSystem::DeleteFolderContentsExceptForFile, exceptFileName));
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
