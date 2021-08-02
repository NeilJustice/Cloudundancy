#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyFileSystem.h"

TESTS(CloudundancyFileSystemTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(DeleteMultipleFolderContentsExceptForFile_CallsDeleteContentsOfFolderExceptForFileNameOnEachFolderPath)
EVIDENCE

CloudundancyFileSystem _cloudundancyFileSystem;
// Function Pointers
METALMOCK_NONVOID1_FREE(bool, _call_fs_exists, const fs::path&)
// Function Callers
using _forEacher_DeleteContentsOfFolderExceptForFileNameMockType = Utils::OneExtraArgMemberFunctionForEacherMock<CloudundancyFileSystem, fs::path, string_view>;
_forEacher_DeleteContentsOfFolderExceptForFileNameMockType* _forEacher_DeleteContentsOfFolderExceptForFileNameMock = nullptr;

STARTUP
{
   // Function Pointers
   _cloudundancyFileSystem._call_fs_exists = BIND_1ARG_METALMOCK_OBJECT(_call_fs_existsMock);
   // Function Callers
   _cloudundancyFileSystem._forEacher_DeleteContentsOfFolderExceptForFileName.reset(_forEacher_DeleteContentsOfFolderExceptForFileNameMock = new _forEacher_DeleteContentsOfFolderExceptForFileNameMockType);
}

TEST(DefaultConstructor_NewsComponents)
{
   CloudundancyFileSystem cloudundancyFileSystem;
   // Function Pointers
   STD_FUNCTION_TARGETS_OVERLOAD(CloudundancyFileSystem::_fs_exists_FunctionOverloadType, fs::exists, cloudundancyFileSystem._call_fs_exists);
   // Function Callers
   DELETE_TO_ASSERT_NEWED(cloudundancyFileSystem._forEacher_DeleteContentsOfFolderExceptForFileName);
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
