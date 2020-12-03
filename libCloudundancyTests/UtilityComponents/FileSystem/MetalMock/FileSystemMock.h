#pragma once
#include "libCloudundancy/UtilityComponents/FileSystem/FileSystem.h"

class FileSystemMock : public Metal::Mock<FileSystem>
{
public:
   // File Or Folder Existence Checks
   METALMOCK_NONVOID1_CONST(bool, FileOrFolderExists, const fs::path&)
   METALMOCK_VOID1_CONST(ThrowIfFilePathIsNotEmptyAndDoesNotExist, const fs::path&)

   // File Reads
   METALMOCK_NONVOID1_CONST(string, ReadFileText, const fs::path&)
   METALMOCK_NONVOID1_CONST(shared_ptr<const vector<char>>, ReadFileBytes, const fs::path&)
   METALMOCK_NONVOID1_CONST(vector<string>, ReadFileLinesWhichMustBeNonEmpty, const fs::path&)

   // File Copies
   METALMOCK_NONVOID1_CONST(bool, IsFileSizeGreaterThanOrEqualTo2GB, const fs::path&)
   METALMOCK_NONVOID2_CONST(FileCopyResult, TryCopyFile, const fs::path&, const fs::path&)
   METALMOCK_NONVOID2_CONST(FileCopyResult, TryCopyFileWithStdFilesystemCopyFile, const fs::path&, const fs::path&)

   // File Writes
   METALMOCK_VOID2_CONST(AppendText, const fs::path&, string_view)
   METALMOCK_VOID2_CONST(WriteTextFile, const fs::path&, string_view)

   // Misc
   METALMOCK_VOID1_CONST(DeleteFolder, const fs::path&)
   METALMOCK_VOID2_CONST(DeleteFolderExceptForFile, const fs::path&, string_view)
   METALMOCK_VOID2_CONST(DeleteFoldersExceptForFile, const vector<fs::path>&, string_view)
   METALMOCK_VOID1_CONST(SetCurrentPath, const fs::path&)
};
