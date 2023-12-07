#include "pch.h"
#include "libCloudundancy/Exceptions/FileSystemExceptions.h"
#include "libCloudundancyTests/UtilityComponents/Assertion/MetalMock/AsserterMock.h"
#include "libCloudundancyTests/UtilityComponents/ErrorHandling/MetalMock/ErrorCodeTranslatorMock.h"
#include "libCloudundancyTests/UtilityComponents/FileSystem/MetalMock/FileSystemMock.h"
#include "libCloudundancyTests/UtilityComponents/FileSystem/MetalMock/PassthroughFileSystemMock.h"
#include "libCloudundancyTests/UtilityComponents/FunctionCallers/Member/MetalMock/NonVoidOneArgMemberFunctionCallerMock.h"
#include "libCloudundancyTests/UtilityComponents/FunctionCallers/Member/MetalMock/NonVoidTwoArgMemberFunctionCallerMock.h"
#include "libCloudundancyTests/UtilityComponents/FunctionCallers/Member/MetalMock/VoidOneArgMemberFunctionCallerMock.h"
#include "libCloudundancyTests/UtilityComponents/FunctionCallers/Member/MetalMock/VoidTwoArgMemberFunctionCallerMock.h"
#include "libCloudundancyTests/UtilityComponents/Memory/MetalMock/CharVectorAllocatorMock.h"
#include "libCloudundancyTests/UtilityComponents/Time/MetalMock/StopwatchFactoryMock.h"
#include "libCloudundancyTests/UtilityComponents/Time/MetalMock/StopwatchMock.h"

TESTS(FileSystemTests)
AFACT(DefaultConstructor_NewsComponents_SetsFunctionPointers)
// File Open Functions
#if defined __linux__
AFACT(Linux__CreateFileInBinaryWriteMode_ReturnsSharedFilePointerCreatedWithFileOpenMode_wb)
AFACT(Linux__CreateOrOpenFileInBinaryAppendMode_ReturnsSharedFilePointerCreatedWithFileOpenMode_ab)
AFACT(Linux__OpenFileInBinaryReadMode_ReturnsSharedPtrFromCallingCreateOrOpenFileOnLinux)
AFACT(Linux__OpenFileInTextReadMode_ReturnsSharedPtrFromCallingCreateOrOpenFileOnLinux)
#elif defined _WIN32
AFACT(Windows__CreateFileInBinaryWriteMode_ReturnsSharedFilePointerCreatedWithFileOpenMode_wb)
AFACT(Windows__CreateOrOpenFileInBinaryAppendMode_ReturnsSharedFilePointerCreatedWithFileOpenMode_ab)
AFACT(Windows__OpenFileInBinaryReadMode_ReturnsSharedPtrFromCallingCreateOrOpenFileOnWindows)
AFACT(Windows__OpenFileInTextReadMode_ReturnsSharedPtrFromCallingCreateOrOpenFileOnLinux)
#endif
// Behavior Functions
AFACT(AppendTextToClosedFile_OpensFileInBinaryAppendMode_AppendsText_ImplicitlyClosesFile)
AFACT(CloseFile_fcloseReturnValueIsNot0_ThrowsRuntimeError)
AFACT(CloseFile_fcloseReturnValueIs0_Returns)
AFACT(CopyFileToFile_SourceFileIsNotEmpty_CreatesParentFoldersForDestinationFile_WritesSourceFileBytesToDestinationFilePath_ReturnsCopySucceededFileCopyResult)
AFACT(CopyFileToFileLargerThan2GB_CreatesParentFoldersForDestinationFile_CopiesSourceFileToDestinationFileByCallingStdFilesystemCopyFileToFile)
AFACT(CreateTextFileIfDoesNotExist_FileExists_DoesNothing)
AFACT(CreateTextFileIfDoesNotExist_FileDoesNotExist_CreateFileWithFileText)
AFACT(DeleteFolder_CallsTestableFileSystemremove_all)
AFACT(FileOrFolderExists_ReturnsResultOfCallingStdFileSystemExists)
AFACT(ReadFileBytes_OpensFileInBinaryReadMode_FileSizeIs0_ClosesFile_ReturnsSharedPtrToEmptyCharVector)
AFACT(ReadFileBytes_OpensFileInBinaryReadMode_FileSizeIsNot0_ReadsFileBytes_ClosesFile_ReturnsSharedPtrToFileBytes)
AFACT(ReadFileText_ReadsFileSizeWhichReturns0_ClosesFile_ReturnsEmptyString)
AFACT(ReadFileText_ReadsFileSizeWhichReturnsGreaterThan0_ReadsFileBytesIntoString_ClosesFile_ReturnsFileTextString)
AFACT(ReadFileLinesWhichMustBeNonEmpty_FileTextIsEmpty_ThrowsFileSystemException)
FACTS(ReadFileLinesWhichMustBeNonEmpty_FileTextIsNotEmpty_ReturnsFileTextSplitOnNewlines)
AFACT(SetCurrentPath_CallsFSCurrentPathWithFolderPath)
AFACT(ThrowIfFilePathIsNotEmptyPathAndFileDoesNotExist_FilePathIsEmpty_DoesNothing)
AFACT(ThrowIfFilePathIsNotEmptyPathAndFileDoesNotExist_FilePathIsNotEmpty_FilePathExists_DoesNothing)
AFACT(ThrowIfFilePathIsNotEmptyPathAndFileDoesNotExist_FilePathIsNotEmpty_FilePathDoesNotExist_ThrowsFileSystemException)
AFACT(WriteTextToOpenFile_CallsFWriteOnFilePointerWithText_CallsFFlushOnFilePointer)
AFACT(WriteBytesToOpenFile_CallsFWriteOnFilePointerWithBytes_CallsFFlushOnFilePointer)
// Private Functions
#if defined __linux__
AFACT(Linux__CreateOrOpenFileOnLinux_CreatesParentDirectoriesForFilePath_fopenReturnsNonNullptr_ReturnsOpenedFilePointer)
AFACT(Linux__CreateOrOpenFileOnLinux_CreatesParentDirectoriesForFilePath_fopenReturnsNullptr_ThrowsRuntimeError)
#elif defined _WIN32
AFACT(Windows__CreateOrOpenFileOnWindows_CreatesParentDirectoriesForFilePath_CallswfsopenWhichReturnsNonNullptr_ReturnsOpenedFilePointer)
AFACT(Windows__CreateOrOpenFileOnWindows_CreatesParentDirectoriesForFilePath_CallswfsopenWhichReturnsNullptr_ThrowsRuntimeError)
#endif
AFACT(ReadFileSize_CallsFSeekEndThenFTellToDetermineSizeOfFileInBytes)
EVIDENCE

