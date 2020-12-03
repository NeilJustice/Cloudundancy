#include "pch.h"
#include "libCloudundancy/UtilityComponents/FileSystem/FileSystem.h"
#include "libCloudundancyTests/UtilityComponents/Assertion/MetalMock/AsserterMock.h"
#include "libCloudundancyTests/UtilityComponents/FileSystem/MetalMock/FileOpenerCloserMock.h"
#include "libCloudundancyTests/UtilityComponents/Memory/MetalMock/CharVectorAllocatorMock.h"
#include "libCloudundancyTests/UtilityComponents/FunctionCallers/MemberFunctions/MetalMock/NonVoidOneArgMemberFunctionCallerMock.h"
#include "libCloudundancyTests/UtilityComponents/Time/MetalMock/StopwatchMock.h"
#include "libCloudundancyTests/UtilityComponents/Time/MetalMock/WatchMock.h"

TESTS(FileSystemTests)
#ifdef __linux__
AFACT(GetLinuxErrno_ReturnsAddressOfGlobalErrnoVariable)
#endif
AFACT(DefaultConstructor_SetsFunctionPointers_NewsComponents)
// File Or Folder Existence Checks
AFACT(FileOrFolderExists_ReturnsResultOfCallingStdFileSystemExists)
AFACT(ThrowIfFilePathIsNotEmptyAndDoesNotExist_FilePathIsEmpty_DoesNothing)
AFACT(ThrowIfFilePathIsNotEmptyAndDoesNotExist_FilePathIsNotEmpty_FilePathExists_DoesNothing)
AFACT(ThrowIfFilePathIsNotEmptyAndDoesNotExist_FilePathIsNotEmpty_FilePathDoesNotExist_ThrowsFileSystemException)
// File Reads
AFACT(ReadFileText_OpensFileInTextReadMode_FileSizeIs0_ClosesFile_ReturnsEmptyCharVector)
AFACT(ReadFileText_OpensFileInTextReadMode_FileSizeIsNot0_ReadsFileText_ClosesFile_ReturnsFileBytes)
AFACT(ReadFileBytes_OpensFileInBinaryReadMode_FileSizeIs0_ClosesFile_ReturnsSharedPtrToEmptyCharVector)
AFACT(ReadFileBytes_OpensFileInBinaryReadMode_FileSizeIsNot0_ReadsFileBytes_ClosesFile_ReturnsSharedPtrToFileBytes)
AFACT(ReadFileLinesWhichMustBeNonEmpty_FileTextIsEmpty_ThrowsFileSystemException)
FACTS(ReadFileLinesWhichMustBeNonEmpty_FileTextIsNotEmpty_ReturnsFileTextSplitOnNewlines)
// File Copies
FACTS(IsFileSizeGreaterThanOrEqualTo2GB_FileSizeIsGreaterThanOrEqualTo2GB_ReturnsTrue)
FACTS(IsFileSizeGreaterThanOrEqualTo2GB_FileSizeIsLessThan2GB_ReturnsFalse)
AFACT(TryCopyFile_SourceFileIsEmpty_CreatesParentFoldersForDestinationFile_CreatesEmptyDestinationFile_ReturnsCopySucceededFileCopyResult)
AFACT(TryCopyFile_SourceFileIsNotEmpty_CreatesParentFoldersForDestinationFile_WritesSourceFileBytesToDestinationFilePath_ReturnsCopySucceededFileCopyResult)
AFACT(TryCopyFileWithStdFilesystemCopyFile_CreatesParentFoldersForDestinationFile_CopiesSourceFileToDestinationFileByCallingStdFilesystemCopyFile)
// File Writes
AFACT(AppendText_CreatesParentDirectoryToFilePath_AppendsTimestampedTextToFile)
AFACT(WriteTextFile_CreatesParentDirectoryToFilePath_CreatesFileInTextWriteMode_WritesFileTextToFile_ClosesFile)
// Misc
AFACT(DeleteFolder_CallsStdFileSystemRemoveAllOnFolderPath)
AFACT(DeleteFolders_CallsStdFileSystemRemoveAllOnEachFolderPath)
AFACT(SetCurrentPath_CallsFsCurrentPathWithFolderPath)
// Private Functions
AFACT(FileSize_CallsFSeekEndThenFTellToDetermineSizeOfFileInBytes)
EVIDENCE

