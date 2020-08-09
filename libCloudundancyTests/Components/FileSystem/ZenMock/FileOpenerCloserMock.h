#pragma once
#include "libCloudundancy/Components/FileSystem/FileOpenerCloser.h"

class FileOpenerCloserMock : public Zen::Mock<FileOpenerCloser>
{
public:
   ZENMOCK_VOID1_CONST(CloseFile, FILE*)
   ZENMOCK_NONVOID1_CONST(FILE*, CreateBinaryFileInWriteMode, const fs::path&)
   ZENMOCK_NONVOID1_CONST(FILE*, CreateTextFileInWriteMode, const fs::path&)
   ZENMOCK_NONVOID1_CONST(FILE*, OpenBinaryFileInReadMode, const fs::path&)
   ZENMOCK_NONVOID1_CONST(FILE*, OpenTextFileInReadMode, const fs::path&)
};