Utils::FileSystem _fileSystem;
// C Function Pointers
METALMOCK_NONVOID1_STATIC_OR_FREE(int, _call_fclose, FILE*)
METALMOCK_NONVOID1_STATIC_OR_FREE(int, _call_fflush, FILE*)
METALMOCK_NONVOID4_STATIC_OR_FREE(size_t, _call_fread, void*, size_t, size_t, FILE*)
METALMOCK_NONVOID3_STATIC_OR_FREE(int, _call_fseek, FILE*, long, int)
METALMOCK_NONVOID1_STATIC_OR_FREE(long, _call_ftell, FILE*)
#if defined __linux__
METALMOCK_NONVOID2_STATIC_OR_FREE(FILE*, _call_fopen, const char*, const char*)
#elif defined _WIN32
METALMOCK_NONVOID3_STATIC_OR_FREE(FILE*, _call_wfsopen, const wchar_t*, const wchar_t*, int)
#endif
METALMOCK_NONVOID4_STATIC_OR_FREE(size_t, _call_fwrite, const void*, size_t, size_t, FILE*)
// std::filesystem Function Pointers
METALMOCK_NONVOID3_STATIC_OR_FREE(bool, _call_fs_copy_file, const fs::path&, const fs::path&, fs::copy_options)
METALMOCK_NONVOID1_STATIC_OR_FREE(bool, _call_fs_create_directories, const fs::path&)
METALMOCK_VOID1_STATIC_OR_FREE(_call_fs_current_path, const fs::path&)
METALMOCK_NONVOID1_STATIC_OR_FREE(bool, _call_fs_exists, const fs::path&)

// Function Callers
using _caller_CreateOrOpenFileFunctionMockType = Utils::NonVoidOneArgMemberFunctionCallerMock<shared_ptr<FILE>, Utils::FileSystem, const fs::path&>;
_caller_CreateOrOpenFileFunctionMockType* _caller_CreateOrOpenFileFunctionMock = nullptr;

using _caller_ReadFileBytesMockType = Utils::NonVoidOneArgMemberFunctionCallerMock<shared_ptr<const vector<char>>, Utils::FileSystem, const fs::path&>;
_caller_ReadFileBytesMockType* _caller_ReadFileBytesMock = nullptr;

using _caller_ReadFileSizeMockType = Utils::NonVoidOneArgMemberFunctionCallerMock<size_t, Utils::FileSystem, const shared_ptr<FILE>&>;
_caller_ReadFileSizeMockType* _caller_ReadFileSizeMock = nullptr;

using _caller_ReadFileTextMockType = Utils::NonVoidOneArgMemberFunctionCallerMock<string, Utils::FileSystem, const fs::path&>;
_caller_ReadFileTextMockType* _caller_ReadFileTextMock = nullptr;

using _caller_WriteTextToOpenFileMockType = Utils::VoidTwoArgMemberFunctionCallerMock<Utils::FileSystem, const shared_ptr<FILE>&, string_view>;
_caller_WriteTextToOpenFileMockType* _caller_WriteTextToOpenFileMock = nullptr;

#if defined __linux__
using _caller_CreateOrOpenFileOnLinuxMockType = Utils::NonVoidTwoArgMemberFunctionCallerMock<shared_ptr<FILE>, Utils::FileSystem, const fs::path&, const char*>;
_caller_CreateOrOpenFileOnLinuxMockType* _caller_CreateOrOpenFileOnLinuxMock = nullptr;
#elif defined _WIN32
using _caller_CreateOrOpenFileOnWindowsMockType = Utils::NonVoidTwoArgMemberFunctionCallerMock<shared_ptr<FILE>, Utils::FileSystem, const fs::path&, const wchar_t*>;
_caller_CreateOrOpenFileOnWindowsMockType* _caller_CreateOrOpenFileOnWindowsMock = nullptr;
#endif

// Constant Components
Utils::AsserterMock* _asserterMock = nullptr;
Utils::CharVectorAllocatorMock* _charVectorAllocatorMock = nullptr;
Utils::ErrorCodeTranslatorMock* _errorCodeTranslatorMock = nullptr;
PassthroughFileSystemMock* _passthroughFileSystemMock = nullptr;
Utils::StopwatchFactoryMock* _stopwatchFactoryMock = nullptr;

STARTUP
{
   // C Function Pointers
   _fileSystem._call_fclose = BIND_1ARG_METALMOCK_OBJECT(_call_fcloseMock);
   _fileSystem._call_fflush = BIND_1ARG_METALMOCK_OBJECT(_call_fflushMock);
   _fileSystem._call_fread = BIND_4ARG_METALMOCK_OBJECT(_call_freadMock);
   _fileSystem._call_fseek = BIND_3ARG_METALMOCK_OBJECT(_call_fseekMock);
   _fileSystem._call_ftell = BIND_1ARG_METALMOCK_OBJECT(_call_ftellMock);
   _fileSystem._call_fwrite = BIND_4ARG_METALMOCK_OBJECT(_call_fwriteMock);
#if defined __linux__
   _fileSystem._call_fopen = BIND_2ARG_METALMOCK_OBJECT(_call_fopenMock);
#elif defined _WIN32
   _fileSystem._call_wfsopen = BIND_3ARG_METALMOCK_OBJECT(_call_wfsopenMock);
#endif
   // std::filesystem Function Pointers
   _fileSystem._call_fs_copy_file = BIND_3ARG_METALMOCK_OBJECT(_call_fs_copy_fileMock);
   _fileSystem._call_fs_create_directories = BIND_1ARG_METALMOCK_OBJECT(_call_fs_create_directoriesMock);
   _fileSystem._call_fs_current_path = BIND_1ARG_METALMOCK_OBJECT(_call_fs_current_pathMock);
   _fileSystem._call_fs_exists = BIND_1ARG_METALMOCK_OBJECT(_call_fs_existsMock);
   // Function Callers
   _fileSystem._caller_CreateOrOpenFileFunction.reset(_caller_CreateOrOpenFileFunctionMock = new _caller_CreateOrOpenFileFunctionMockType);
   _fileSystem._caller_ReadFileBytes.reset(_caller_ReadFileBytesMock = new _caller_ReadFileBytesMockType);
   _fileSystem._caller_ReadFileSize.reset(_caller_ReadFileSizeMock = new _caller_ReadFileSizeMockType);
   _fileSystem._caller_ReadFileText.reset(_caller_ReadFileTextMock = new _caller_ReadFileTextMockType);
#if defined __linux__
   _fileSystem._caller_CreateOrOpenFileOnLinux.reset(_caller_CreateOrOpenFileOnLinuxMock = new _caller_CreateOrOpenFileOnLinuxMockType);
#elif defined _WIN32
   _fileSystem._caller_CreateOrOpenFileOnWindows.reset(_caller_CreateOrOpenFileOnWindowsMock = new _caller_CreateOrOpenFileOnWindowsMockType);
#endif
   _fileSystem._caller_WriteTextToOpenFile.reset(_caller_WriteTextToOpenFileMock = new _caller_WriteTextToOpenFileMockType);
   // Constant Components
   _fileSystem._asserter.reset(_asserterMock = new Utils::AsserterMock);
   _fileSystem._charVectorAllocator.reset(_charVectorAllocatorMock = new Utils::CharVectorAllocatorMock);
   _fileSystem._errorCodeTranslator.reset(_errorCodeTranslatorMock = new Utils::ErrorCodeTranslatorMock);
   _fileSystem._passthroughFileSystem.reset(_passthroughFileSystemMock = new PassthroughFileSystemMock);
   _fileSystem._stopwatchFactory.reset(_stopwatchFactoryMock = new Utils::StopwatchFactoryMock);
}