FileSystem _fileSystem;
// C File Function Pointers
METALMOCK_NONVOID0_FREE(int*, errno)
METALMOCK_NONVOID4_FREE(size_t, fread, void*, size_t, size_t, FILE*)
METALMOCK_NONVOID3_FREE(int, fseek, FILE*, long, int)
METALMOCK_NONVOID1_FREE(long, ftell, FILE*)
METALMOCK_NONVOID4_FREE(size_t, fwrite, const void*, size_t, size_t, FILE*)
// std::filesystem Function Pointers
METALMOCK_NONVOID3_NAMESPACED_FREE(bool, std::filesystem, copy_file, const fs::path&, const fs::path&, fs::copy_options)
METALMOCK_VOID1_NAMESPACED_FREE(std::filesystem, current_path, const fs::path&)
METALMOCK_NONVOID1_NAMESPACED_FREE(bool, std::filesystem, create_directories, const fs::path&)
METALMOCK_NONVOID1_NAMESPACED_FREE(bool, std::filesystem, exists, const fs::path&)
METALMOCK_NONVOID1_NAMESPACED_FREE(size_t, std::filesystem, file_size, const fs::path&)
METALMOCK_NONVOID1_NAMESPACED_FREE(uintmax_t, std::filesytem, remove_all, const fs::path&)
// Function Callers
using _caller_FileSize_MockType = NonVoidOneArgMemberFunctionCallerMock<size_t, FileSystem, FILE*>;
_caller_FileSize_MockType* _caller_FileSizeMock = nullptr;

using _caller_ReadFileBytes_MockType = NonVoidOneArgMemberFunctionCallerMock<shared_ptr<const vector<char>>, FileSystem, const fs::path&>;
_caller_ReadFileBytes_MockType* _caller_ReadFileBytesMock = nullptr;

using _caller_ReadFileText_MockType = NonVoidOneArgMemberFunctionCallerMock<string, FileSystem, const fs::path&>;
_caller_ReadFileText_MockType* _caller_ReadFileTextMock = nullptr;

// Constant Components
AsserterMock* _asserterMock = nullptr;
CharVectorAllocatorMock* _charVectorAllocatorMock = nullptr;
FileOpenerCloserMock* _fileOpenerCloserMock = nullptr;

// Mutable Fields
StopwatchMock* _stopwatchMock = nullptr;

STARTUP
{
   // C File Function Pointers
   _fileSystem._call_errno = BIND_0ARG_METALMOCK_OBJECT(errnoMock);
   _fileSystem._call_fread = BIND_4ARG_METALMOCK_OBJECT(freadMock);
   _fileSystem._call_fseek = BIND_3ARG_METALMOCK_OBJECT(fseekMock);
   _fileSystem._call_ftell = BIND_1ARG_METALMOCK_OBJECT(ftellMock);
   _fileSystem._call_fwrite = BIND_4ARG_METALMOCK_OBJECT(fwriteMock);
   // std::filesystem Function Pointers
   _fileSystem._call_fs_copy_file = BIND_3ARG_METALMOCK_OBJECT(copy_fileMock);
   _fileSystem._call_fs_current_path = BIND_1ARG_METALMOCK_OBJECT(current_pathMock);
   _fileSystem._call_fs_create_directories = BIND_1ARG_METALMOCK_OBJECT(create_directoriesMock);
   _fileSystem._call_fs_file_size = BIND_1ARG_METALMOCK_OBJECT(file_sizeMock);
   _fileSystem._call_fs_remove_all = BIND_1ARG_METALMOCK_OBJECT(remove_allMock);
   _fileSystem._call_fs_exists = BIND_1ARG_METALMOCK_OBJECT(existsMock);
   // Function Callers
   _fileSystem._caller_ReadFileBytes.reset(_caller_ReadFileBytesMock = new _caller_ReadFileBytes_MockType);
   _fileSystem._caller_FileSize.reset(_caller_FileSizeMock = new _caller_FileSize_MockType);
   _fileSystem._caller_ReadFileText.reset(_caller_ReadFileTextMock = new _caller_ReadFileText_MockType);
   // Constant Components
   _fileSystem._asserter.reset(_asserterMock = new AsserterMock);
   _fileSystem._charVectorAllocator.reset(_charVectorAllocatorMock = new CharVectorAllocatorMock);
   _fileSystem._fileOpenerCloser.reset(_fileOpenerCloserMock = new FileOpenerCloserMock);
   // Mutable Components
   _fileSystem._stopwatch.reset(_stopwatchMock = new StopwatchMock);
}

#ifdef __linux__
TEST(GetLinuxErrno_ReturnsAddressOfGlobalErrnoVariable)
{
   int* errnoPointer = GetLinuxErrno();
   ARE_EQUAL(&errno, errnoPointer);
}
#endif

