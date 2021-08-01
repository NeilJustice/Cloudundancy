#include "pch.h"
#include "libCloudundancy/UtilityComponents/FileSystem/RawFileSystem.h"
#include "libCloudundancyTests/Components/ErrorHandling/MetalMock/ErrorCodeTranslatorMock.h"
#include "libCloudundancyTests/UtilityComponents/Assertion/MetalMock/AsserterMock.h"
#include "libCloudundancyTests/UtilityComponents/FunctionCallers/MemberFunctions/MetalMock/NonVoidOneArgMemberFunctionCallerMock.h"
#include "libCloudundancyTests/UtilityComponents/FunctionCallers/MemberFunctions/MetalMock/NonVoidTwoArgMemberFunctionCallerMock.h"
#include "libCloudundancyTests/UtilityComponents/FunctionCallers/MemberFunctions/MetalMock/VoidOneArgMemberFunctionCallerMock.h"
#include "libCloudundancyTests/UtilityComponents/FunctionCallers/MemberFunctions/MetalMock/VoidTwoArgMemberFunctionCallerMock.h"

TESTS(RawFileSystemTests)
AFACT(DefaultConstructor_NewsComponents_SetsFunctionPointers)
AFACT(CloseFile_fcloseReturnValueIsNot0_ThrowsRuntimeError)
AFACT(CloseFile_fcloseReturnValueIs0_Returns)
AFACT(CreateFileWithTextIfDoesNotExist_FileExists_DoesNothing)
AFACT(CreateFileWithTextIfDoesNotExist_FileDoesNotExist_CreateFileWithFileText)
#if defined __linux__
AFACT(Linux__CreateFileInBinaryWriteMode_ReturnsSharedFilePointerCreatedWithFileOpenMode_wb)
AFACT(Linux__OpenFileInTextReadMode_ReturnsSharedPtrFromCallingCreateOrOpenFileOnLinux)
#elif defined _WIN32
AFACT(Windows__CreateFileInBinaryWriteMode_ReturnsSharedFilePointerCreatedWithFileOpenMode_wb)
AFACT(Windows__OpenFileInTextReadMode_ReturnsSharedPtrFromCallingCreateOrOpenFileOnWindows)
#endif
AFACT(ReadTextFromOpenFile_ReadsFileSizeWhichReturns0_ClosesFile_ReturnsEmptyString)
AFACT(ReadTextFromOpenFile_ReadsFileSizeWhichReturnsGreaterThan0_ReadsFileBytesIntoString_ClosesFile_ReturnsFileTextString)
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

RawFileSystem _rawFileSystem;
// Function Pointers
METALMOCK_NONVOID1_FREE(bool, _call_fs_create_directories, const fs::path&)
METALMOCK_NONVOID1_FREE(int, _call_fclose, FILE*)
METALMOCK_NONVOID1_FREE(int, _call_fflush, FILE*)
METALMOCK_NONVOID4_FREE(size_t, _call_fread, void*, size_t, size_t, FILE*)
METALMOCK_NONVOID3_FREE(int, _call_fseek, FILE*, long, int)
METALMOCK_NONVOID1_FREE(long, _call_ftell, FILE*)
#if defined __linux__
METALMOCK_NONVOID2_FREE(FILE*, _call_fopen, const char*, const char*)
#elif defined _WIN32
METALMOCK_NONVOID3_FREE(FILE*, _call_wfsopen, const wchar_t*, const wchar_t*, int)
#endif
METALMOCK_NONVOID4_FREE(size_t, _call_fwrite, const void*, size_t, size_t, FILE*)
METALMOCK_NONVOID1_FREE(bool, _call_fs_exists, const fs::path&)
// Function Callers
using _caller_CloseFileMockType = VoidTwoArgMemberFunctionCallerMock<RawFileSystem, const shared_ptr<FILE>&, const fs::path&>;
_caller_CloseFileMockType* _caller_CloseFileMock = nullptr;