TEST(DefaultConstructor_NewsComponents_SetsFunctionPointers)
{
   Utils::FileSystem fileSystem;
   // C Function Pointers
   STD_FUNCTION_TARGETS(fclose, fileSystem._call_fclose);
   STD_FUNCTION_TARGETS(fflush, fileSystem._call_fflush);
   STD_FUNCTION_TARGETS(fread, fileSystem._call_fread);
   STD_FUNCTION_TARGETS(fseek, fileSystem._call_fseek);
   STD_FUNCTION_TARGETS(ftell, fileSystem._call_ftell);
   STD_FUNCTION_TARGETS(fwrite, fileSystem._call_fwrite);
#if defined __linux__
   STD_FUNCTION_TARGETS(fopen, fileSystem._call_fopen);
#elif defined _WIN32
   STD_FUNCTION_TARGETS(_wfsopen, fileSystem._call_wfsopen);
#endif
   // std::filesystem Function Pointers
#if defined _WIN32
   STD_FUNCTION_TARGETS_OVERLOAD(Utils::FileSystem::fs_copy_file_FunctionOverloadType, fs::copy_file, fileSystem._call_fs_copy_file);
   STD_FUNCTION_TARGETS_OVERLOAD(Utils::FileSystem::fs_create_directories_FunctionOverloadType, fs::create_directories, fileSystem._call_fs_create_directories);
   STD_FUNCTION_TARGETS_OVERLOAD(Utils::FileSystem::fs_current_path_FunctionOverloadType, fs::current_path, fileSystem._call_fs_current_path);
   STD_FUNCTION_TARGETS_OVERLOAD(Utils::FileSystem::fs_exists_FunctionOverloadType, fs::exists, fileSystem._call_fs_exists);
#endif
   // Function Callers
   DELETE_TO_ASSERT_NEWED(fileSystem._caller_CreateOrOpenFileFunction);
   DELETE_TO_ASSERT_NEWED(fileSystem._caller_ReadFileBytes);
   DELETE_TO_ASSERT_NEWED(fileSystem._caller_ReadFileSize);
   DELETE_TO_ASSERT_NEWED(fileSystem._caller_WriteTextToOpenFile);
#if defined __linux__
   DELETE_TO_ASSERT_NEWED(fileSystem._caller_CreateOrOpenFileOnLinux);
#elif defined _WIN32
   DELETE_TO_ASSERT_NEWED(fileSystem._caller_CreateOrOpenFileOnWindows);
#endif
   // Constant Components
   DELETE_TO_ASSERT_NEWED(fileSystem._asserter);
   DELETE_TO_ASSERT_NEWED(fileSystem._charVectorAllocator);
   DELETE_TO_ASSERT_NEWED(fileSystem._errorCodeTranslator);
   DELETE_TO_ASSERT_NEWED(fileSystem._passthroughFileSystem);
   DELETE_TO_ASSERT_NEWED(fileSystem._stopwatchFactory);
}

// File Open Functions

#if defined __linux__

TEST(Linux__CreateFileInBinaryWriteMode_ReturnsSharedFilePointerCreatedWithFileOpenMode_wb)
{
   const shared_ptr<FILE> binaryWriteModeFilePointer = make_shared<FILE>();
   _caller_CreateOrOpenFileOnLinuxMock->CallConstMemberFunctionMock.Return(binaryWriteModeFilePointer);
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const shared_ptr<FILE> returnedFilePointer = _fileSystem.CreateFileInBinaryWriteMode(filePath);
   //
   METALMOCK(_caller_CreateOrOpenFileOnLinuxMock->CallConstMemberFunctionMock.CalledOnceWith(
      &_fileSystem, &Utils::FileSystem::CreateOrOpenFileOnLinux, filePath, "wb"));
   ARE_EQUAL(binaryWriteModeFilePointer, returnedFilePointer);
}

TEST(Linux__CreateOrOpenFileInBinaryAppendMode_ReturnsSharedFilePointerCreatedWithFileOpenMode_ab)
{
   const shared_ptr<FILE> binaryAppendModeFilePointer = make_shared<FILE>();
   _caller_CreateOrOpenFileOnLinuxMock->CallConstMemberFunctionMock.Return(binaryAppendModeFilePointer);
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const shared_ptr<FILE> returnedFilePointer = _fileSystem.CreateOrOpenFileInBinaryAppendMode(filePath);
   //
   METALMOCK(_caller_CreateOrOpenFileOnLinuxMock->CallConstMemberFunctionMock.CalledOnceWith(
      &_fileSystem, &Utils::FileSystem::CreateOrOpenFileOnLinux, filePath, "ab"));
   ARE_EQUAL(binaryAppendModeFilePointer, returnedFilePointer);
}

struct fopen_CallHistory
{
   size_t numberOfCalls = 0;
   FILE* returnValue = nullptr;
   fs::path filePathArgument;
   const char* fileOpenModeArgument = nullptr;

   void RecordFunctionCall(const char* filePath, const char* fileOpenMode)
   {
      ++numberOfCalls;
      filePathArgument = filePath;
      fileOpenModeArgument = fileOpenMode;
   }

   void AssertCalledOnceWith(const fs::path& expectedFilePath, const char* expectedFileOpenMode) const
   {
      ARE_EQUAL(1, numberOfCalls);
      ARE_EQUAL(expectedFilePath, filePathArgument);
      ARE_EQUAL(expectedFileOpenMode, fileOpenModeArgument);
   }
} _fopen_CallHistory;

FILE* fopen_CallInsteadFunction(const char* filePath, const char* fileOpenMode)
{
   _fopen_CallHistory.RecordFunctionCall(filePath, fileOpenMode);
   return _fopen_CallHistory.returnValue;
}

TEST(Linux__OpenFileInBinaryReadMode_ReturnsSharedPtrFromCallingCreateOrOpenFileOnLinux)
{
   shared_ptr<FILE> binaryReadModeFilePointer = make_shared<FILE>();
   _caller_CreateOrOpenFileOnLinuxMock->CallConstMemberFunctionMock.Return(binaryReadModeFilePointer);
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const shared_ptr<FILE> returnedFilePointer = _fileSystem.OpenFileInBinaryReadMode(filePath);
   //
   METALMOCK(_caller_CreateOrOpenFileOnLinuxMock->CallConstMemberFunctionMock.CalledOnceWith(
      &_fileSystem, &Utils::FileSystem::CreateOrOpenFileOnLinux, filePath, "rb"));
   ARE_EQUAL(binaryReadModeFilePointer, returnedFilePointer);
}

TEST(Linux__OpenFileInTextReadMode_ReturnsSharedPtrFromCallingCreateOrOpenFileOnLinux)
{
   shared_ptr<FILE> textReadModeFilePointer = make_shared<FILE>();
   _caller_CreateOrOpenFileOnLinuxMock->CallConstMemberFunctionMock.Return(textReadModeFilePointer);
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const shared_ptr<FILE> returnedFilePointer = _fileSystem.OpenFileInTextReadMode(filePath);
   //
   METALMOCK(_caller_CreateOrOpenFileOnLinuxMock->CallConstMemberFunctionMock.CalledOnceWith(
      &_fileSystem, &Utils::FileSystem::CreateOrOpenFileOnLinux, filePath, "r"));
   ARE_EQUAL(textReadModeFilePointer, returnedFilePointer);
}

