#pragma once
#include "libCloudundancy/Components/FileSystem/FileSystem.h"

class FileSystemMock : public Zen::Mock<FileSystem>
{
public:
   ZENMOCK_VOID1_CONST(DeleteFolder, const fs::path&)
   ZENMOCK_NONVOID1_CONST(bool, FileOrFolderExists, const fs::path&)
   ZENMOCK_NONVOID1_CONST(std::vector<std::string>, ReadAsciiFileLinesWhichMustBeNonEmpty, const fs::path&)
   ZENMOCK_NONVOID1_CONST(std::string, ReadAsciiFileText, const fs::path&)
   ZENMOCK_NONVOID1_CONST(std::vector<char>, ReadFileBytes, const fs::path&)
   ZENMOCK_VOID1_CONST(SetCurrentPath, const fs::path&)
   ZENMOCK_VOID1_CONST(ThrowIfFilePathIsNotEmptyAndDoesNotExist, const fs::path&)
   ZENMOCK_NONVOID2_CONST(FileCopyResult, TryCopyFile, const fs::path&, const fs::path&)
   ZENMOCK_VOID2_CONST(WriteTextFile, const fs::path&, string_view)
};
