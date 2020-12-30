#include "pch.h"
#include "libCloudundancy/UtilityComponents/FileSystem/FileOpenerCloser.h"
#include "libCloudundancyTests/UtilityComponents/Assertion/MetalMock/AsserterMock.h"

TESTS(FileOpenerCloserTests)
AFACT(DefaultConstructor_SetsFunctionPointers)
AFACT(CreateWriteModeBinaryFile_ReturnsFileHandleOpenedInBinaryWriteMode)
AFACT(CreateWriteModeTextFile_ReturnsFileHandleOpenedInTextWriteMode)
AFACT(OpenReadModeBinaryFile_ReturnsFileHandleOpenedInBinaryReadMode)
AFACT(OpenReadModeTextFile_ReturnsFileHandleOpenedInTextReadMode)
AFACT(OpenAppendModeTextFile_ReturnsFileHandleOpenedInTextAppendMode)
AFACT(CloseFile_CallsFCloseOnFileHandle)
// Private Functions
AFACT(ThrowFileOpenExceptionIfFileOpenFailed_FileHandleIsNullptr_ThrowsFileOpenException)
AFACT(ThrowFileOpenExceptionIfFileOpenFailed_FileHandleIsNotNullptr_DoesNotThrowException)
EVIDENCE

FileOpenerCloser _fileOpenerCloser;
// Function Pointers
METALMOCK_NONVOID1_FREE(int, fclose, FILE*)
#if defined __linux__ || defined __APPLE__
METALMOCK_NONVOID2_FREE(FILE*, fopen, const char*, const char*)
#elif _WIN32
METALMOCK_NONVOID3_FREE(FILE*, _wfsopen, const wchar_t*, const wchar_t*, int)
#endif
// Constant Components
AsserterMock* _asserterMock = nullptr;

STARTUP
{
   // Function Pointers
   _fileOpenerCloser._call_fclose = BIND_1ARG_METALMOCK_OBJECT(fcloseMock);
#if defined __linux__ || defined __APPLE__
   _fileOpenerCloser._call_fopen = BIND_2ARG_METALMOCK_OBJECT(fopenMock);
#elif _WIN32
   _fileOpenerCloser._call_wfsopen = BIND_3ARG_METALMOCK_OBJECT(_wfsopenMock);
#endif
   // Constant Components
   _fileOpenerCloser._asserter.reset(_asserterMock = new AsserterMock);
}

TEST(DefaultConstructor_SetsFunctionPointers)
{
   const FileOpenerCloser fileOpenerCloser;
   STD_FUNCTION_TARGETS(::fclose, fileOpenerCloser._call_fclose);
#if defined __linux__ || defined __APPLE__
   STD_FUNCTION_TARGETS(fopen, fileOpenerCloser._call_fopen);
#elif _WIN32
   STD_FUNCTION_TARGETS(_wfsopen, fileOpenerCloser._call_wfsopen);
#endif
}

TEST(CreateWriteModeBinaryFile_ReturnsFileHandleOpenedInBinaryWriteMode)
{
   FILE writeModeBinaryFileHandle;
#if defined __linux__ || defined __APPLE__
   fopenMock.Return(&writeModeBinaryFileHandle);
#elif _WIN32
   _wfsopenMock.Return(&writeModeBinaryFileHandle);
#endif
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   FILE* const returnedWriteModeBinaryFileHandle = _fileOpenerCloser.CreateWriteModeBinaryFile(filePath);
   //
#if defined __linux__ || defined __APPLE__
   METALMOCK(fopenMock.CalledOnceWith(filePath.c_str(), "wb"));
#elif _WIN32
   METALMOCK(_wfsopenMock.CalledOnceWith(filePath.c_str(), L"wb", _SH_DENYWR));
#endif
   ARE_EQUAL(&writeModeBinaryFileHandle, returnedWriteModeBinaryFileHandle);
}

TEST(CreateWriteModeTextFile_ReturnsFileHandleOpenedInTextWriteMode)
{
   FILE writeModeTextFileHandle;
#if defined __linux__ || defined __APPLE__
   fopenMock.Return(&writeModeTextFileHandle);
#elif _WIN32
   _wfsopenMock.Return(&writeModeTextFileHandle);
#endif
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   FILE* const returnedWriteModeTextFileHandle = _fileOpenerCloser.CreateWriteModeTextFile(filePath);
   //
#if defined __linux__ || defined __APPLE__
   METALMOCK(fopenMock.CalledOnceWith(filePath.c_str(), "w"));
#elif _WIN32
   METALMOCK(_wfsopenMock.CalledOnceWith(filePath.c_str(), L"w", _SH_DENYWR));
#endif
   ARE_EQUAL(&writeModeTextFileHandle, returnedWriteModeTextFileHandle);
}

