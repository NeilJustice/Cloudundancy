#pragma once
#include "libCloudundancy/Components/FileSystem/FileOpenerCloser.h"

class FileOpenerCloserMock : public Metal::Mock<FileOpenerCloser>
{
public:
   METALMOCK_VOID1_CONST(CloseFile, FILE*)
   METALMOCK_NONVOID1_CONST(FILE*, CreateBinaryFileInWriteMode, const fs::path&)
   METALMOCK_NONVOID1_CONST(FILE*, CreateTextFileInWriteMode, const fs::path&)
   METALMOCK_NONVOID1_CONST(FILE*, OpenBinaryFileInReadMode, const fs::path&)
   METALMOCK_NONVOID1_CONST(FILE*, OpenTextFileInReadMode, const fs::path&)
};
