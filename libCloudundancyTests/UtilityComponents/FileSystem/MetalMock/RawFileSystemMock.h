#pragma once
#include "libCloudundancy/UtilityComponents/FileSystem/RawFileSystem.h"

namespace Utils
{
   class RawFileSystemMock : public Metal::Mock<RawFileSystem>
   {
   public:
      // File Open Functions
      METALMOCK_NONVOID1_CONST(shared_ptr<FILE>, CreateFileInBinaryWriteMode, const fs::path&)
      METALMOCK_NONVOID1_CONST(shared_ptr<FILE>, CreateOrOpenFileInBinaryAppendMode, const fs::path&)
      METALMOCK_NONVOID1_CONST(shared_ptr<FILE>, OpenFileInBinaryReadMode, const fs::path&)
      METALMOCK_NONVOID1_CONST(shared_ptr<FILE>, OpenFileInTextReadMode, const fs::path&)
      // Behavior Functions
      METALMOCK_VOID2_CONST(AppendTextToClosedFile, const fs::path&, string_view)
      METALMOCK_NONVOID2_CONST(Utils::FileCopyResult, CopyFileFast, const fs::path&, const fs::path&)
      METALMOCK_NONVOID2_CONST(Utils::FileCopyResult, CopyFileFastLargerThan2GB, const fs::path&, const fs::path&)
      METALMOCK_VOID2_CONST(CloseFile, const shared_ptr<FILE>&, const fs::path&)
      METALMOCK_VOID2_CONST(CreateFileWithTextIfDoesNotExist, const fs::path&, string_view)
      METALMOCK_VOID1_CONST(DeleteFolder, const fs::path&)
      METALMOCK_NONVOID1_CONST(bool, FileOrFolderExists, const fs::path&)
      METALMOCK_NONVOID1_CONST(vector<string>, ReadFileLinesWhichMustBeNonEmpty, const fs::path&)
      METALMOCK_NONVOID1_CONST(shared_ptr<const vector<char>>, ReadFileBytes, const fs::path&)
      METALMOCK_NONVOID1_CONST(string, ReadFileText, const fs::path&)
      METALMOCK_VOID1_CONST(SetCurrentPath, const fs::path&)
      METALMOCK_VOID1_CONST(ThrowIfFilePathIsNotEmptyPathAndFileDoesNotExist, const fs::path&)
      METALMOCK_VOID2_CONST(WriteTextToOpenFile, const shared_ptr<FILE>&, string_view)
      METALMOCK_VOID3_CONST(WriteBytesToOpenFile, const shared_ptr<FILE>&, const void*, size_t)
   };
}
