#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyFileSystem.h"

TESTS(CloudundancyFileSystemTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(DeleteFolderContentsExceptForFile_FolderDoesNotExist_DoesNothing)
AFACT(DeleteFolderContentsExceptForFile_FolderExists_DeletesFolderContentsExceptForFile)
AFACT(DeleteMultipleFolderContentsExceptForFile_CallsDeleteContentsOfFolderExceptForFileNameOnEachFolderPath)
EVIDENCE

CloudundancyFileSystem _cloudundancyFileSystem;
// Function Pointers
METALMOCK_NONVOID1_FREE(bool, _call_fs_exists, const fs::path&)
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
   STD_FUNCTION_TARGETS_OVERLOAD(CloudundancyFileSystem::_fs_exists_FunctionOverloadType, fs::exists, cloudundancyFileSystem._call_fs_exists);
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

RUN_TESTS(CloudundancyFileSystemTests)