using _caller_CreateFileInBinaryWriteModeMockType = NonVoidOneArgMemberFunctionCallerMock<shared_ptr<FILE>, RawFileSystem, const fs::path&>;
_caller_CreateFileInBinaryWriteModeMockType* _caller_CreateFileInBinaryWriteModeMock = nullptr;

using _caller_ReadFileSizeMockType = NonVoidOneArgMemberFunctionCallerMock<size_t, RawFileSystem, const shared_ptr<FILE>&>;
_caller_ReadFileSizeMockType* _caller_ReadFileSizeMock = nullptr;

using _caller_WriteTextToOpenFileMockType = VoidTwoArgMemberFunctionCallerMock<RawFileSystem, const shared_ptr<FILE>&, string_view>;
_caller_WriteTextToOpenFileMockType* _caller_WriteTextToOpenFileMock = nullptr;

#if defined __linux__
using _caller_CreateOrOpenFileOnLinuxMockType = NonVoidTwoArgMemberFunctionCallerMock<shared_ptr<FILE>, RawFileSystem, const fs::path&, const char*>;
_caller_CreateOrOpenFileOnLinuxMockType* _caller_CreateOrOpenFileOnLinuxMock = nullptr;
#elif defined _WIN32
using _caller_CreateOrOpenFileOnWindowsMockType = NonVoidTwoArgMemberFunctionCallerMock<shared_ptr<FILE>, RawFileSystem, const fs::path&, const wchar_t*>;
_caller_CreateOrOpenFileOnWindowsMockType* _caller_CreateOrOpenFileOnWindowsMock = nullptr;
#endif

// Constant Components
AsserterMock* _asserterMock = nullptr;
ErrorCodeTranslatorMock* _errorCodeTranslatorMock = nullptr;

STARTUP
{
   // C Function Pointers
   _rawFileSystem._call_fclose = BIND_1ARG_METALMOCK_OBJECT(_call_fcloseMock);
   _rawFileSystem._call_fflush = BIND_1ARG_METALMOCK_OBJECT(_call_fflushMock);
   _rawFileSystem._call_fread = BIND_4ARG_METALMOCK_OBJECT(_call_freadMock);
   _rawFileSystem._call_fseek = BIND_3ARG_METALMOCK_OBJECT(_call_fseekMock);
   _rawFileSystem._call_ftell = BIND_1ARG_METALMOCK_OBJECT(_call_ftellMock);
   _rawFileSystem._call_fwrite = BIND_4ARG_METALMOCK_OBJECT(_call_fwriteMock);
#if defined __linux__
   _rawFileSystem._call_fopen = BIND_2ARG_METALMOCK_OBJECT(_call_fopenMock);
#elif defined _WIN32
   _rawFileSystem._call_wfsopen = BIND_3ARG_METALMOCK_OBJECT(_call_wfsopenMock);
#endif
   // std::filesystem Function Pointers
   _rawFileSystem._call_fs_create_directories = BIND_1ARG_METALMOCK_OBJECT(_call_fs_create_directoriesMock);
   _rawFileSystem._call_fs_exists = BIND_1ARG_METALMOCK_OBJECT(_call_fs_existsMock);
   // Function Callers
   _rawFileSystem._caller_CloseFile.reset(_caller_CloseFileMock = new _caller_CloseFileMockType);
   _rawFileSystem._caller_CreateFileInBinaryWriteMode.reset(_caller_CreateFileInBinaryWriteModeMock = new _caller_CreateFileInBinaryWriteModeMockType);
   _rawFileSystem._caller_ReadFileSize.reset(_caller_ReadFileSizeMock = new _caller_ReadFileSizeMockType);
#if defined __linux__
   _rawFileSystem._caller_CreateOrOpenFileOnLinux.reset(_caller_CreateOrOpenFileOnLinuxMock = new _caller_CreateOrOpenFileOnLinuxMockType);
#elif defined _WIN32
   _rawFileSystem._caller_CreateOrOpenFileOnWindows.reset(_caller_CreateOrOpenFileOnWindowsMock = new _caller_CreateOrOpenFileOnWindowsMockType);
#endif
   _rawFileSystem._caller_WriteTextToOpenFile.reset(_caller_WriteTextToOpenFileMock = new _caller_WriteTextToOpenFileMockType);
   // Constant Components
   _rawFileSystem._asserter.reset(_asserterMock = new AsserterMock);
   _rawFileSystem._errorCodeTranslator.reset(_errorCodeTranslatorMock = new ErrorCodeTranslatorMock);
}

