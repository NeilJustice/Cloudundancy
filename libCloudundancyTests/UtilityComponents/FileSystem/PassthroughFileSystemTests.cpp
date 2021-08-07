#include "pch.h"
#include "libCloudundancy/UtilityComponents/FileSystem/PassthroughFileSystem.h"
#include <fstream>

TESTS(PassthroughFileSystemTests)
AFACT(remove_all_DeletesFolder)
AFACT(file_size_ReturnsSizeOfFileInBytes)
EVIDENCE

PassthroughFileSystem _passthroughFileSystem;

TEST(remove_all_DeletesFolder)
{
   const fs::path folderPath = "remove_all_test_folder";
   fs::create_directory(folderPath);
   IS_TRUE(fs::exists(folderPath));
   //
   _passthroughFileSystem.remove_all(folderPath);
   //
   IS_FALSE(fs::exists(folderPath));
}

TEST(file_size_ReturnsSizeOfFileInBytes)
{
   const fs::path filePath = "file_size_test_file.txt";
   ofstream f(filePath.c_str());
   IS_TRUE(f.is_open());
   f << 0 << 0 << 0;
   f.close();
   //
   const unsigned long long fileSize = _passthroughFileSystem.file_size(filePath);
   //
   fs::remove(filePath);
   ARE_EQUAL(3, fileSize);
}

RUN_TESTS(PassthroughFileSystemTests)
