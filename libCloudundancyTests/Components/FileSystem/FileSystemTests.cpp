#include "pch.h"
#include "libCloudundancy/Components/FileSystem/FileSystem.h"
#include "libCloudundancyTests/Components/Assertion/MetalMock/AsserterMock.h"
#include "libCloudundancyTests/Components/FileSystem/MetalMock/FileOpenerCloserMock.h"
#include "libCloudundancyTests/Components/Memory/MetalMock/CharVectorAllocatorMock.h"
#include "libCloudundancyTests/Components/FunctionCallers/MemberFunctions/MetalMock/NonVoidOneArgMemberFunctionCallerMock.h"
#include "libCloudundancyTests/Components/Time/MetalMock/StopwatchMock.h"

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
AFACT(ReadFileBytes_OpensFileInBinaryReadMode_FileSizeIs0_ClosesFile_ReturnsEmptyCharVector)
AFACT(ReadFileBytes_OpensFileInBinaryReadMode_FileSizeIsNot0_ReadsFileBytes_ClosesFile_ReturnsFileBytes)
AFACT(ReadFileLinesWhichMustBeNonEmpty_FileTextIsEmpty_ThrowsFileSystemException)
FACTS(ReadFileLinesWhichMustBeNonEmpty_FileTextIsNotEmpty_ReturnsFileTextSplitOnNewlines)
// File Copies
FACTS(IsFileSizeGreaterThanOrEqualTo2GB_FileSizeIsGreaterThanOrEqualTo2GB_ReturnsTrue)
FACTS(IsFileSizeGreaterThanOrEqualTo2GB_FileSizeIsLessThan2GB_ReturnsFalse)
AFACT(TryCopyFile_SourceFileIsNotEmpty_CreationOfParentFolderOfDestinationFilePathThrowsFilesystemError_ReturnsFalseFileCopyResult)
AFACT(TryCopyFile_SourceFileIsEmpty_CreationOfParentFolderOfDestinationFilePathSucceeds_CreatesEmptyDestinationFile_ReturnsCopySucceededFileCopyResult)
AFACT(TryCopyFile_SourceFileIsNotEmpty_CreationOfParentFolderOfDestinationFilePathSucceeds_WritesSourceFileBytesToDestinationFilePath_ReturnsCopySucceededFileCopyResult)
AFACT(TryCopyFileWithStdFilesystemCopyFile_CallsStdFilesystemCopyFile)
// File Writes
AFACT(WriteTextFile_CreatesDirectoriesLeadingUpToFilePath_CreatesFileInTextWriteMode_WritesFileTextToFile_ClosesFile)
// Misc
AFACT(DeleteFolder_CallsStdFileSystemRemoveAllOnFolderPath)
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

using _caller_ReadFileBytes_MockType = NonVoidOneArgMemberFunctionCallerMock<vector<char>, FileSystem, const fs::path&>;
_caller_ReadFileBytes_MockType* _caller_ReadFileBytesMock = nullptr;

using _caller_ReadFileText_MockType = NonVoidOneArgMemberFunctionCallerMock<string, FileSystem, const fs::path&>;
_caller_ReadFileText_MockType* _caller_ReadFileTextMock = nullptr;

// Constant Components
AsserterMock* _asserterMock = nullptr;
CharVectorAllocatorMock* _charVectorAllocatorMock = nullptr;
FileOpenerCloserMock* _fileOpenerCloserMock = nullptr;

// Mutable Fields
StopwatchMock* _stopwatchMock = nullptr;

struct fwriteCallHistory
{
   size_t numberOfCalls = 0;
   size_t returnValue_numberOfBytesWritten = 0;
   const void* sourceBytesArgument = nullptr;
   size_t elementSizeArgument = 0;
   size_t countArgument = 0;
   FILE* fileArgument = nullptr;

   size_t RecordFunctionCall(const void* sourceBytes, size_t elementSize, size_t count, FILE* file)
   {
      ++numberOfCalls;
      sourceBytesArgument = sourceBytes;
      elementSizeArgument = elementSize;
      countArgument = count;
      fileArgument = file;
      return returnValue_numberOfBytesWritten;
   }

   void AssertCalledOnceWith(size_t expectedElementSizeArgument, size_t expectedCountArgument, FILE* expectedFileArgument)
   {
      IS_NOT_NULLPTR(sourceBytesArgument);
      ARE_EQUAL(expectedElementSizeArgument, elementSizeArgument);
      ARE_EQUAL(expectedCountArgument, countArgument);
      ARE_EQUAL(expectedFileArgument, fileArgument);
   }
} _fwriteCallHistory;