TEST(DefaultConstructor_NewsComponents_SetsFunctionPointers)
{
   RawFileSystem rawFileSystem;
   // C Function Pointers
   STD_FUNCTION_TARGETS(fclose, rawFileSystem._call_fclose);
   STD_FUNCTION_TARGETS(fflush, rawFileSystem._call_fflush);
   STD_FUNCTION_TARGETS(fread, rawFileSystem._call_fread);
   STD_FUNCTION_TARGETS(fseek, rawFileSystem._call_fseek);
   STD_FUNCTION_TARGETS(ftell, rawFileSystem._call_ftell);
   STD_FUNCTION_TARGETS(fwrite, rawFileSystem._call_fwrite);
#if defined __linux__
   STD_FUNCTION_TARGETS(fopen, rawFileSystem._call_fopen);
#elif defined _WIN32
   STD_FUNCTION_TARGETS(_wfsopen, rawFileSystem._call_wfsopen);
#endif
   // std::filesystem Function Pointers
#if defined _WIN32
   STD_FUNCTION_TARGETS_OVERLOAD(RawFileSystem::create_directories_FunctionOverloadType, fs::create_directories, rawFileSystem._call_fs_create_directories);
   STD_FUNCTION_TARGETS_OVERLOAD(RawFileSystem::std_filesystem_exists_FunctionOverloadType, fs::exists, rawFileSystem._call_fs_exists);
#endif
   // Function Callers
   DELETE_TO_ASSERT_NEWED(rawFileSystem._caller_CreateFileInBinaryWriteMode);
   DELETE_TO_ASSERT_NEWED(rawFileSystem._caller_CloseFile);
   DELETE_TO_ASSERT_NEWED(rawFileSystem._caller_ReadFileSize);
   DELETE_TO_ASSERT_NEWED(rawFileSystem._caller_WriteTextToOpenFile);
#if defined __linux__
   DELETE_TO_ASSERT_NEWED(rawFileSystem._caller_CreateOrOpenFileOnLinux);
#elif defined _WIN32
   DELETE_TO_ASSERT_NEWED(rawFileSystem._caller_CreateOrOpenFileOnWindows);
#endif
   // Constant Components
   DELETE_TO_ASSERT_NEWED(rawFileSystem._asserter);
   DELETE_TO_ASSERT_NEWED(rawFileSystem._errorCodeTranslator);
}

TEST(CloseFile_fcloseReturnValueIs0_Returns)
{
   _call_fcloseMock.Return(0);
   const shared_ptr<FILE> filePointer = make_shared<FILE>();
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   _rawFileSystem.CloseFile(filePointer, filePath);
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
   const string expectedExceptionMessage = String::ConcatValues(
      "fclose(filePointer) when closing file ", filePath.string(), " returned ", errnoWithDescription.first, ": ", errnoWithDescription.second);
   THROWS_EXCEPTION(_rawFileSystem.CloseFile(filePointer, filePath),
      runtime_error, expectedExceptionMessage);
   //
   METALMOCK(_call_fcloseMock.CalledOnceWith(filePointer.get()));
   METALMOCK(_errorCodeTranslatorMock->GetErrnoWithDescriptionMock.CalledOnce());
}

TEST(CreateFileWithTextIfDoesNotExist_FileExists_DoesNothing)
{
   _call_fs_existsMock.Return(true);
   const fs::path filePath = ZenUnit::Random<fs::path>();
   const string fileText = ZenUnit::Random<string>();
   //
   _rawFileSystem.CreateFileWithTextIfDoesNotExist(filePath, fileText);
   //
   METALMOCK(_call_fs_existsMock.CalledOnceWith(filePath));
}

