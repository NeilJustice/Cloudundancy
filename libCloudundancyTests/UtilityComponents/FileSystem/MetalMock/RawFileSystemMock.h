#pragma once
#include "libCloudundancy/UtilityComponents/FileSystem/RawFileSystem.h"

namespace Utils
{
   class RawFileSystemMock : public Metal::Mock<RawFileSystem>
   {
   public:
      METALMOCK_VOID2_CONST(AppendTextToClosedFile, const fs::path&, string_view)
      METALMOCK_VOID2_CONST(CloseFile, const shared_ptr<FILE>&, const fs::path&)
      METALMOCK_VOID2_CONST(CreateFileWithTextIfDoesNotExist, const fs::path&, string_view)
      METALMOCK_NONVOID1_CONST(shared_ptr<FILE>, CreateFileInBinaryWriteMode, const fs::path&)
      METALMOCK_NONVOID1_CONST(shared_ptr<FILE>, CreateOrOpenFileInBinaryAppendMode, const fs::path&)
      METALMOCK_NONVOID1_CONST(shared_ptr<FILE>, OpenFileInBinaryReadMode, const fs::path&)
      METALMOCK_NONVOID2_CONST(string, ReadTextFromOpenFile, const shared_ptr<FILE>&, const fs::path&)
      METALMOCK_VOID2_CONST(WriteTextToOpenFile, const shared_ptr<FILE>&, string_view)
      METALMOCK_VOID3_CONST(WriteBytesToOpenFile, const shared_ptr<FILE>&, const void*, size_t)
   };
}