TEST(DefaultConstructor_SetsFunctionPointers_NewsComponents)
{
   FileSystem fileSystem;
   // C File Function Pointers
#ifdef __linux__
   STD_FUNCTION_TARGETS(GetLinuxErrno, fileSystem._call_errno);
#elif _WIN32
   STD_FUNCTION_TARGETS(::_errno, fileSystem._call_errno);
#endif
   STD_FUNCTION_TARGETS(::fread, fileSystem._call_fread);
   STD_FUNCTION_TARGETS(::fseek, fileSystem._call_fseek);
   STD_FUNCTION_TARGETS(::ftell, fileSystem._call_ftell);
   STD_FUNCTION_TARGETS(::fwrite, fileSystem._call_fwrite);
   // std::filesystem Function Pointers
#ifdef _WIN32
   STD_FUNCTION_TARGETS_OVERLOAD(FileSystem::CopyFileOverloadType, fs::copy_file, fileSystem._call_fs_copy_file);
   STD_FUNCTION_TARGETS_OVERLOAD(FileSystem::CurrentPathOverloadType, fs::current_path, fileSystem._call_fs_current_path);
   STD_FUNCTION_TARGETS_OVERLOAD(FileSystem::CreateDirectoriesOverloadType, fs::create_directories, fileSystem._call_fs_create_directories);
   STD_FUNCTION_TARGETS_OVERLOAD(FileSystem::ExistsOverloadType, fs::exists, fileSystem._call_fs_exists);
   STD_FUNCTION_TARGETS_OVERLOAD(FileSystem::FileSizeOverloadType, fs::file_size, fileSystem._call_fs_file_size);
   STD_FUNCTION_TARGETS_OVERLOAD(FileSystem::RemoveAllOverloadType, fs::remove_all, fileSystem._call_fs_remove_all);
#endif
   // Function Callers
   DELETE_TO_ASSERT_NEWED(fileSystem._caller_FileSize);
   DELETE_TO_ASSERT_NEWED(fileSystem._caller_ReadFileBytes);
   DELETE_TO_ASSERT_NEWED(fileSystem._caller_ReadFileText);
   // Constant Components
   DELETE_TO_ASSERT_NEWED(fileSystem._asserter);
   DELETE_TO_ASSERT_NEWED(fileSystem._charVectorAllocator);
   DELETE_TO_ASSERT_NEWED(fileSystem._fileOpenerCloser);
   // Mutable Components
   DELETE_TO_ASSERT_NEWED(fileSystem._stopwatch);
}

// File Or Folder Existence Checks

TEST(FileOrFolderExists_ReturnsResultOfCallingStdFileSystemExists)
{
   const bool fileOrFolderExists = existsMock.ReturnRandom();
   const fs::path fileOrFolderPath = ZenUnit::Random<fs::path>();
   //
   const bool returnedFileOrFolderExists = _fileSystem.FileOrFolderExists(fileOrFolderPath);
   //
   METALMOCK(existsMock.CalledOnceWith(fileOrFolderPath));
   ARE_EQUAL(fileOrFolderExists, returnedFileOrFolderExists);
}

TEST(ThrowIfFilePathIsNotEmptyAndDoesNotExist_FilePathIsEmpty_DoesNothing)
{
   const fs::path emptyFilePath;
   _fileSystem.ThrowIfFilePathIsNotEmptyAndDoesNotExist(emptyFilePath);
}

TEST(ThrowIfFilePathIsNotEmptyAndDoesNotExist_FilePathIsNotEmpty_FilePathExists_DoesNothing)
{
   existsMock.Return(true);
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   _fileSystem.ThrowIfFilePathIsNotEmptyAndDoesNotExist(filePath);
   //
   METALMOCK(existsMock.CalledOnceWith(filePath));
}

TEST(ThrowIfFilePathIsNotEmptyAndDoesNotExist_FilePathIsNotEmpty_FilePathDoesNotExist_ThrowsFileSystemException)
{
   existsMock.Return(false);
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   FileSystemException expectedException(FileSystemExceptionType::FileDoesNotExist, filePath);
   THROWS_EXCEPTION(_fileSystem.ThrowIfFilePathIsNotEmptyAndDoesNotExist(filePath),
      FileSystemException, expectedException.what());
   //
   METALMOCK(existsMock.CalledOnceWith(filePath));
}

// File Reads