TEST(CreateFileWithTextIfDoesNotExist_FileDoesNotExist_CreateFileWithFileText)
{
   _call_fs_existsMock.Return(false);
   const shared_ptr<FILE> textFilePointer = make_shared<FILE>();
   _caller_CreateFileInBinaryWriteModeMock->CallConstMemberFunctionMock.Return(textFilePointer);
   _caller_WriteTextToOpenFileMock->CallConstMemberFunctionMock.Expect();
   const fs::path filePath = ZenUnit::Random<fs::path>();
   const string fileText = ZenUnit::Random<string>();
   //
   _rawFileSystem.CreateFileWithTextIfDoesNotExist(filePath, fileText);
   //
   METALMOCK(_caller_CreateFileInBinaryWriteModeMock->CallConstMemberFunctionMock.CalledOnceWith(
      &RawFileSystem::CreateFileInBinaryWriteMode, &_rawFileSystem, filePath));
   METALMOCK(_caller_WriteTextToOpenFileMock->CallConstMemberFunctionMock.CalledOnceWith(
      &RawFileSystem::WriteTextToOpenFile, &_rawFileSystem, textFilePointer, fileText));
   METALMOCK(_call_fs_existsMock.CalledOnceWith(filePath));
}

#if defined __linux__

TEST(Linux__CreateFileInBinaryWriteMode_ReturnsSharedFilePointerCreatedWithFileOpenMode_wb)
{
   const shared_ptr<FILE> filePointer = make_shared<FILE>();
   _caller_CreateOrOpenFileOnLinuxMock->CallConstMemberFunctionMock.Return(filePointer);
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const shared_ptr<FILE> returnedTextFilePointer = _rawFileSystem.CreateFileInBinaryWriteMode(filePath);
   //
   METALMOCK(_caller_CreateOrOpenFileOnLinuxMock->CallConstMemberFunctionMock.CalledOnceWith(
      &RawFileSystem::CreateOrOpenFileOnLinux, &_rawFileSystem, filePath, "wb"));
   ARE_EQUAL(filePointer, returnedTextFilePointer);
}