size_t fwriteCallInstead(const void* sourceBytesArgument, size_t elementSizeArgument, size_t countArgument, FILE* fileArgument)
{
   const size_t numberOfBytesWritten = _fwriteCallHistory.RecordFunctionCall(
      sourceBytesArgument, elementSizeArgument, countArgument, fileArgument);
   return numberOfBytesWritten;
}

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
   FILE readModeTextFilePointer;
   _fileOpenerCloserMock->OpenTextFileInReadModeMock.Return(&readModeTextFilePointer);

   _caller_FileSizeMock->CallConstMemberFunctionMock.Return(0);

   _fileOpenerCloserMock->CloseFileMock.Expect();

   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const string fileText = _fileSystem.ReadFileText(filePath);
   //
   METALMOCK(_fileOpenerCloserMock->OpenTextFileInReadModeMock.CalledOnceWith(filePath));
   METALMOCK(_caller_FileSizeMock->CallConstMemberFunctionMock.CalledOnceWith(
      &FileSystem::FileSize, &_fileSystem, &readModeTextFilePointer));
   METALMOCK(_fileOpenerCloserMock->CloseFileMock.CalledOnceWith(&readModeTextFilePointer));
   ARE_EQUAL("", fileText);
}

TEST(ReadFileText_OpensFileInTextReadMode_FileSizeIsNot0_ReadsFileText_ClosesFile_ReturnsFileBytes)
{
   FILE readModeTextFilePointer;
   _fileOpenerCloserMock->OpenTextFileInReadModeMock.Return(&readModeTextFilePointer);

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
   METALMOCK(_fileOpenerCloserMock->OpenTextFileInReadModeMock.CalledOnceWith(filePath));
   METALMOCK(_caller_FileSizeMock->CallConstMemberFunctionMock.CalledOnceWith(
      &FileSystem::FileSize, &_fileSystem, &readModeTextFilePointer));
   METALMOCK(_charVectorAllocatorMock->NewCharVectorMock.CalledOnceWith(fileSizeInBytes));
   METALMOCK(freadMock.CalledOnceWith(expected0thTextBufferByte, 1, fileSizeInBytes, &readModeTextFilePointer));
   METALMOCK(_fileOpenerCloserMock->CloseFileMock.CalledOnceWith(&readModeTextFilePointer));
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

TEST(ReadFileBytes_OpensFileInBinaryReadMode_FileSizeIs0_ClosesFile_ReturnsEmptyCharVector)
{
   FILE readModeBinaryFilePointer;
   _fileOpenerCloserMock->OpenBinaryFileInReadModeMock.Return(&readModeBinaryFilePointer);

   _caller_FileSizeMock->CallConstMemberFunctionMock.Return(0);

   _fileOpenerCloserMock->CloseFileMock.Expect();

   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const vector<char> fileBytes = _fileSystem.ReadFileBytes(filePath);
   //
   METALMOCK(_fileOpenerCloserMock->OpenBinaryFileInReadModeMock.CalledOnceWith(filePath));
   METALMOCK(_caller_FileSizeMock->CallConstMemberFunctionMock.CalledOnceWith(
      &FileSystem::FileSize, &_fileSystem, &readModeBinaryFilePointer));
   METALMOCK(_fileOpenerCloserMock->CloseFileMock.CalledOnceWith(&readModeBinaryFilePointer));
   IS_EMPTY(fileBytes);
}

TEST(ReadFileBytes_OpensFileInBinaryReadMode_FileSizeIsNot0_ReadsFileBytes_ClosesFile_ReturnsFileBytes)
{
   FILE readModeBinaryFilePointer;
   _fileOpenerCloserMock->OpenBinaryFileInReadModeMock.Return(&readModeBinaryFilePointer);

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
   const vector<char> fileBytes = _fileSystem.ReadFileBytes(filePath);
   //
   METALMOCK(_fileOpenerCloserMock->OpenBinaryFileInReadModeMock.CalledOnceWith(filePath));
   METALMOCK(_caller_FileSizeMock->CallConstMemberFunctionMock.CalledOnceWith(
      &FileSystem::FileSize, &_fileSystem, &readModeBinaryFilePointer));
   METALMOCK(_charVectorAllocatorMock->NewCharVectorMock.CalledOnceWith(fileSizeInBytes));
   METALMOCK(freadMock.CalledOnceWith(expected0thBytesBufferByte, 1, fileSizeInBytes, &readModeBinaryFilePointer));
   METALMOCK(_fileOpenerCloserMock->CloseFileMock.CalledOnceWith(&readModeBinaryFilePointer));
   METALMOCK(_asserterMock->ThrowIfSizeTsNotEqualMock.CalledOnceWith(fileSizeInBytes, numberOfBytesRead,
      "fread() in FileSystem::ReadBytes() unexpectedly did not return fileSizeInBytes"));
   const vector<char> expectedFileBytes(fileSizeInBytes);
   VECTORS_ARE_EQUAL(expectedFileBytes, fileBytes);
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

TEST(TryCopyFile_SourceFileIsNotEmpty_CreationOfParentFolderOfDestinationFilePathThrowsFilesystemError_ReturnsFalseFileCopyResult)
{
   _stopwatchMock->StartMock.Expect();

   const vector<char> sourceFileBytes = ZenUnit::RandomNonEmptyVector<char>();
   _caller_ReadFileBytesMock->CallConstMemberFunctionMock.Return(sourceFileBytes);

   const string exceptionMessage = ZenUnit::Random<string>();
   const error_code errorCode = ZenUnit::Random<error_code>();
   create_directoriesMock.ThrowExceptionWhenCalled<fs::filesystem_error>(exceptionMessage, errorCode);

   const unsigned long long elapsedMilliseconds = _stopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();

   const fs::path sourceFilePath = ZenUnit::Random<fs::path>();
   const fs::path destinationFilePath = ZenUnit::Random<fs::path>();
   //
   const FileCopyResult fileCopyResult = _fileSystem.TryCopyFile(sourceFilePath, destinationFilePath);
   //
   METALMOCK(_stopwatchMock->StartMock.CalledOnce());
   METALMOCK(_caller_ReadFileBytesMock->CallConstMemberFunctionMock.CalledOnceWith(
      &FileSystem::ReadFileBytes, &_fileSystem, sourceFilePath));
   const fs::path expectedParentPathOfDestinationFilePath = destinationFilePath.parent_path();
   METALMOCK(create_directoriesMock.CalledOnceWith(expectedParentPathOfDestinationFilePath));
   METALMOCK(_stopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce());
   FileCopyResult expectedReturnValue;
   expectedReturnValue.copySucceeded = false;
   expectedReturnValue.sourceFilePath = sourceFilePath;
   expectedReturnValue.destinationFilePath = destinationFilePath;
   const fs::filesystem_error expectedException(exceptionMessage, errorCode);
   const char* const expectedExceptionMessage = expectedException.what();
   expectedReturnValue.copyFailureReason = expectedExceptionMessage;
   expectedReturnValue.durationInMilliseconds = elapsedMilliseconds;
   ARE_EQUAL(expectedReturnValue, fileCopyResult);
}

TEST(TryCopyFile_SourceFileIsEmpty_CreationOfParentFolderOfDestinationFilePathSucceeds_CreatesEmptyDestinationFile_ReturnsCopySucceededFileCopyResult)
{
   _stopwatchMock->StartMock.Expect();

   const vector<char> emptySourceFileBytes;
   _caller_ReadFileBytesMock->CallConstMemberFunctionMock.Return(emptySourceFileBytes);

   create_directoriesMock.ReturnRandom();

   FILE writeModeDestinationBinaryFilePointer;
   _fileOpenerCloserMock->CreateBinaryFileInWriteModeMock.Return(&writeModeDestinationBinaryFilePointer);

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
   METALMOCK(_fileOpenerCloserMock->CreateBinaryFileInWriteModeMock.CalledOnceWith(destinationFilePath));
   METALMOCK(_asserterMock->ThrowIfSizeTsNotEqualMock.CalledOnceWith(
      0, _fwriteCallHistory.returnValue_numberOfBytesWritten,
      "fwrite() in FileSystem::TryCopyFile(const fs::path& sourceFilePath, const fs::path& destinationFilePath) unexpectedly returned numberOfBytesWritten != sourceFileBytesSize"));
   METALMOCK(_fileOpenerCloserMock->CloseFileMock.CalledOnceWith(&writeModeDestinationBinaryFilePointer));
   METALMOCK(_stopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce());
   FileCopyResult expectedReturnValue;
   expectedReturnValue.copySucceeded = true;
   expectedReturnValue.sourceFilePath = sourceFilePath;
   expectedReturnValue.destinationFilePath = destinationFilePath;
   expectedReturnValue.durationInMilliseconds = elapsedMilliseconds;
   ARE_EQUAL(expectedReturnValue, fileCopyResult);
}

TEST(TryCopyFile_SourceFileIsNotEmpty_CreationOfParentFolderOfDestinationFilePathSucceeds_WritesSourceFileBytesToDestinationFilePath_ReturnsCopySucceededFileCopyResult)
{
   _stopwatchMock->StartMock.Expect();

   const vector<char> sourceFileBytes = ZenUnit::RandomNonEmptyVector<char>();
   _caller_ReadFileBytesMock->CallConstMemberFunctionMock.Return(sourceFileBytes);

   create_directoriesMock.ReturnRandom();

   FILE writeModeDestinationBinaryFilePointer;
   _fileOpenerCloserMock->CreateBinaryFileInWriteModeMock.Return(&writeModeDestinationBinaryFilePointer);

   _asserterMock->ThrowIfSizeTsNotEqualMock.Expect();

   _fileOpenerCloserMock->CloseFileMock.Expect();

   _fwriteCallHistory.returnValue_numberOfBytesWritten = ZenUnit::Random<size_t>();
   fwriteMock.CallInstead(std::bind(&FileSystemTests::fwriteCallInstead, this,
      std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));

   const unsigned long long elapsedMilliseconds = _stopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();

   const fs::path sourceFilePath = ZenUnit::Random<fs::path>();
   const fs::path destinationFilePath = ZenUnit::Random<fs::path>();
   //
   const FileCopyResult fileCopyResult = _fileSystem.TryCopyFile(sourceFilePath, destinationFilePath);
   //
   const size_t expectedSourceFileBytesSize = sourceFileBytes.size();
   METALMOCK(_stopwatchMock->StartMock.CalledOnce());
   METALMOCK(_caller_ReadFileBytesMock->CallConstMemberFunctionMock.CalledOnceWith(
      &FileSystem::ReadFileBytes, &_fileSystem, sourceFilePath));
   const fs::path expectedParentPathOfDestinationFilePath = destinationFilePath.parent_path();
   METALMOCK(create_directoriesMock.CalledOnceWith(expectedParentPathOfDestinationFilePath));
   METALMOCK(_fileOpenerCloserMock->CreateBinaryFileInWriteModeMock.CalledOnceWith(destinationFilePath));
   _fwriteCallHistory.AssertCalledOnceWith(
      1, expectedSourceFileBytesSize, &writeModeDestinationBinaryFilePointer);
   METALMOCK(_asserterMock->ThrowIfSizeTsNotEqualMock.CalledOnceWith(
      expectedSourceFileBytesSize, _fwriteCallHistory.returnValue_numberOfBytesWritten,
      "fwrite() in FileSystem::TryCopyFile(const fs::path& sourceFilePath, const fs::path& destinationFilePath) unexpectedly returned numberOfBytesWritten != sourceFileBytesSize"));
   METALMOCK(_fileOpenerCloserMock->CloseFileMock.CalledOnceWith(&writeModeDestinationBinaryFilePointer));
   METALMOCK(_stopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce());
   FileCopyResult expectedReturnValue;
   expectedReturnValue.sourceFilePath = sourceFilePath;
   expectedReturnValue.destinationFilePath = destinationFilePath;
   expectedReturnValue.copySucceeded = true;
   expectedReturnValue.durationInMilliseconds = elapsedMilliseconds;
   ARE_EQUAL(expectedReturnValue, fileCopyResult);
}

TEST(TryCopyFileWithStdFilesystemCopyFile_CallsStdFilesystemCopyFile)
{
   _stopwatchMock->StartMock.Expect();
   const unsigned long long elapsedMilliseconds = _stopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();
   const bool copyFileReturnValue = copy_fileMock.ReturnRandom();
   const fs::path sourceFilePath = ZenUnit::Random<fs::path>();
   const fs::path destinationFilePath = ZenUnit::Random<fs::path>();
   //
   const FileCopyResult fileCopyResult =
      _fileSystem.TryCopyFileWithStdFilesystemCopyFile(sourceFilePath, destinationFilePath);
   //
   METALMOCK(_stopwatchMock->StartMock.CalledOnce());
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

TEST(WriteTextFile_CreatesDirectoriesLeadingUpToFilePath_CreatesFileInTextWriteMode_WritesFileTextToFile_ClosesFile)
{
   create_directoriesMock.ReturnRandom();

   FILE writeModeTextFilePointer{};
   _fileOpenerCloserMock->CreateTextFileInWriteModeMock.Return(&writeModeTextFilePointer);

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
   METALMOCK(_fileOpenerCloserMock->CreateTextFileInWriteModeMock.CalledOnceWith(filePath));
   METALMOCK(fwriteMock.CalledOnceWith(fileText.data(), 1, fileText.size(), &writeModeTextFilePointer));
   METALMOCK(_asserterMock->ThrowIfSizeTsNotEqualMock.CalledOnceWith(fileText.size(), numberOfBytesWritten,
      "fwrite() in FileSystem::CreateTextFile() unexpectedly did not return fileText.size() number of bytes written"));
   METALMOCK(_fileOpenerCloserMock->CloseFileMock.CalledOnceWith(&writeModeTextFilePointer));
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