TEST(ReadFileText_OpensFileInTextReadMode_FileSizeIs0_ClosesFile_ReturnsEmptyCharVector)
{
   FILE readModeTextFileHandle;
   _fileOpenerCloserMock->OpenReadModeTextFileMock.Return(&readModeTextFileHandle);

   _caller_FileSizeMock->CallConstMemberFunctionMock.Return(0);

   _fileOpenerCloserMock->CloseFileMock.Expect();

   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const string fileText = _fileSystem.ReadFileText(filePath);
   //
   METALMOCK(_fileOpenerCloserMock->OpenReadModeTextFileMock.CalledOnceWith(filePath));
   METALMOCK(_caller_FileSizeMock->CallConstMemberFunctionMock.CalledOnceWith(
      &FileSystem::FileSize, &_fileSystem, &readModeTextFileHandle));
   METALMOCK(_fileOpenerCloserMock->CloseFileMock.CalledOnceWith(&readModeTextFileHandle));
   ARE_EQUAL("", fileText);
}

TEST(ReadFileText_OpensFileInTextReadMode_FileSizeIsNot0_ReadsFileText_ClosesFile_ReturnsFileBytes)
{
   FILE readModeTextFileHandle;
   _fileOpenerCloserMock->OpenReadModeTextFileMock.Return(&readModeTextFileHandle);

   const size_t fileSizeInBytes = ZenUnit::RandomBetween<size_t>(1, 3);
   _caller_FileSizeMock->CallConstMemberFunctionMock.Return(fileSizeInBytes);

   vector<char>* fileTextBuffer = new vector<char>(fileSizeInBytes);
   _charVectorAllocatorMock->NewCharVectorMock.Return(fileTextBuffer);
   char* const expected0thTextBufferByte = &(*fileTextBuffer)[0];
   const string expectedFileText(&(*fileTextBuffer)[0]);

   _fileOpenerCloserMock->CloseFileMock.Expect();

   freadMock.ReturnRandom();

   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const string fileText = _fileSystem.ReadFileText(filePath);
   //
   METALMOCK(_fileOpenerCloserMock->OpenReadModeTextFileMock.CalledOnceWith(filePath));
   METALMOCK(_caller_FileSizeMock->CallConstMemberFunctionMock.CalledOnceWith(
      &FileSystem::FileSize, &_fileSystem, &readModeTextFileHandle));
   METALMOCK(_charVectorAllocatorMock->NewCharVectorMock.CalledOnceWith(fileSizeInBytes));
   METALMOCK(freadMock.CalledOnceWith(expected0thTextBufferByte, 1, fileSizeInBytes, &readModeTextFileHandle));
   METALMOCK(_fileOpenerCloserMock->CloseFileMock.CalledOnceWith(&readModeTextFileHandle));
   ARE_EQUAL(expectedFileText, fileText);
}

TEST(ReadFileLinesWhichMustBeNonEmpty_FileTextIsEmpty_ThrowsFileSystemException)
{
   _caller_ReadFileTextMock->CallConstMemberFunctionMock.Return("");
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   FileSystemException expectedFileSystemException(FileSystemExceptionType::FileCannotBeEmpty, filePath);
   THROWS_EXCEPTION(_fileSystem.ReadFileLinesWhichMustBeNonEmpty(filePath),
      FileSystemException, expectedFileSystemException.what());
   //
   METALMOCK(_caller_ReadFileTextMock->CallConstMemberFunctionMock.CalledOnceWith(
      &FileSystem::ReadFileText, &_fileSystem, filePath));
}

TEST2X2(ReadFileLinesWhichMustBeNonEmpty_FileTextIsNotEmpty_ReturnsFileTextSplitOnNewlines,
   string_view fileText, const vector<string>& expectedReturnValue,
   " ", vector<string>{ " " },
   "Line1\nLine2\nLine3", vector<string>{ "Line1", "Line2", "Line3" },
   "Line1\n\n\n", vector<string>{ "Line1", "", "" })
{
   _caller_ReadFileTextMock->CallConstMemberFunctionMock.Return(fileText);
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const vector<string> fileLines = _fileSystem.ReadFileLinesWhichMustBeNonEmpty(filePath);
   //
   METALMOCK(_caller_ReadFileTextMock->CallConstMemberFunctionMock.CalledOnceWith(
      &FileSystem::ReadFileText, &_fileSystem, filePath));
   VECTORS_ARE_EQUAL(expectedReturnValue, fileLines);
}