TEST(Linux__CreateOrOpenFileInBinaryAppendMode_ReturnsSharedFilePointerCreatedWithFileOpenMode_ab)
{
   const shared_ptr<FILE> filePointer = make_shared<FILE>();
   _caller_CreateOrOpenFileOnLinuxMock->CallConstMemberFunctionMock.Return(filePointer);
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const shared_ptr<FILE> returnedFilePointer = _rawFileSystem.CreateOrOpenFileInBinaryAppendMode(filePath);
   //
   METALMOCK(_caller_CreateOrOpenFileOnLinuxMock->CallConstMemberFunctionMock.CalledOnceWith(
      &RawFileSystem::CreateOrOpenFileOnLinux, &_rawFileSystem, filePath, "ab"));
   ARE_EQUAL(filePointer, returnedFilePointer);
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

TEST(Linux__OpenFileInTextReadMode_ReturnsSharedPtrFromCallingCreateOrOpenFileOnLinux)
{
   shared_ptr<FILE> filePointer = make_shared<FILE>();
   _caller_CreateOrOpenFileOnLinuxMock->CallConstMemberFunctionMock.Return(filePointer);
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const shared_ptr<FILE> returnedFilePointer = _rawFileSystem.OpenFileInTextReadMode(filePath);
   //
   METALMOCK(_caller_CreateOrOpenFileOnLinuxMock->CallConstMemberFunctionMock.CalledOnceWith(
      &RawFileSystem::CreateOrOpenFileOnWindows, &_rawFileSystem, filePath, "r"));
   ARE_EQUAL(filePointer, returnedFilePointer);
}

#elif defined _WIN32

TEST(Windows__CreateFileInBinaryWriteMode_ReturnsSharedFilePointerCreatedWithFileOpenMode_wb)
{
   const shared_ptr<FILE> filePointer = make_shared<FILE>();
   _caller_CreateOrOpenFileOnWindowsMock->CallConstMemberFunctionMock.Return(filePointer);
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const shared_ptr<FILE> returnedFilePointer = _rawFileSystem.CreateFileInBinaryWriteMode(filePath);
   //
   METALMOCK(_caller_CreateOrOpenFileOnWindowsMock->CallConstMemberFunctionMock.CalledOnceWith(
      &RawFileSystem::CreateOrOpenFileOnWindows, &_rawFileSystem, filePath, L"wb"));
   ARE_EQUAL(filePointer, returnedFilePointer);
}

TEST(Windows__OpenFileInTextReadMode_ReturnsSharedPtrFromCallingCreateOrOpenFileOnWindows)
{
   shared_ptr<FILE> filePointer = make_shared<FILE>();
   _caller_CreateOrOpenFileOnWindowsMock->CallConstMemberFunctionMock.Return(filePointer);
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const shared_ptr<FILE> returnedFilePointer = _rawFileSystem.OpenFileInTextReadMode(filePath);
   //
   METALMOCK(_caller_CreateOrOpenFileOnWindowsMock->CallConstMemberFunctionMock.CalledOnceWith(
      &RawFileSystem::CreateOrOpenFileOnWindows, &_rawFileSystem, filePath, L"r"));
   ARE_EQUAL(filePointer, returnedFilePointer);
}

#endif

TEST(ReadTextFromOpenFile_ReadsFileSizeWhichReturns0_ClosesFile_ReturnsEmptyString)
{
   _caller_ReadFileSizeMock->CallConstMemberFunctionMock.Return(0);
   const shared_ptr<FILE> filePointer = make_shared<FILE>();
   //
   _rawFileSystem.ReadTextFromOpenFile(filePointer);
   //
   METALMOCK(_caller_ReadFileSizeMock->CallConstMemberFunctionMock.CalledOnceWith(&RawFileSystem::ReadFileSize, &_rawFileSystem, filePointer));
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

size_t fread_CallInstead(void* buffer, size_t elementSize, size_t elementCount, FILE* rawFilePointer)
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

void fread_AssertCalledOnceWith(size_t expectedElementSize, size_t expectedElementCount, FILE* expectedRawFilePointer)
{
   ARE_EQUAL(1, _fread_CallHistory.numberOfCalls);
   ARE_EQUAL(expectedElementSize, _fread_CallHistory.elementSize);
   ARE_EQUAL(expectedElementCount, _fread_CallHistory.elementCount);
   ARE_EQUAL(expectedRawFilePointer, _fread_CallHistory.rawFilePointer);
}

TEST(ReadTextFromOpenFile_ReadsFileSizeWhichReturnsGreaterThan0_ReadsFileBytesIntoString_ClosesFile_ReturnsFileTextString)
{
   //_caller_ReadFileSizeMock->CallConstMemberFunctionMock.Return(FileSize);

   //const size_t numberOfBytesRead = ZenUnit::Random<size_t>();
   //_fread_CallHistory.returnValue = numberOfBytesRead;
   //const array<char, FileSize> bufferReturnValue = ZenUnit::RandomStdArray<char, FileSize>();
   //_fread_CallHistory.bufferReturnValue = bufferReturnValue;
   //_call_freadMock.CallInstead(std::bind(
   //   &RawFileSystemTests::fread_CallInstead, this, placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4));

   //_asserterMock->ThrowIfSizeTsNotEqualMock.Expect();

   //const shared_ptr<FILE> filePointer = make_shared<FILE>();
   ////
   //_rawFileSystem.ReadTextFromOpenFile(filePointer);
   ////
   //METALMOCK(_caller_ReadFileSizeMock->CallConstMemberFunctionMock.CalledOnceWith(&RawFileSystem::ReadFileSize, &_rawFileSystem, filePointer));
   //fread_AssertCalledOnceWith(1, FileSize, filePointer.get());
   //METALMOCK(_asserterMock->ThrowIfSizeTsNotEqualMock.CalledOnceWith(FileSize, numberOfBytesRead,
   //   "_call_fread(const_cast<char*>(&fileText[0]), 1, fileSize, filePointer.get()) unexpectedly returned numberOfBytesRead != fileSize"));
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
   _rawFileSystem.WriteTextToOpenFile(textFilePointer, text);
   //
   const size_t textSize = text.size();
   METALMOCK(_call_fwriteMock.CalledOnceWith(text.data(), 1, textSize, textFilePointer.get()));
   METALMOCK(_asserterMock->ThrowIfSizeTsNotEqualMock.CalledOnceWith(
      textSize, numberOfBytesWritten, "fwrite() unexpectedly returned numberOfBytesWritten != textSize"));
   METALMOCK(_call_fflushMock.CalledOnceWith(textFilePointer.get()));
   METALMOCK(_asserterMock->ThrowIfIntsNotEqualMock.CalledOnceWith(0, flushReturnValue, "fflush() unexpectedly did not return 0"));
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
   _rawFileSystem.WriteBytesToOpenFile(filePointer, bytes.data(), bytes.size());
   //
   const size_t bytesLength = bytes.size();
   METALMOCK(_call_fwriteMock.CalledOnceWith(bytes.data(), 1, bytes.size(), filePointer.get()));
   METALMOCK(_asserterMock->ThrowIfSizeTsNotEqualMock.CalledOnceWith(
      bytesLength, numberOfBytesWritten, "fwrite() unexpectedly returned numberOfBytesWritten != bytesLength"));
   METALMOCK(_call_fflushMock.CalledOnceWith(filePointer.get()));
   METALMOCK(_asserterMock->ThrowIfIntsNotEqualMock.CalledOnceWith(0, flushReturnValue, "fflush() unexpectedly did not return 0"));
}

// Private Functions

#if defined __linux__

TEST(Linux__CreateOrOpenFileOnLinux_CreatesParentDirectoriesForFilePath_fopenReturnsNonNullptr_ReturnsOpenedFilePointer)
{
   _call_fs_create_directoriesMock.ReturnRandom();

   FILE* const openWriteModeTextFilePointer = tmpfile();
   _fopen_CallHistory.returnValue = &openWriteModeTextFilePointer;

   _call_fopenMock.CallInstead(std::bind(&RawFileSystemTests::fopen_CallInsteadFunction, this, placeholders::_1, placeholders::_2));

   const fs::path filePath = ZenUnit::Random<fs::path>();
   const char* const fileOpenMode = ZenUnit::Random<const char*>();
   //
   const shared_ptr<FILE> returnedOpenWriteModeTextFilePointer = _rawFileSystem.CreateOrOpenFileOnLinux(filePath, fileOpenMode);
   //
   const fs::path expectedParentDirectoryPath = filePath.parent_path();
   METALMOCK(_call_fs_create_directoriesMock.CalledOnceWith(expectedParentDirectoryPath));
   _fopen_CallHistory.AssertCalledOnceWith(filePath.c_str(), fileOpenMode);
   ARE_EQUAL(&openWriteModeTextFilePointer, returnedOpenWriteModeTextFilePointer.get());
}

TEST(Linux__CreateOrOpenFileOnLinux_CreatesParentDirectoriesForFilePath_fopenReturnsNullptr_ThrowsRuntimeError)
{
   _call_fs_create_directoriesMock.ReturnRandom();

   _fopen_CallHistory.returnValue = nullptr;
   _call_fopenMock.CallInstead(std::bind(&RawFileSystemTests::fopen_CallInsteadFunction, this, placeholders::_1, placeholders::_2));

   const pair<int, string> errnoWithDescription = _errorCodeTranslatorMock->GetErrnoWithDescriptionMock.ReturnRandom();

   const fs::path filePath = ZenUnit::Random<fs::path>();
   const char* const fileOpenMode = ZenUnit::Random<const char*>();
   //
   const string expectedExceptionMessage = String::ConcatValues(
      "fopen(filePath.c_str(), fileOpenMode) returned nullptr. ",
      "filePath=\"", filePath.string(), "\". errno=", errnoWithDescription.first, " (", errnoWithDescription.second, ")");
   THROWS_EXCEPTION(_rawFileSystem.CreateOrOpenFileOnLinux(filePath, fileOpenMode),
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

   FILE* const rawFilePointer = tmpfile();
   _call_wfsopenMock.Return(rawFilePointer);

   const fs::path filePath = ZenUnit::Random<fs::path>();
   const wchar_t* const fileOpenMode = ZenUnit::Random<const wchar_t*>();
   //
   const shared_ptr<FILE> sharedFilePointer = _rawFileSystem.CreateOrOpenFileOnWindows(filePath, fileOpenMode);
   //
   const fs::path expectedParentDirectoryPath = filePath.parent_path();
   METALMOCK(_call_fs_create_directoriesMock.CalledOnceWith(expectedParentDirectoryPath));
   METALMOCK(_call_wfsopenMock.CalledOnceWith(filePath.c_str(), fileOpenMode, _SH_DENYWR));
   ARE_EQUAL(rawFilePointer, sharedFilePointer.get());
}

TEST(Windows__CreateOrOpenFileOnWindows_CreatesParentDirectoriesForFilePath_CallswfsopenWhichReturnsNullptr_ThrowsRuntimeError)
{
   _call_fs_create_directoriesMock.ReturnRandom();
   _call_wfsopenMock.Return(nullptr);

   const pair<int, string> errnoWithDescription = _errorCodeTranslatorMock->GetErrnoWithDescriptionMock.ReturnRandom();

   const fs::path filePath = ZenUnit::Random<fs::path>();
   const wchar_t* const fileOpenMode = ZenUnit::Random<const wchar_t*>();

   const string expectedExceptionMessage = String::ConcatValues(
      "_wfsopen(filePath.c_str(), fileOpenMode, _SH_DENYWR) returned nullptr. ",
      "filePath=\"", filePath.string(), "\". errno=", errnoWithDescription.first, " (", errnoWithDescription.second, ")");
   THROWS_EXCEPTION(_rawFileSystem.CreateOrOpenFileOnWindows(filePath, fileOpenMode),
      runtime_error, expectedExceptionMessage);
   //
   const fs::path expectedParentDirectoryPath = filePath.parent_path();
   METALMOCK(_call_fs_create_directoriesMock.CalledOnceWith(expectedParentDirectoryPath));
   METALMOCK(_call_wfsopenMock.CalledOnceWith(filePath.c_str(), fileOpenMode, _SH_DENYWR));
   METALMOCK(_errorCodeTranslatorMock->GetErrnoWithDescriptionMock.CalledOnce());
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
   const size_t fileSizeInBytes = _rawFileSystem.ReadFileSize(filePointer);
   //
   METALMOCK(_call_fseekMock.CalledAsFollows(
   {
      { filePointer.get(), 0, SEEK_END },
      { filePointer.get(), 0, SEEK_SET }
   }));
   METALMOCK(_asserterMock->ThrowIfIntsNotEqualMock.CalledAsFollows(
   {
      { 0, fseekEndReturnValue, "fseek(filePointer.get(), 0, SEEK_END) in FileSystem::FileSize() unexpectedly did not return 0" },
      { 0, fseekSetReturnValue, "fseek(filePointer.get(), 0, SEEK_SET) in FileSystem::FileSize() unexpectedly did not return 0" }
   }));
   METALMOCK(_call_ftellMock.CalledOnceWith(filePointer.get()));
   ARE_EQUAL(static_cast<size_t>(ftellReturnValue), fileSizeInBytes);
}

RUN_TESTS(RawFileSystemTests)
