#include "pch.h"
#include "libCloudundancy/UtilityComponents/FileSystem/RecursiveDirectoryIterator.h"

TESTS(RecursiveDirectoryIteratorTests)
AFACT(DefaultConstructor_SetsFilesystemRemoveFunctionPointer)
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

TEST(DefaultConstructor_SetsFilesystemRemoveFunctionPointer)
{
   Utils::RecursiveDirectoryIterator recursiveDirectoryIterator;
#ifdef _WIN32
   using FilesystemRemoveOverloadFunctionType = bool(*)(const fs::path&);
   STD_FUNCTION_TARGETS_OVERLOAD(FilesystemRemoveOverloadFunctionType, fs::remove, recursiveDirectoryIterator._call_fs_remove);
#endif
}

RUN_TESTS(RecursiveDirectoryIteratorTests)