#elif defined _WIN32

TEST(Windows__CreateFileInBinaryWriteMode_ReturnsSharedFilePointerCreatedWithFileOpenMode_wb)
{
   const shared_ptr<FILE> binaryWriteModeFilePointer = make_shared<FILE>();
   _caller_CreateOrOpenFileOnWindowsMock->CallConstMemberFunctionMock.Return(binaryWriteModeFilePointer);
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const shared_ptr<FILE> returnedFilePointer = _fileSystem.CreateFileInBinaryWriteMode(filePath);
   //
   METALMOCK(_caller_CreateOrOpenFileOnWindowsMock->CallConstMemberFunctionMock.CalledOnceWith(
      &_fileSystem, &Utils::FileSystem::CreateOrOpenFileOnWindows, filePath, L"wb"));
   ARE_EQUAL(binaryWriteModeFilePointer, returnedFilePointer);
}

TEST(Windows__CreateOrOpenFileInBinaryAppendMode_ReturnsSharedFilePointerCreatedWithFileOpenMode_ab)
{
   const shared_ptr<FILE> binaryAppendModeFilePointer = make_shared<FILE>();
   _caller_CreateOrOpenFileOnWindowsMock->CallConstMemberFunctionMock.Return(binaryAppendModeFilePointer);
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const shared_ptr<FILE> returnedFilePointer = _fileSystem.CreateOrOpenFileInBinaryAppendMode(filePath);
   //
   METALMOCK(_caller_CreateOrOpenFileOnWindowsMock->CallConstMemberFunctionMock.CalledOnceWith(
      &_fileSystem, &Utils::FileSystem::CreateOrOpenFileOnWindows, filePath, L"ab"));
   ARE_EQUAL(binaryAppendModeFilePointer, returnedFilePointer);
}

TEST(Windows__OpenFileInBinaryReadMode_ReturnsSharedPtrFromCallingCreateOrOpenFileOnWindows)
{
   shared_ptr<FILE> binaryReadModeFilePointer = make_shared<FILE>();
   _caller_CreateOrOpenFileOnWindowsMock->CallConstMemberFunctionMock.Return(binaryReadModeFilePointer);
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const shared_ptr<FILE> returnedFilePointer = _fileSystem.OpenFileInBinaryReadMode(filePath);
   //
   METALMOCK(_caller_CreateOrOpenFileOnWindowsMock->CallConstMemberFunctionMock.CalledOnceWith(
      &_fileSystem, &Utils::FileSystem::CreateOrOpenFileOnWindows, filePath, L"rb"));
   ARE_EQUAL(binaryReadModeFilePointer, returnedFilePointer);
}

TEST(Windows__OpenFileInTextReadMode_ReturnsSharedPtrFromCallingCreateOrOpenFileOnLinux)
{
   shared_ptr<FILE> textReadModeFilePointer = make_shared<FILE>();
   _caller_CreateOrOpenFileOnWindowsMock->CallConstMemberFunctionMock.Return(textReadModeFilePointer);
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const shared_ptr<FILE> returnedFilePointer = _fileSystem.OpenFileInTextReadMode(filePath);
   //
   METALMOCK(_caller_CreateOrOpenFileOnWindowsMock->CallConstMemberFunctionMock.CalledOnceWith(
      &_fileSystem, &Utils::FileSystem::CreateOrOpenFileOnWindows, filePath, L"r"));
   ARE_EQUAL(textReadModeFilePointer, returnedFilePointer);
}

#endif

// Behavior Functions

TEST(AppendTextToClosedFile_OpensFileInBinaryAppendMode_AppendsText_ImplicitlyClosesFile)
{
   const shared_ptr<FILE> appendModeBinaryFilePointer = make_shared<FILE>();
   _caller_CreateOrOpenFileFunctionMock->CallConstMemberFunctionMock.Return(appendModeBinaryFilePointer);

   const size_t numberOfBytesAppended = _call_fwriteMock.ReturnRandom();

   _asserterMock->ThrowIfSizeTsNotEqualMock.Expect();

   const fs::path filePath = ZenUnit::Random<fs::path>();
   const string text = ZenUnit::Random<string>();
   //
   _fileSystem.AppendTextToClosedFile(filePath, text);
   //
   METALMOCKTHEN(_caller_CreateOrOpenFileFunctionMock->CallConstMemberFunctionMock.CalledOnceWith(&_fileSystem, &Utils::FileSystem::CreateOrOpenFileInBinaryAppendMode, filePath)).Then(
   METALMOCKTHEN(_call_fwriteMock.CalledOnceWith(text.data(), 1, text.size(), appendModeBinaryFilePointer.get()))).Then(
   METALMOCKTHEN(_asserterMock->ThrowIfSizeTsNotEqualMock.CalledOnceWith(text.size(), numberOfBytesAppended,
      "_call_fwrite(text.data(), 1, textSize, appendModeTextFileHandle) unexpectedly did not return textSize")));
}

TEST(CloseFile_fcloseReturnValueIs0_Returns)
{
   _call_fcloseMock.Return(0);
   const shared_ptr<FILE> filePointer = make_shared<FILE>();
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   _fileSystem.CloseFile(filePointer, filePath);
   //
   METALMOCK(_call_fcloseMock.CalledOnceWith(filePointer.get()));
}

TEST(CloseFile_fcloseReturnValueIsNot0_ThrowsRuntimeError)
{
   const int fcloseReturnValue = ZenUnit::RandomNon0<int>();
   _call_fcloseMock.Return(fcloseReturnValue);

   const pair<int, string> errnoWithDescription = _errorCodeTranslatorMock->GetErrnoWithDescriptionMock.ReturnRandom();

   const shared_ptr<FILE> filePointer = make_shared<FILE>();
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const string expectedExceptionMessage = Utils::String::ConcatValues(
      "fclose(filePointer) when closing file ", filePath.string(), " returned ", errnoWithDescription.first, ": ", errnoWithDescription.second);
   THROWS_EXCEPTION(_fileSystem.CloseFile(filePointer, filePath),
      runtime_error, expectedExceptionMessage);
   //
   METALMOCKTHEN(_call_fcloseMock.CalledOnceWith(filePointer.get())).Then(
   METALMOCKTHEN(_errorCodeTranslatorMock->GetErrnoWithDescriptionMock.CalledOnce()));
}

