#include "pch.h"
#include "libCloudundancy/Components/FileSystem/FileSystemPather.h"

TESTS(FileSystemPatherTests)
AFACT(DefaultConstructor_SetsFunctionPointers)

// Exceptions
AFACT(ThrowIfFileDoesNotExist_FileExists_DoesNothing)
AFACT(ThrowIfFileDoesNotExist_FileDoesNotExist_ThrowsFileDoesNotExistException)

// File and Folder Paths
AFACT(GetAbsoluteFileOrFolderPath_IsEmptyPath_ReturnsEmptyPath)
AFACT(GetAbsoluteFileOrFolderPath_IsNotEmptyPath_ReturnsResultOfCallingFilesystemAbsoluteOnFileOrFolderPath)
EVIDENCE

Utils::FileSystemPather _fileSystemPather;
// Function Pointers
METALMOCK_NONVOID1_STATIC_OR_FREE(fs::path, _call_fs_absolute, const fs::path&)
METALMOCK_NONVOID1_STATIC_OR_FREE(bool, _call_fs_is_regular_file, const fs::path&)

STARTUP
{
   // Function Pointers
   _fileSystemPather._call_fs_absolute = BIND_1ARG_METALMOCK_OBJECT(_call_fs_absoluteMock);
   _fileSystemPather._call_fs_is_regular_file = BIND_1ARG_METALMOCK_OBJECT(_call_fs_is_regular_fileMock);
}

TEST(DefaultConstructor_SetsFunctionPointers)
{
   const Utils::FileSystemPather fileSystemPather;
   // Function Pointers
#ifdef _WIN32
   STD_FUNCTION_TARGETS_OVERLOAD(Utils::FileSystemPather::fs_absolute_function_overload_type,
      fs::absolute, fileSystemPather._call_fs_absolute);

   STD_FUNCTION_TARGETS_OVERLOAD(Utils::FileSystemPather::IsRegularFileOverloadType,
      fs::is_regular_file, fileSystemPather._call_fs_is_regular_file);
#endif
}

// Exceptions

TEST(ThrowIfFileDoesNotExist_FileExists_DoesNothing)
{
   _call_fs_is_regular_fileMock.Return(true);
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   _fileSystemPather.ThrowIfFileDoesNotExist(filePath);
   //
   METALMOCK(_call_fs_is_regular_fileMock.CalledOnceWith(filePath));
}

TEST(ThrowIfFileDoesNotExist_FileDoesNotExist_ThrowsFileDoesNotExistException)
{
   _call_fs_is_regular_fileMock.Return(false);
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const string expectedExceptionMessage = filePath.string();
   THROWS_EXCEPTION(_fileSystemPather.ThrowIfFileDoesNotExist(filePath),
      Utils::FileNotFoundException, expectedExceptionMessage);
   //
   METALMOCK(_call_fs_is_regular_fileMock.CalledOnceWith(filePath));
}

// File and Folder Paths

TEST(GetAbsoluteFileOrFolderPath_IsEmptyPath_ReturnsEmptyPath)
{
   const fs::path emptyFileOrFolderPath;
   //
   const fs::path& returnedAbsoluteFileOrFolderPath = _fileSystemPather.GetAbsoluteFileOrFolderPath(emptyFileOrFolderPath);
   //
   IS_EMPTY_PATH(returnedAbsoluteFileOrFolderPath);
}

TEST(GetAbsoluteFileOrFolderPath_IsNotEmptyPath_ReturnsResultOfCallingFilesystemAbsoluteOnFileOrFolderPath)
{
   const fs::path absoluteFileOrFolderPath = _call_fs_absoluteMock.ReturnRandom();
   const fs::path fileOrFolderPath = ZenUnit::Random<string>();
   //
   const fs::path& returnedAbsoluteFileOrFolderPath = _fileSystemPather.GetAbsoluteFileOrFolderPath(fileOrFolderPath);
   //
   METALMOCK(_call_fs_absoluteMock.CalledOnceWith(fileOrFolderPath));
   ARE_EQUAL(absoluteFileOrFolderPath, returnedAbsoluteFileOrFolderPath);
}

RUN_TESTS(FileSystemPatherTests)