TEST(ReadFileBytes_OpensFileInBinaryReadMode_FileSizeIs0_ClosesFile_ReturnsSharedPtrToEmptyCharVector)
{
   FILE readModeBinaryFileHandle;
   _fileOpenerCloserMock->OpenReadModeBinaryFileMock.Return(&readModeBinaryFileHandle);

   _caller_FileSizeMock->CallConstMemberFunctionMock.Return(0);

   _fileOpenerCloserMock->CloseFileMock.Expect();

   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const shared_ptr<const vector<char>> fileBytes = _fileSystem.ReadFileBytes(filePath);
   //
   METALMOCK(_fileOpenerCloserMock->OpenReadModeBinaryFileMock.CalledOnceWith(filePath));
   METALMOCK(_caller_FileSizeMock->CallConstMemberFunctionMock.CalledOnceWith(
      &FileSystem::FileSize, &_fileSystem, &readModeBinaryFileHandle));
   METALMOCK(_fileOpenerCloserMock->CloseFileMock.CalledOnceWith(&readModeBinaryFileHandle));
   IS_EMPTY(*fileBytes);
}

TEST(ReadFileBytes_OpensFileInBinaryReadMode_FileSizeIsNot0_ReadsFileBytes_ClosesFile_ReturnsSharedPtrToFileBytes)
{
   FILE readModeBinaryFileHandle;
   _fileOpenerCloserMock->OpenReadModeBinaryFileMock.Return(&readModeBinaryFileHandle);

   const size_t fileSizeInBytes = ZenUnit::RandomBetween<size_t>(1, 3);
   _caller_FileSizeMock->CallConstMemberFunctionMock.Return(fileSizeInBytes);

   vector<char>* fileBytesBuffer = new vector<char>(fileSizeInBytes);
   _charVectorAllocatorMock->NewCharVectorMock.Return(fileBytesBuffer);
   char* const expected0thBytesBufferByte = &(*fileBytesBuffer)[0];

   _fileOpenerCloserMock->CloseFileMock.Expect();

   _asserterMock->ThrowIfSizeTsNotEqualMock.Expect();

   const size_t numberOfBytesRead = freadMock.ReturnRandom();

   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const shared_ptr<const vector<char>> fileBytes = _fileSystem.ReadFileBytes(filePath);
   //
   METALMOCK(_fileOpenerCloserMock->OpenReadModeBinaryFileMock.CalledOnceWith(filePath));
   METALMOCK(_caller_FileSizeMock->CallConstMemberFunctionMock.CalledOnceWith(
      &FileSystem::FileSize, &_fileSystem, &readModeBinaryFileHandle));
   METALMOCK(_charVectorAllocatorMock->NewCharVectorMock.CalledOnceWith(fileSizeInBytes));
   METALMOCK(freadMock.CalledOnceWith(expected0thBytesBufferByte, 1, fileSizeInBytes, &readModeBinaryFileHandle));
   METALMOCK(_fileOpenerCloserMock->CloseFileMock.CalledOnceWith(&readModeBinaryFileHandle));
   METALMOCK(_asserterMock->ThrowIfSizeTsNotEqualMock.CalledOnceWith(fileSizeInBytes, numberOfBytesRead,
      "fread() in FileSystem::ReadBytes() unexpectedly did not return fileSizeInBytes"));
   const vector<char> expectedFileBytes(fileSizeInBytes);
   VECTORS_ARE_EQUAL(expectedFileBytes, *fileBytes);
}

// File Copies

TEST1X1(IsFileSizeGreaterThanOrEqualTo2GB_FileSizeIsGreaterThanOrEqualTo2GB_ReturnsTrue,
   size_t fileSize,
   2ull * 1024ull * 1024ull * 1024ull,
   2ull * 1024ull * 1024ull * 1024ull + 1,
   2ull * 1024ull * 1024ull * 1024ull + 2,
   10ull * 1024ull * 1024ull * 1024ull)
{
   file_sizeMock.Return(fileSize);
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const bool isFileSizeGreaterThanOrEqualTo2GB = _fileSystem.IsFileSizeGreaterThanOrEqualTo2GB(filePath);
   //
   METALMOCK(file_sizeMock.CalledOnceWith(filePath));
   IS_TRUE(isFileSizeGreaterThanOrEqualTo2GB);
}

TEST1X1(IsFileSizeGreaterThanOrEqualTo2GB_FileSizeIsLessThan2GB_ReturnsFalse,
   size_t fileSize,
   0ull,
   1ull,
   2ull * 1024ull * 1024ull * 1024ull - 2,
   2ull * 1024ull * 1024ull * 1024ull - 1)
{
   file_sizeMock.Return(fileSize);
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const bool isFileSizeGreaterThanOrEqualTo2GB = _fileSystem.IsFileSizeGreaterThanOrEqualTo2GB(filePath);
   //
   METALMOCK(file_sizeMock.CalledOnceWith(filePath));
   IS_FALSE(isFileSizeGreaterThanOrEqualTo2GB);
}