TEST(CopyFileToFile_SourceFileIsNotEmpty_CreatesParentFoldersForDestinationFile_WritesSourceFileBytesToDestinationFilePath_ReturnsCopySucceededFileCopyResult)
{
   const shared_ptr<Utils::StopwatchMock> stopwatchMock = make_shared<Utils::StopwatchMock>();
   _stopwatchFactoryMock->NewStopwatchMock.Return(stopwatchMock);
   stopwatchMock->StartMock.Expect();

   const shared_ptr<const vector<char>> sourceFileBytes = make_shared<vector<char>>(ZenUnit::RandomNonEmptyVector<char>());
   _caller_ReadFileBytesMock->CallConstMemberFunctionMock.Return(sourceFileBytes);

   _call_fs_create_directoriesMock.ReturnRandom();

   const shared_ptr<FILE> binaryWriteModeDestinationFilePointer = make_shared<FILE>();
   _caller_CreateOrOpenFileFunctionMock->CallConstMemberFunctionMock.Return(binaryWriteModeDestinationFilePointer);

   _asserterMock->ThrowIfSizeTsNotEqualMock.Expect();

   const size_t numberOfBytesWritten = _call_fwriteMock.ReturnRandom();

   const unsigned long long elapsedMilliseconds = stopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();

   const fs::path sourceFilePath = ZenUnit::Random<fs::path>();
   const fs::path destinationFilePath = ZenUnit::Random<fs::path>();
   //
   const Utils::FileCopyResult fileCopyResult = _fileSystem.CopyFileToFile(sourceFilePath, destinationFilePath);
   //
   const size_t expectedSourceFileBytesSize = sourceFileBytes->size();
   const fs::path expectedParentPathOfDestinationFilePath = destinationFilePath.parent_path();
   METALMOCKTHEN(_stopwatchFactoryMock->NewStopwatchMock.CalledOnce()).Then(

   METALMOCKTHEN(stopwatchMock->StartMock.CalledOnce())).Then(

   METALMOCKTHEN(_caller_ReadFileBytesMock->CallConstMemberFunctionMock.CalledOnceWith(
      &_fileSystem, &Utils::FileSystem::ReadFileBytes, sourceFilePath))).Then(

   METALMOCKTHEN(_call_fs_create_directoriesMock.CalledOnceWith(expectedParentPathOfDestinationFilePath))).Then(

   METALMOCKTHEN(_caller_CreateOrOpenFileFunctionMock->CallConstMemberFunctionMock.CalledOnceWith(
      &_fileSystem, &Utils::FileSystem::CreateFileInBinaryWriteMode, destinationFilePath))).Then(

   METALMOCKTHEN(_call_fwriteMock.CalledOnceWith(
      sourceFileBytes->data(), 1, expectedSourceFileBytesSize, binaryWriteModeDestinationFilePointer.get()))).Then(

   METALMOCKTHEN(_asserterMock->ThrowIfSizeTsNotEqualMock.CalledOnceWith(expectedSourceFileBytesSize, numberOfBytesWritten,
      "fwrite() in Utils::FileSystem::CopyFileToFile(const fs::path& sourceFilePath, const fs::path& destinationFilePath) unexpectedly returned numberOfBytesWritten != sourceFileSize")));

   METALMOCKTHEN(stopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce());
   Utils::FileCopyResult expectedReturnValue{};
   expectedReturnValue.sourceFilePath = sourceFilePath;
   expectedReturnValue.destinationFilePath = destinationFilePath;
   expectedReturnValue.copySucceeded = true;
   expectedReturnValue.durationInMilliseconds = elapsedMilliseconds;
   ARE_EQUAL(expectedReturnValue, fileCopyResult);
}

TEST(CopyFileToFileLargerThan2GB_CreatesParentFoldersForDestinationFile_CopiesSourceFileToDestinationFileByCallingStdFilesystemCopyFileToFile)
{
   const shared_ptr<Utils::StopwatchMock> stopwatchMock = make_shared<Utils::StopwatchMock>();
   stopwatchMock->StartMock.Expect();
   _stopwatchFactoryMock->NewStopwatchMock.Return(stopwatchMock);

   _call_fs_create_directoriesMock.ReturnRandom();

   const unsigned long long elapsedMilliseconds = stopwatchMock->StopAndGetElapsedMillisecondsMock.ReturnRandom();

   const bool copyFileReturnValue = _call_fs_copy_fileMock.ReturnRandom();

   const fs::path sourceFilePath = ZenUnit::Random<fs::path>();
   const fs::path destinationFilePath = ZenUnit::Random<fs::path>();
   //
   const Utils::FileCopyResult fileCopyResult = _fileSystem.CopyFileToFileLargerThan2GB(sourceFilePath, destinationFilePath);
   //
   const fs::path expectedParentPathOfDestinationFilePath = destinationFilePath.parent_path();
   METALMOCKTHEN(_stopwatchFactoryMock->NewStopwatchMock.CalledOnce()).Then(
   METALMOCKTHEN(stopwatchMock->StartMock.CalledOnce())).Then(
   METALMOCKTHEN(_call_fs_create_directoriesMock.CalledOnceWith(expectedParentPathOfDestinationFilePath))).Then(
   METALMOCKTHEN(_call_fs_copy_fileMock.CalledOnceWith(sourceFilePath, destinationFilePath, fs::copy_options::overwrite_existing))).Then(
   METALMOCKTHEN(stopwatchMock->StopAndGetElapsedMillisecondsMock.CalledOnce()));
   Utils::FileCopyResult expectedFileCopyResult{};
   expectedFileCopyResult.sourceFilePath = sourceFilePath;
   expectedFileCopyResult.destinationFilePath = destinationFilePath;
   expectedFileCopyResult.copySucceeded = copyFileReturnValue;
   expectedFileCopyResult.durationInMilliseconds = elapsedMilliseconds;
   ARE_EQUAL(expectedFileCopyResult, fileCopyResult);
}

TEST(CreateTextFileIfDoesNotExist_FileExists_DoesNothing)
{
   _call_fs_existsMock.Return(true);
   const fs::path filePath = ZenUnit::Random<fs::path>();
   const string fileText = ZenUnit::Random<string>();
   //
   _fileSystem.CreateTextFileIfDoesNotExist(filePath, fileText);
   //
   METALMOCK(_call_fs_existsMock.CalledOnceWith(filePath));
}

TEST(CreateTextFileIfDoesNotExist_FileDoesNotExist_CreateFileWithFileText)
{
   _call_fs_existsMock.Return(false);

   const shared_ptr<FILE> writeModeBinaryFilePointer = make_shared<FILE>();
   _caller_CreateOrOpenFileFunctionMock->CallConstMemberFunctionMock.Return(writeModeBinaryFilePointer);

   _caller_WriteTextToOpenFileMock->CallConstMemberFunctionMock.Expect();

   const fs::path filePath = ZenUnit::Random<fs::path>();
   const string fileText = ZenUnit::Random<string>();
   //
   _fileSystem.CreateTextFileIfDoesNotExist(filePath, fileText);
   //
   METALMOCKTHEN(_caller_CreateOrOpenFileFunctionMock->CallConstMemberFunctionMock.CalledOnceWith(
      &_fileSystem, &Utils::FileSystem::CreateFileInBinaryWriteMode, filePath)).Then(
   METALMOCKTHEN(_caller_WriteTextToOpenFileMock->CallConstMemberFunctionMock.CalledOnceWith(
      &_fileSystem, &Utils::FileSystem::WriteTextToOpenFile, writeModeBinaryFilePointer, fileText)));
   METALMOCK(_call_fs_existsMock.CalledOnceWith(filePath));
}

TEST(DeleteFolder_CallsTestableFileSystemremove_all)
{
   _passthroughFileSystemMock->remove_allMock.ReturnRandom();
   const fs::path folderPath = ZenUnit::Random<fs::path>();
   //
   _fileSystem.DeleteFolder(folderPath);
   //
   METALMOCK(_passthroughFileSystemMock->remove_allMock.CalledOnceWith(folderPath));
}

