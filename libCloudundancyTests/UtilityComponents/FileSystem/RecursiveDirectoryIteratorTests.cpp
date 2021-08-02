#include "pch.h"
#include "libCloudundancy/UtilityComponents/FileSystem/RecursiveDirectoryIterator.h"

TESTS(RecursiveDirectoryIteratorTests)
AFACT(DefaultConstructor_SetsFilesystemRemoveFunctionPointer_NewsOneExtraArgTransformer)
AFACT(RecursivelyDeleteAllFilesExceptIgnoredFileSubpaths_RecursivelyCallsFilesystemRemoveOnEachFilePathUntilDefaultPathReturned)
EVIDENCE

Utils::RecursiveDirectoryIterator _recursiveDirectoryIterator;

class RecursiveDirectoryIteratorSelfMocked : public Metal::Mock<Utils::RecursiveDirectoryIterator>
{
public:
   METALMOCK_NONVOID1_STATIC(bool, std::filesystem, remove, const fs::path&)
   METALMOCK_NONVOID0(fs::path, NextNonIgnoredFilePath)
   RecursiveDirectoryIteratorSelfMocked()
   {
      _call_fs_remove = BIND_1ARG_METALMOCK_OBJECT(removeMock);
   }
} _recursiveDirectoryIteratorSelfMocked;

TEST(DefaultConstructor_SetsFilesystemRemoveFunctionPointer_NewsOneExtraArgTransformer)
{
   Utils::RecursiveDirectoryIterator recursiveDirectoryIterator;
#ifdef _WIN32
   using FilesystemRemoveOverloadFunctionType = bool(*)(const fs::path&);
   STD_FUNCTION_TARGETS_OVERLOAD(FilesystemRemoveOverloadFunctionType, fs::remove, recursiveDirectoryIterator._call_fs_remove);
   DELETE_TO_ASSERT_NEWED(recursiveDirectoryIterator._oneExtraArgTransformer);
#endif
}

TEST(RecursivelyDeleteAllFilesExceptIgnoredFileSubpaths_RecursivelyCallsFilesystemRemoveOnEachFilePathUntilDefaultPathReturned)
{
   const fs::path filePath1 = ZenUnit::Random<fs::path>();
   const fs::path filePath2 = ZenUnit::Random<fs::path>();
   const fs::path defaultFilePath{};
   _recursiveDirectoryIteratorSelfMocked.NextNonIgnoredFilePathMock.ReturnValues(filePath1, filePath2, defaultFilePath);
   _recursiveDirectoryIteratorSelfMocked.removeMock.ReturnRandom();
   //
   _recursiveDirectoryIteratorSelfMocked.RecursivelyDeleteAllFilesExceptIgnoredFileSubpaths();
   //
   METALMOCK(_recursiveDirectoryIteratorSelfMocked.NextNonIgnoredFilePathMock.CalledNTimes(3));
   METALMOCK(_recursiveDirectoryIteratorSelfMocked.removeMock.CalledAsFollows(
   {
      filePath1, filePath2
   }));
}

RUN_TESTS(RecursiveDirectoryIteratorTests)