TEST(TryCopyFile_SourceFileIsEmpty_CreatesParentFoldersForDestinationFile_CreatesEmptyDestinationFile_ReturnsCopySucceededFileCopyResult)
{
   _stopwatchMock->StartMock.Expect();

   const shared_ptr<const vector<char>> emptySourceFileBytes = make_shared<vector<char>>(vector<char>{});
   _caller_ReadFileBytesMock->CallConstMemberFunctionMock.Return(emptySourceFileBytes);

   create_directoriesMock.ReturnRandom();

   FILE writeModeDestinationBinaryFileHandle;
   _fileOpenerCloserMock->CreateWriteModeBinaryFileMock.Return(&writeModeDestinationBinaryFileHandle);

   _asserterMock->ThrowIfSizeTsNotEqualMock.Expect();

   _fileOpenerCloserMock->CloseFileMock.Expect();

   const unsigned long long elapsedMilliseconds = _stopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();

   const fs::path sourceFilePath = ZenUnit::Random<fs::path>();
   const fs::path destinationFilePath = ZenUnit::Random<fs::path>();
   //
   const FileCopyResult fileCopyResult = _fileSystem.TryCopyFile(sourceFilePath, destinationFilePath);
   //
   const fs::path expectedParentPathOfDestinationFilePath = destinationFilePath.parent_path();
   METALMOCK(_stopwatchMock->StartMock.CalledOnce());
   METALMOCK(create_directoriesMock.CalledOnceWith(expectedParentPathOfDestinationFilePath));
   METALMOCK(_caller_ReadFileBytesMock->CallConstMemberFunctionMock.CalledOnceWith(
      &FileSystem::ReadFileBytes, &_fileSystem, sourceFilePath));
   METALMOCK(_fileOpenerCloserMock->CreateWriteModeBinaryFileMock.CalledOnceWith(destinationFilePath));
   METALMOCK(_asserterMock->ThrowIfSizeTsNotEqualMock.CalledOnceWith(0, 0,
      "fwrite() in FileSystem::TryCopyFile(const fs::path& sourceFilePath, const fs::path& destinationFilePath) unexpectedly returned numberOfBytesWritten != sourceFileBytesSize"));
   METALMOCK(_fileOpenerCloserMock->CloseFileMock.CalledOnceWith(&writeModeDestinationBinaryFileHandle));
   METALMOCK(_stopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce());
   FileCopyResult expectedReturnValue;
   expectedReturnValue.copySucceeded = true;
   expectedReturnValue.sourceFilePath = sourceFilePath;
   expectedReturnValue.destinationFilePath = destinationFilePath;
   expectedReturnValue.durationInMilliseconds = elapsedMilliseconds;
   ARE_EQUAL(expectedReturnValue, fileCopyResult);
}

TEST(TryCopyFile_SourceFileIsNotEmpty_CreatesParentFoldersForDestinationFile_WritesSourceFileBytesToDestinationFilePath_ReturnsCopySucceededFileCopyResult)
{
   _stopwatchMock->StartMock.Expect();

   const shared_ptr<const vector<char>> sourceFileBytes = make_shared<vector<char>>(ZenUnit::RandomNonEmptyVector<char>());
   _caller_ReadFileBytesMock->CallConstMemberFunctionMock.Return(sourceFileBytes);

   create_directoriesMock.ReturnRandom();

   FILE writeModeDestinationBinaryFileHandle;
   _fileOpenerCloserMock->CreateWriteModeBinaryFileMock.Return(&writeModeDestinationBinaryFileHandle);

   _asserterMock->ThrowIfSizeTsNotEqualMock.Expect();

   _fileOpenerCloserMock->CloseFileMock.Expect();

   const size_t numberOfBytesWritten = fwriteMock.ReturnRandom();

   const unsigned long long elapsedMilliseconds = _stopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();

   const fs::path sourceFilePath = ZenUnit::Random<fs::path>();
   const fs::path destinationFilePath = ZenUnit::Random<fs::path>();
   //
   const FileCopyResult fileCopyResult = _fileSystem.TryCopyFile(sourceFilePath, destinationFilePath);
   //
   const size_t expectedSourceFileBytesSize = sourceFileBytes->size();
   METALMOCK(_stopwatchMock->StartMock.CalledOnce());
   METALMOCK(_caller_ReadFileBytesMock->CallConstMemberFunctionMock.CalledOnceWith(
      &FileSystem::ReadFileBytes, &_fileSystem, sourceFilePath));
   const fs::path expectedParentPathOfDestinationFilePath = destinationFilePath.parent_path();
   METALMOCK(create_directoriesMock.CalledOnceWith(expectedParentPathOfDestinationFilePath));
   METALMOCK(_fileOpenerCloserMock->CreateWriteModeBinaryFileMock.CalledOnceWith(destinationFilePath));
   METALMOCK(fwriteMock.CalledOnceWith(sourceFileBytes->data(), 1, expectedSourceFileBytesSize, &writeModeDestinationBinaryFileHandle));
   METALMOCK(_asserterMock->ThrowIfSizeTsNotEqualMock.CalledOnceWith(expectedSourceFileBytesSize, numberOfBytesWritten,
      "fwrite() in FileSystem::TryCopyFile(const fs::path& sourceFilePath, const fs::path& destinationFilePath) unexpectedly returned numberOfBytesWritten != sourceFileBytesSize"));
   METALMOCK(_fileOpenerCloserMock->CloseFileMock.CalledOnceWith(&writeModeDestinationBinaryFileHandle));
   METALMOCK(_stopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce());
   FileCopyResult expectedReturnValue;
   expectedReturnValue.sourceFilePath = sourceFilePath;
   expectedReturnValue.destinationFilePath = destinationFilePath;
   expectedReturnValue.copySucceeded = true;
   expectedReturnValue.durationInMilliseconds = elapsedMilliseconds;
   ARE_EQUAL(expectedReturnValue, fileCopyResult);
}