TEST(FileOrFolderExists_ReturnsResultOfCallingStdFileSystemExists)
{
   const bool fileOrFolderExists = _call_fs_existsMock.ReturnRandom();
   const fs::path fileOrFolderPath = ZenUnit::Random<fs::path>();
   //
   const bool returnedFileOrFolderExists = _fileSystem.FileOrFolderExists(fileOrFolderPath);
   //
   METALMOCK(_call_fs_existsMock.CalledOnceWith(fileOrFolderPath));
   ARE_EQUAL(fileOrFolderExists, returnedFileOrFolderExists);
}

TEST(ReadFileBytes_OpensFileInBinaryReadMode_FileSizeIs0_ClosesFile_ReturnsSharedPtrToEmptyCharVector)
{
   const shared_ptr<FILE> binaryReadModeFilePointer = make_shared<FILE>();
   _caller_CreateOrOpenFileFunctionMock->CallConstMemberFunctionMock.Return(binaryReadModeFilePointer);

   _caller_ReadFileSizeMock->CallConstMemberFunctionMock.Return(0);

   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const shared_ptr<const vector<char>> fileBytes = _fileSystem.ReadFileBytes(filePath);
   //
   METALMOCKTHEN(_caller_CreateOrOpenFileFunctionMock->CallConstMemberFunctionMock.CalledOnceWith(&_fileSystem, &Utils::FileSystem::OpenFileInBinaryReadMode, filePath)).Then(
   METALMOCKTHEN(_caller_ReadFileSizeMock->CallConstMemberFunctionMock.CalledOnceWith(&_fileSystem, &Utils::FileSystem::ReadFileSize, binaryReadModeFilePointer)));
   IS_EMPTY(*fileBytes);
}

TEST(ReadFileBytes_OpensFileInBinaryReadMode_FileSizeIsNot0_ReadsFileBytes_ClosesFile_ReturnsSharedPtrToFileBytes)
{
   const shared_ptr<FILE> binaryReadModeFilePointer = make_shared<FILE>();
   _caller_CreateOrOpenFileFunctionMock->CallConstMemberFunctionMock.Return(binaryReadModeFilePointer);

   const size_t fileSize = ZenUnit::RandomBetween<size_t>(1, 3);
   _caller_ReadFileSizeMock->CallConstMemberFunctionMock.Return(fileSize);

   vector<char>* const fileBytesBuffer = new vector<char>(fileSize);
   _charVectorAllocatorMock->NewCharVectorMock.Return(fileBytesBuffer);
   char* const expected0thBytesBufferByte = &(*fileBytesBuffer)[0];

   _asserterMock->ThrowIfSizeTsNotEqualMock.Expect();

   const size_t numberOfBytesRead = _call_freadMock.ReturnRandom();

   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const shared_ptr<const vector<char>> fileBytes = _fileSystem.ReadFileBytes(filePath);
   //
   METALMOCKTHEN(_caller_CreateOrOpenFileFunctionMock->CallConstMemberFunctionMock.CalledOnceWith(&_fileSystem, &Utils::FileSystem::OpenFileInBinaryReadMode, filePath)).Then(
   METALMOCKTHEN(_caller_ReadFileSizeMock->CallConstMemberFunctionMock.CalledOnceWith(&_fileSystem, &Utils::FileSystem::ReadFileSize, binaryReadModeFilePointer))).Then(
   METALMOCKTHEN(_charVectorAllocatorMock->NewCharVectorMock.CalledOnceWith(fileSize))).Then(
   METALMOCKTHEN(_call_freadMock.CalledOnceWith(expected0thBytesBufferByte, 1, fileSize, binaryReadModeFilePointer.get()))).Then(
   METALMOCKTHEN(_asserterMock->ThrowIfSizeTsNotEqualMock.CalledOnceWith(fileSize, numberOfBytesRead,
      "fread() in Utils::FileSystem::ReadFileBytes(const fs::path& filePath) unexpectedly did not return fileSize")));
   const vector<char> expectedFileBytes(fileSize);
   VECTORS_ARE_EQUAL(expectedFileBytes, *fileBytes);
}

TEST(ReadFileLinesWhichMustBeNonEmpty_FileTextIsEmpty_ThrowsFileSystemException)
{
   _caller_ReadFileTextMock->CallConstMemberFunctionMock.Return("");
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   Utils::FileMalformedException expectedFileMalformedException(filePath, "File cannot be empty");
   THROWS_EXCEPTION(_fileSystem.ReadFileLinesWhichMustBeNonEmpty(filePath),
      Utils::FileMalformedException, expectedFileMalformedException.what());
   //
   METALMOCK(_caller_ReadFileTextMock->CallConstMemberFunctionMock.CalledOnceWith(
      &_fileSystem, &Utils::FileSystem::ReadFileText, filePath));
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
      &_fileSystem, &Utils::FileSystem::ReadFileText, filePath));
   VECTORS_ARE_EQUAL(expectedReturnValue, fileLines);
}

TEST(ReadFileText_ReadsFileSizeWhichReturns0_ClosesFile_ReturnsEmptyString)
{
   const shared_ptr<FILE> readModeTextFilePointer = make_shared<FILE>();
   _caller_CreateOrOpenFileFunctionMock->CallConstMemberFunctionMock.Return(readModeTextFilePointer);

   _caller_ReadFileSizeMock->CallConstMemberFunctionMock.Return(0);

   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const string fileText = _fileSystem.ReadFileText(filePath);
   //
   METALMOCKTHEN(_caller_CreateOrOpenFileFunctionMock->CallConstMemberFunctionMock.CalledOnceWith(
      &_fileSystem, &Utils::FileSystem::OpenFileInTextReadMode, filePath)).Then(
   METALMOCKTHEN(_caller_ReadFileSizeMock->CallConstMemberFunctionMock.CalledOnceWith(
      &_fileSystem, &Utils::FileSystem::ReadFileSize, readModeTextFilePointer)));
   ARE_EQUAL("", fileText);
}

static constexpr size_t FileSize = 64;
struct _fread_CallHistoryValues
{
   size_t numberOfCalls = 0;

   size_t returnValue = 0;
   array<char, FileSize> bufferReturnValue = {};

   size_t elementSize = 0;
   size_t elementCount = 0;
   FILE* rawFilePointer = nullptr;
} _fread_CallHistory;

size_t _call_fread_CallInstead(void* buffer, size_t elementSize, size_t elementCount, FILE* rawFilePointer)
{
   ++_fread_CallHistory.numberOfCalls;

   const array<char, FileSize> expectedInitialBufferContents{};
   const char* bufferAsConstCharPointer = reinterpret_cast<const char*>(buffer);
   ARRAYS_ARE_EQUAL(expectedInitialBufferContents.data(), bufferAsConstCharPointer, FileSize);
   memcpy(buffer, _fread_CallHistory.bufferReturnValue.data(), _fread_CallHistory.bufferReturnValue.size());

   _fread_CallHistory.elementSize = elementSize;
   _fread_CallHistory.elementCount = elementCount;
   _fread_CallHistory.rawFilePointer = rawFilePointer;
   return _fread_CallHistory.returnValue;
}