TEST(OpenReadModeBinaryFile_ReturnsFileHandleOpenedInBinaryReadMode)
{
   FILE readModeBinaryFileHandle;
#if defined __linux__ || defined __APPLE__
   fopenMock.Return(&readModeBinaryFileHandle);
#elif _WIN32
   _wfsopenMock.Return(&readModeBinaryFileHandle);
#endif
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   FILE* const returnedReadModeBinaryFileHandle = _fileOpenerCloser.OpenReadModeBinaryFile(filePath);
   //
#if defined __linux__ || defined __APPLE__
   METALMOCK(fopenMock.CalledOnceWith(filePath.c_str(), "rb"));
#elif _WIN32
   METALMOCK(_wfsopenMock.CalledOnceWith(filePath.c_str(), L"rb", _SH_DENYWR));
#endif
   ARE_EQUAL(&readModeBinaryFileHandle, returnedReadModeBinaryFileHandle);
}

TEST(OpenReadModeTextFile_ReturnsFileHandleOpenedInTextReadMode)
{
   FILE readModeTextFileHandle;
#if defined __linux__ || defined __APPLE__
   fopenMock.Return(&readModeTextFileHandle);
#elif _WIN32
   _wfsopenMock.Return(&readModeTextFileHandle);
#endif
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   FILE* const returnedReadModeTextFileHandle = _fileOpenerCloser.OpenReadModeTextFile(filePath);
   //
#if defined __linux__ || defined __APPLE__
   METALMOCK(fopenMock.CalledOnceWith(filePath.c_str(), "r"));
#elif _WIN32
   METALMOCK(_wfsopenMock.CalledOnceWith(filePath.c_str(), L"r", _SH_DENYWR));
#endif
   ARE_EQUAL(&readModeTextFileHandle, returnedReadModeTextFileHandle);
}

TEST(OpenAppendModeTextFile_ReturnsFileHandleOpenedInTextAppendMode)
{
   FILE appendModeTextFileHandle;
#if defined __linux__ || defined __APPLE__
   fopenMock.Return(&appendModeTextFileHandle);
#elif _WIN32
   _wfsopenMock.Return(&appendModeTextFileHandle);
#endif
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   FILE* const returnedAppendModeTextFileHandle = _fileOpenerCloser.OpenAppendModeTextFile(filePath);
   //
#if defined __linux__ || defined __APPLE__
   METALMOCK(fopenMock.CalledOnceWith(filePath.c_str(), "a"));
#elif _WIN32
   METALMOCK(_wfsopenMock.CalledOnceWith(filePath.c_str(), L"a", _SH_DENYWR));
#endif
   ARE_EQUAL(&appendModeTextFileHandle, returnedAppendModeTextFileHandle);
}

TEST(CloseFile_CallsFCloseOnFileHandle)
{
   const int fcloseReturnValue = fcloseMock.ReturnRandom();
   _asserterMock->ThrowIfIntsNotEqualMock.Expect();
   FILE fileHandle{};
   //
   _fileOpenerCloser.CloseFile(&fileHandle);
   //
   METALMOCK(fcloseMock.CalledOnceWith(&fileHandle));
   METALMOCK(_asserterMock->ThrowIfIntsNotEqualMock.CalledOnceWith(0, fcloseReturnValue,
      "fclose(fileHandle) in FileOpenerCloser::CloseFile() unexpectedly returned a non-0 value"));
}

// Private Functions

TEST(ThrowFileOpenExceptionIfFileOpenFailed_FileHandleIsNullptr_ThrowsFileOpenException)
{
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const string expectedExceptionMessage = "fopen() returned nullptr. filePath=\"" + filePath.string() + "\"";
   THROWS_EXCEPTION(_fileOpenerCloser.ThrowFileOpenExceptionIfFileOpenFailed(nullptr, filePath),
      runtime_error, expectedExceptionMessage);
}

TEST(ThrowFileOpenExceptionIfFileOpenFailed_FileHandleIsNotNullptr_DoesNotThrowException)
{
   FILE nonNullFileHandle{};
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   FileOpenerCloser::ThrowFileOpenExceptionIfFileOpenFailed(&nonNullFileHandle, filePath);
}

RUN_TESTS(FileOpenerCloserTests)