TEST(TryCopyFileWithStdFilesystemCopyFile_CreatesParentFoldersForDestinationFile_CopiesSourceFileToDestinationFileByCallingStdFilesystemCopyFile)
{
   _stopwatchMock->StartMock.Expect();
   create_directoriesMock.ReturnRandom();
   const unsigned long long elapsedMilliseconds = _stopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();
   const bool copyFileReturnValue = copy_fileMock.ReturnRandom();

   const fs::path sourceFilePath = ZenUnit::Random<fs::path>();
   const fs::path destinationFilePath = ZenUnit::Random<fs::path>();
   //
   const FileCopyResult fileCopyResult =
      _fileSystem.TryCopyFileWithStdFilesystemCopyFile(sourceFilePath, destinationFilePath);
   //
   const fs::path expectedParentPathOfDestinationFilePath = destinationFilePath.parent_path();
   METALMOCK(_stopwatchMock->StartMock.CalledOnce());
   METALMOCK(create_directoriesMock.CalledOnceWith(expectedParentPathOfDestinationFilePath));
   METALMOCK(copy_fileMock.CalledOnceWith(sourceFilePath, destinationFilePath, fs::copy_options::overwrite_existing));
   METALMOCK(_stopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce());
   FileCopyResult expectedFileCopyResult;
   expectedFileCopyResult.sourceFilePath = sourceFilePath;
   expectedFileCopyResult.destinationFilePath = destinationFilePath;
   expectedFileCopyResult.copySucceeded = copyFileReturnValue;
   expectedFileCopyResult.durationInMilliseconds = elapsedMilliseconds;
   ARE_EQUAL(expectedFileCopyResult, fileCopyResult);
}

// File Writes

TEST(AppendText_CreatesParentDirectoryToFilePath_AppendsTimestampedTextToFile)
{
   create_directoriesMock.ReturnRandom();

   FILE appendModeTextFileHandle{};
   _fileOpenerCloserMock->OpenAppendModeTextFileMock.Return(&appendModeTextFileHandle);

   _fileOpenerCloserMock->CloseFileMock.Expect();

   const size_t numberOfBytesWritten = fwriteMock.ReturnRandom();

   _asserterMock->ThrowIfSizeTsNotEqualMock.Expect();

   const fs::path filePath = ZenUnit::Random<fs::path>();
   const string text = ZenUnit::Random<string>();
   //
   _fileSystem.AppendText(filePath, text);
   //
   const fs::path expectedParentFolderPath = filePath.parent_path();
   METALMOCK(create_directoriesMock.CalledOnceWith(expectedParentFolderPath));
   METALMOCK(_fileOpenerCloserMock->OpenAppendModeTextFileMock.CalledOnceWith(filePath));
   const size_t expectedTextSize = text.size();
   METALMOCK(fwriteMock.CalledOnceWith(text.data(), 1, expectedTextSize, &appendModeTextFileHandle));
   METALMOCK(_asserterMock->ThrowIfSizeTsNotEqualMock.CalledOnceWith(expectedTextSize, numberOfBytesWritten,
      "fwrite(text.data(), 1, textSize, appendModeTextFileHandle) unexpectedly did not return textSize"));
   METALMOCK(_fileOpenerCloserMock->CloseFileMock.CalledOnceWith(&appendModeTextFileHandle));
}