void _call_fread_AssertCalledOnceWith(size_t expectedElementSize, size_t expectedElementCount, FILE* expectedRawFilePointer) const
{
   ARE_EQUAL(1, _fread_CallHistory.numberOfCalls);
   ARE_EQUAL(expectedElementSize, _fread_CallHistory.elementSize);
   ARE_EQUAL(expectedElementCount, _fread_CallHistory.elementCount);
   ARE_EQUAL(expectedRawFilePointer, _fread_CallHistory.rawFilePointer);
}

TEST(ReadFileText_ReadsFileSizeWhichReturnsGreaterThan0_ReadsFileBytesIntoString_ClosesFile_ReturnsFileTextString)
{
   const shared_ptr<FILE> readModeTextFilePointer = make_shared<FILE>();
   _caller_CreateOrOpenFileFunctionMock->CallConstMemberFunctionMock.Return(readModeTextFilePointer);

   _caller_ReadFileSizeMock->CallConstMemberFunctionMock.Return(FileSize);

   _fread_CallHistory.returnValue = FileSize;
   const array<char, FileSize> bufferReturnValue = ZenUnit::RandomStdArray<char, FileSize>();
   _fread_CallHistory.bufferReturnValue = bufferReturnValue;
   _call_freadMock.CallInstead(std::bind(
      &FileSystemTests::_call_fread_CallInstead, this, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4));

   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const string fileText = _fileSystem.ReadFileText(filePath);
   //
   METALMOCKTHEN(_caller_CreateOrOpenFileFunctionMock->CallConstMemberFunctionMock.CalledOnceWith(
      &_fileSystem, &Utils::FileSystem::OpenFileInTextReadMode, filePath)).Then(
   METALMOCKTHEN(_caller_ReadFileSizeMock->CallConstMemberFunctionMock.CalledOnceWith(
      &_fileSystem, &Utils::FileSystem::ReadFileSize, readModeTextFilePointer)));
   _call_fread_AssertCalledOnceWith(1, FileSize, readModeTextFilePointer.get());
   const string expectedFileText(bufferReturnValue.data(), _fread_CallHistory.returnValue);
   ARE_EQUAL(expectedFileText, fileText);
}

TEST(SetCurrentPath_CallsFSCurrentPathWithFolderPath)
{
   _call_fs_current_pathMock.Expect();
   const fs::path folderPath = ZenUnit::Random<fs::path>();
   //
   _fileSystem.SetCurrentPath(folderPath);
   //
   METALMOCK(_call_fs_current_pathMock.CalledOnceWith(folderPath));
}

TEST(ThrowIfFilePathIsNotEmptyPathAndFileDoesNotExist_FilePathIsEmpty_DoesNothing)
{
   const fs::path emptyFilePath{};
   _fileSystem.ThrowIfFilePathIsNotEmptyPathAndFileDoesNotExist(emptyFilePath);
}

TEST(ThrowIfFilePathIsNotEmptyPathAndFileDoesNotExist_FilePathIsNotEmpty_FilePathExists_DoesNothing)
{
   _call_fs_existsMock.Return(true);
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   _fileSystem.ThrowIfFilePathIsNotEmptyPathAndFileDoesNotExist(filePath);
   //
   METALMOCK(_call_fs_existsMock.CalledOnceWith(filePath));
}

TEST(ThrowIfFilePathIsNotEmptyPathAndFileDoesNotExist_FilePathIsNotEmpty_FilePathDoesNotExist_ThrowsFileSystemException)
{
   _call_fs_existsMock.Return(false);
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   Utils::FileNotFoundException expectedException(filePath);
   THROWS_EXCEPTION(_fileSystem.ThrowIfFilePathIsNotEmptyPathAndFileDoesNotExist(filePath),
      Utils::FileNotFoundException, expectedException.what());
   //
   METALMOCK(_call_fs_existsMock.CalledOnceWith(filePath));
}

TEST(WriteTextToOpenFile_CallsFWriteOnFilePointerWithText_CallsFFlushOnFilePointer)
{
   const size_t numberOfBytesWritten = _call_fwriteMock.ReturnRandom();
   _asserterMock->ThrowIfSizeTsNotEqualMock.Expect();

   const int flushReturnValue = _call_fflushMock.ReturnRandom();
   _asserterMock->ThrowIfIntsNotEqualMock.Expect();

   const shared_ptr<FILE> textFilePointer = make_shared<FILE>();
   const string text = ZenUnit::Random<string>();
   //
   _fileSystem.WriteTextToOpenFile(textFilePointer, text);
   //
   const size_t textSize = text.size();
   METALMOCKTHEN(_call_fwriteMock.CalledOnceWith(text.data(), 1, textSize, textFilePointer.get())).Then(
   METALMOCKTHEN(_asserterMock->ThrowIfSizeTsNotEqualMock.CalledOnceWith(
      textSize, numberOfBytesWritten, "fwrite() unexpectedly returned numberOfBytesWritten != textSize"))).Then(
   METALMOCKTHEN(_call_fflushMock.CalledOnceWith(textFilePointer.get()))).Then(
   METALMOCKTHEN(_asserterMock->ThrowIfIntsNotEqualMock.CalledOnceWith(0, flushReturnValue, "fflush() unexpectedly did not return 0")));
}

TEST(WriteBytesToOpenFile_CallsFWriteOnFilePointerWithBytes_CallsFFlushOnFilePointer)
{
   const size_t numberOfBytesWritten = _call_fwriteMock.ReturnRandom();
   _asserterMock->ThrowIfSizeTsNotEqualMock.Expect();

   const int flushReturnValue = _call_fflushMock.ReturnRandom();
   _asserterMock->ThrowIfIntsNotEqualMock.Expect();

   const shared_ptr<FILE> filePointer = make_shared<FILE>();
   const vector<char> bytes = ZenUnit::RandomVector<char>();
   //
   _fileSystem.WriteBytesToOpenFile(filePointer, bytes.data(), bytes.size());
   //
   const size_t bytesLength = bytes.size();
   METALMOCKTHEN(_call_fwriteMock.CalledOnceWith(bytes.data(), 1, bytes.size(), filePointer.get())).Then(
   METALMOCKTHEN(_asserterMock->ThrowIfSizeTsNotEqualMock.CalledOnceWith(
      bytesLength, numberOfBytesWritten, "fwrite() unexpectedly returned numberOfBytesWritten != bytesLength"))).Then(
   METALMOCKTHEN(_call_fflushMock.CalledOnceWith(filePointer.get()))).Then(
   METALMOCKTHEN(_asserterMock->ThrowIfIntsNotEqualMock.CalledOnceWith(0, flushReturnValue, "fflush() unexpectedly did not return 0")));
}

// Private Functions

#if defined __linux__

