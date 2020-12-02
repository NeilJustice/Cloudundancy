#pragma once
#include "libCloudundancy/UtilityComponents/FileSystem/FileOpenerCloser.h"

class FileOpenerCloserMock : public Metal::Mock<FileOpenerCloser>
{
public:
   METALMOCK_VOID1_CONST(CloseFile, FILE*)
   METALMOCK_NONVOID1_CONST(FILE*, CreateWriteModeBinaryFile, const fs::path&)
   METALMOCK_NONVOID1_CONST(FILE*, CreateWriteModeTextFile, const fs::path&)
   METALMOCK_NONVOID1_CONST(FILE*, OpenReadModeBinaryFile, const fs::path&)
   METALMOCK_NONVOID1_CONST(FILE*, OpenReadModeTextFile, const fs::path&)
   METALMOCK_NONVOID1_CONST(FILE*, OpenAppendModeTextFile, const fs::path&)
};
