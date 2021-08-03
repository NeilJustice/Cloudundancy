#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyFileSystem.h"

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
METALMOCK_NONVOID1_FREE(unsigned long long, _call_fs_file_size, const fs::path&)
// Function Callers
using _forEacher_DeleteContentsOfFolderExceptForFileNameMockType = Utils::OneExtraArgMemberFunctionForEacherMock<CloudundancyFileSystem, fs::path, string_view>;
_forEacher_DeleteContentsOfFolderExceptForFileNameMockType* _forEacher_DeleteContentsOfFolderExceptForFileNameMock = nullptr;
// Constant Components
Utils::ConsoleMock* _consoleMock = nullptr;
Utils::RawFileSystemMock* _rawFileSystemMock = nullptr;

STARTUP
{
   // Function Pointers
   _cloudundancyFileSystem._call_fs_exists = BIND_1ARG_METALMOCK_OBJECT(_call_fs_existsMock);
   _cloudundancyFileSystem._call_fs_file_size = BIND_1ARG_METALMOCK_OBJECT(_call_fs_file_sizeMock);
   // Function Callers
   _cloudundancyFileSystem._forEacher_DeleteContentsOfFolderExceptForFileName.reset(_forEacher_DeleteContentsOfFolderExceptForFileNameMock = new _forEacher_DeleteContentsOfFolderExceptForFileNameMockType);
   // Constant Components
   _cloudundancyFileSystem._console.reset(_consoleMock = new Utils::ConsoleMock);
   _cloudundancyFileSystem._rawFileSystem.reset(_rawFileSystemMock = new Utils::RawFileSystemMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   CloudundancyFileSystem cloudundancyFileSystem;
   // Function Pointers
   STD_FUNCTION_TARGETS_OVERLOAD(CloudundancyFileSystem::fs_exists_FunctionOverloadType, fs::exists, cloudundancyFileSystem._call_fs_exists);
   STD_FUNCTION_TARGETS_OVERLOAD(CloudundancyFileSystem::fs_file_size_FunctionOverloadType, fs::file_size, cloudundancyFileSystem._call_fs_file_size);
   // Function Callers
   DELETE_TO_ASSERT_NEWED(cloudundancyFileSystem._forEacher_DeleteContentsOfFolderExceptForFileName);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(cloudundancyFileSystem._console);
   DELETE_TO_ASSERT_NEWED(cloudundancyFileSystem._rawFileSystem);
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

   const string textOfExceptFile = _rawFileSystemMock->ReadFileTextMock.ReturnRandom();

   _rawFileSystemMock->DeleteFolderMock.Expect();

   _rawFileSystemMock->CreateFileWithTextIfDoesNotExistMock.Expect();

   _consoleMock->WriteLineMock.Expect();

   const fs::path folderPath = ZenUnit::Random<fs::path>();
   const string exceptFileName = ZenUnit::Random<string>();
   //
   _cloudundancyFileSystem.DeleteFolderContentsExceptForFile(folderPath, exceptFileName);
   //
   METALMOCK(_call_fs_existsMock.CalledOnceWith(folderPath));
   const fs::path expectedExceptFilePath = folderPath / exceptFileName;
   METALMOCK(_rawFileSystemMock->ReadFileTextMock.CalledOnceWith(expectedExceptFilePath));
   METALMOCK(_rawFileSystemMock->DeleteFolderMock.CalledOnceWith(folderPath));
   METALMOCK(_rawFileSystemMock->CreateFileWithTextIfDoesNotExistMock.CalledOnceWith(expectedExceptFilePath, textOfExceptFile));
   const string expectedDeletedFolderMessage = Utils::String::ConcatStrings("[Cloudundancy] Deleted folder ", folderPath.string(), " except for ", exceptFileName);
   METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(expectedDeletedFolderMessage));
}

TEST(DeleteMultipleFolderContentsExceptForFile_CallsDeleteContentsOfFolderExceptForFileNameOnEachFolderPath)
{
   _forEacher_DeleteContentsOfFolderExceptForFileNameMock->CallConstMemberFunctionForEachElementMock.Expect();
   const vector<fs::path> folderPaths = ZenUnit::RandomVector<fs::path>();
   const string exceptFileName = ZenUnit::Random<string>();
   //
   _cloudundancyFileSystem.DeleteMultipleFolderContentsExceptForFile(folderPaths, exceptFileName);
   //
   METALMOCK(_forEacher_DeleteContentsOfFolderExceptForFileNameMock->CallConstMemberFunctionForEachElementMock.CalledOnceWith(
      folderPaths, &CloudundancyFileSystem::DeleteFolderContentsExceptForFile, &_cloudundancyFileSystem, exceptFileName));
}

TEST1X1(FileSizeIsGreaterThanOrEqualTo2GB_FileSizeIsLessThan2GB_ReturnsFalse,
   size_t fileSizeInBytes,
   2ULL * 1024ULL * 1024ULL * 1024ULL - 2ULL,
   2ULL * 1024ULL * 1024ULL * 1024ULL - 1ULL)
{
   _call_fs_file_sizeMock.Return(fileSizeInBytes);
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const bool fileSizeIsGreaterThanOrEqualTo2GB = _cloudundancyFileSystem.FileSizeIsGreaterThanOrEqualTo2GB(filePath);
   //
   METALMOCK(_call_fs_file_sizeMock.CalledOnceWith(filePath));
   IS_FALSE(fileSizeIsGreaterThanOrEqualTo2GB);
}

TEST1X1(FileSizeIsGreaterThanOrEqualTo2GB_FileSizeIsGreaterThanOrEqualTo2GB_ReturnsTrue,
   size_t fileSizeInBytes,
   2ULL * 1024ULL * 1024ULL * 1024ULL,
   2ULL * 1024ULL * 1024ULL * 1024ULL + 1ULL,
   2ULL * 1024ULL * 1024ULL * 1024ULL + 2ULL)
{
   _call_fs_file_sizeMock.Return(fileSizeInBytes);
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const bool fileSizeIsGreaterThanOrEqualTo2GB = _cloudundancyFileSystem.FileSizeIsGreaterThanOrEqualTo2GB(filePath);
   //
   METALMOCK(_call_fs_file_sizeMock.CalledOnceWith(filePath));
   IS_TRUE(fileSizeIsGreaterThanOrEqualTo2GB);
}

RUN_TESTS(CloudundancyFileSystemTests)