TEST(Linux__CreateOrOpenFileOnLinux_CreatesParentDirectoriesForFilePath_fopenReturnsNonNullptr_ReturnsOpenedFilePointer)
{
   _call_fs_create_directoriesMock.ReturnRandom();

   FILE* const textModeWriteFilePointer = tmpfile();
   _fopen_CallHistory.returnValue = textModeWriteFilePointer;

   _call_fopenMock.CallInstead(std::bind(&FileSystemTests::fopen_CallInsteadFunction, this, placeholders::_1, placeholders::_2));

   const fs::path filePath = ZenUnit::Random<fs::path>();
   const char* const fileOpenMode = ZenUnit::Random<const char*>();
   //
   const shared_ptr<FILE> returnedFilePointer = _fileSystem.CreateOrOpenFileOnLinux(filePath, fileOpenMode);
   //
   const fs::path expectedParentDirectoryPath = filePath.parent_path();
   METALMOCK(_call_fs_create_directoriesMock.CalledOnceWith(expectedParentDirectoryPath));
   _fopen_CallHistory.AssertCalledOnceWith(filePath.c_str(), fileOpenMode);
   ARE_EQUAL(textModeWriteFilePointer, returnedFilePointer.get());
}

TEST(Linux__CreateOrOpenFileOnLinux_CreatesParentDirectoriesForFilePath_fopenReturnsNullptr_ThrowsRuntimeError)
{
   _call_fs_create_directoriesMock.ReturnRandom();

   _fopen_CallHistory.returnValue = nullptr;
   _call_fopenMock.CallInstead(std::bind(&FileSystemTests::fopen_CallInsteadFunction, this, placeholders::_1, placeholders::_2));

   const pair<int, string> errnoWithDescription = _errorCodeTranslatorMock->GetErrnoWithDescriptionMock.ReturnRandom();

   const fs::path filePath = ZenUnit::Random<fs::path>();
   const char* const fileOpenMode = ZenUnit::Random<const char*>();
   //
   const string expectedExceptionMessage = Utils::String::ConcatValues(
      "fopen(filePath.c_str(), fileOpenMode) returned nullptr. ",
      "filePath=\"", filePath.string(), "\". errno=", errnoWithDescription.first, " (", errnoWithDescription.second, ")");
   THROWS_EXCEPTION(_fileSystem.CreateOrOpenFileOnLinux(filePath, fileOpenMode),
      runtime_error, expectedExceptionMessage);
   //
   const fs::path expectedParentDirectoryPath = filePath.parent_path();
   METALMOCK(_call_fs_create_directoriesMock.CalledOnceWith(expectedParentDirectoryPath));
   _fopen_CallHistory.AssertCalledOnceWith(filePath.c_str(), fileOpenMode);
   METALMOCK(_errorCodeTranslatorMock->GetErrnoWithDescriptionMock.CalledOnce());
}

#elif defined _WIN32

TEST(Windows__CreateOrOpenFileOnWindows_CreatesParentDirectoriesForFilePath_CallswfsopenWhichReturnsNonNullptr_ReturnsOpenedFilePointer)
{
   _call_fs_create_directoriesMock.ReturnRandom();

   FILE* tempFilePointer = nullptr;
   tmpfile_s(&tempFilePointer);
   _call_wfsopenMock.Return(tempFilePointer);

   const fs::path filePath = ZenUnit::Random<fs::path>();
   const wchar_t* const fileOpenMode = ZenUnit::Random<const wchar_t*>();
   //
   const shared_ptr<FILE> sharedFilePointer = _fileSystem.CreateOrOpenFileOnWindows(filePath, fileOpenMode);
   //
   const fs::path expectedParentDirectoryPath = filePath.parent_path();
   METALMOCKTHEN(_call_fs_create_directoriesMock.CalledOnceWith(expectedParentDirectoryPath)).Then(
   METALMOCKTHEN(_call_wfsopenMock.CalledOnceWith(filePath.c_str(), fileOpenMode, _SH_DENYWR)));
   ARE_EQUAL(tempFilePointer, sharedFilePointer.get());
}

TEST(Windows__CreateOrOpenFileOnWindows_CreatesParentDirectoriesForFilePath_CallswfsopenWhichReturnsNullptr_ThrowsRuntimeError)
{
   _call_fs_create_directoriesMock.ReturnRandom();
   _call_wfsopenMock.Return(nullptr);

   const pair<int, string> errnoWithDescription = _errorCodeTranslatorMock->GetErrnoWithDescriptionMock.ReturnRandom();

   const fs::path filePath = ZenUnit::Random<fs::path>();
   const wchar_t* const fileOpenMode = ZenUnit::Random<const wchar_t*>();

   const string expectedExceptionMessage = Utils::String::ConcatValues(
      "_wfsopen(filePath.c_str(), fileOpenMode, _SH_DENYWR) returned nullptr. ",
      "filePath=\"", filePath.string(), "\". errno=", errnoWithDescription.first, " (", errnoWithDescription.second, ")");
   THROWS_EXCEPTION(_fileSystem.CreateOrOpenFileOnWindows(filePath, fileOpenMode),
      runtime_error, expectedExceptionMessage);
   //
   const fs::path expectedParentDirectoryPath = filePath.parent_path();
   METALMOCKTHEN(_call_fs_create_directoriesMock.CalledOnceWith(expectedParentDirectoryPath)).Then(
   METALMOCKTHEN(_call_wfsopenMock.CalledOnceWith(filePath.c_str(), fileOpenMode, _SH_DENYWR))).Then(
   METALMOCKTHEN(_errorCodeTranslatorMock->GetErrnoWithDescriptionMock.CalledOnce()));
}

#endif

TEST(ReadFileSize_CallsFSeekEndThenFTellToDetermineSizeOfFileInBytes)
{
   const int fseekEndReturnValue = ZenUnit::Random<int>();
   const int fseekSetReturnValue = ZenUnit::Random<int>();
   _call_fseekMock.ReturnValues(fseekEndReturnValue, fseekSetReturnValue);

   _asserterMock->ThrowIfIntsNotEqualMock.Expect();

   const long ftellReturnValue = _call_ftellMock.ReturnRandom();

   const shared_ptr<FILE> filePointer = make_shared<FILE>();
   //
   const size_t fileSizeInBytes = _fileSystem.ReadFileSize(filePointer);
   //
   METALMOCK(_call_fseekMock.CalledNTimes(2));
   METALMOCK(_asserterMock->ThrowIfIntsNotEqualMock.CalledNTimes(2));

   METALMOCKTHEN(_call_fseekMock.CalledWith(filePointer.get(), 0, SEEK_END)).Then(
   METALMOCKTHEN(_asserterMock->ThrowIfIntsNotEqualMock.CalledWith(
      0, fseekEndReturnValue, "fseek(filePointer.get(), 0, SEEK_END) in FileSystem::FileSize() unexpectedly did not return 0"))).Then(
   METALMOCKTHEN(_call_ftellMock.CalledOnceWith(filePointer.get()))).Then(
   METALMOCKTHEN(_call_fseekMock.CalledWith(filePointer.get(), 0, SEEK_SET))).Then(
   METALMOCKTHEN(_asserterMock->ThrowIfIntsNotEqualMock.CalledWith(
      0, fseekSetReturnValue, "fseek(filePointer.get(), 0, SEEK_SET) in FileSystem::FileSize() unexpectedly did not return 0")));
   ARE_EQUAL(static_cast<size_t>(ftellReturnValue), fileSizeInBytes);
}

RUN_TESTS(FileSystemTests)