TEST(WriteTextFile_CreatesParentDirectoryToFilePath_CreatesFileInTextWriteMode_WritesFileTextToFile_ClosesFile)
{
   create_directoriesMock.ReturnRandom();

   FILE writeModeTextFileHandle{};
   _fileOpenerCloserMock->CreateWriteModeTextFileMock.Return(&writeModeTextFileHandle);

   const size_t numberOfBytesWritten = fwriteMock.ReturnRandom();

   _asserterMock->ThrowIfSizeTsNotEqualMock.Expect();

   _fileOpenerCloserMock->CloseFileMock.Expect();

   const fs::path filePath = ZenUnit::Random<fs::path>();
   const string fileText = ZenUnit::Random<string>();
   //
   _fileSystem.WriteTextFile(filePath, fileText);
   //
   const fs::path expectedParentFolderPath = filePath.parent_path();
   METALMOCK(create_directoriesMock.CalledOnceWith(expectedParentFolderPath));
   METALMOCK(_fileOpenerCloserMock->CreateWriteModeTextFileMock.CalledOnceWith(filePath));
   METALMOCK(fwriteMock.CalledOnceWith(fileText.data(), 1, fileText.size(), &writeModeTextFileHandle));
   METALMOCK(_asserterMock->ThrowIfSizeTsNotEqualMock.CalledOnceWith(fileText.size(), numberOfBytesWritten,
      "fwrite() in FileSystem::CreateTextFile() unexpectedly did not return fileText.size() number of bytes written"));
   METALMOCK(_fileOpenerCloserMock->CloseFileMock.CalledOnceWith(&writeModeTextFileHandle));
}

// Misc

TEST(DeleteFolder_CallsStdFileSystemRemoveAllOnFolderPath)
{
   remove_allMock.ReturnRandom();
   const fs::path folderPath = ZenUnit::Random<fs::path>();
   //
   _fileSystem.DeleteFolder(folderPath);
   //
   METALMOCK(remove_allMock.CalledOnceWith(folderPath));
}

TEST(DeleteFolders_CallsStdFileSystemRemoveAllOnEachFolderPath)
{
   remove_allMock.ReturnRandom();
   const vector<fs::path>& folderPaths =
   {
      ZenUnit::Random<fs::path>(),
      ZenUnit::Random<fs::path>(),
      ZenUnit::Random<fs::path>()
   };
   //
   _fileSystem.DeleteFolders(folderPaths);
   //
   METALMOCK(remove_allMock.CalledAsFollows(
   {
      { folderPaths[0] },
      { folderPaths[1] },
      { folderPaths[2] }
   }));
}

TEST(SetCurrentPath_CallsFsCurrentPathWithFolderPath)
{
   current_pathMock.Expect();
   const fs::path folderPath = ZenUnit::Random<fs::path>();
   //
   _fileSystem.SetCurrentPath(folderPath);
   //
   METALMOCK(current_pathMock.CalledOnceWith(folderPath));
}

// Private Functions

TEST(FileSize_CallsFSeekEndThenFTellToDetermineSizeOfFileInBytes)
{
   const int fseekEndReturnValue = ZenUnit::Random<int>();
   const int fseekSetReturnValue = ZenUnit::Random<int>();
   fseekMock.ReturnValues(fseekEndReturnValue, fseekSetReturnValue);

   _asserterMock->ThrowIfIntsNotEqualMock.Expect();

   const long ftellReturnValue = ftellMock.ReturnRandom();

   FILE filePointer{};
   //
   const size_t fileSizeInBytes = _fileSystem.FileSize(&filePointer);
   //
   METALMOCK(fseekMock.CalledAsFollows(
   {
      { &filePointer, 0, SEEK_END },
      { &filePointer, 0, SEEK_SET }
   }));
   METALMOCK(_asserterMock->ThrowIfIntsNotEqualMock.CalledAsFollows(
   {
      { 0, fseekEndReturnValue, "fseek(filePointer, 0, SEEK_END) in FileSystem::FileSize() unexpectedly did not return 0" },
      { 0, fseekSetReturnValue, "fseek(filePointer, 0, SEEK_SET) in FileSystem::FileSize() unexpectedly did not return 0" }
   }));
   METALMOCK(ftellMock.CalledOnceWith(&filePointer));
   ARE_EQUAL(static_cast<size_t>(ftellReturnValue), fileSizeInBytes);
}

RUN_TESTS(FileSystemTests)
