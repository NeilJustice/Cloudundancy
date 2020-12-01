#include "pch.h"
#include "libCloudundancy/Components/FileSystem/FileOpenerCloser.h"
#include "libCloudundancyTests/Components/Assertion/MetalMock/AsserterMock.h"

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
#ifdef __linux__
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
#ifdef __linux__
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
#ifdef __linux__
   STD_FUNCTION_TARGETS(fopen, fileOpenerCloser._call_fopen);
#elif _WIN32
   STD_FUNCTION_TARGETS(_wfsopen, fileOpenerCloser._call_wfsopen);
#endif
}

TEST(CreateWriteModeBinaryFile_ReturnsFileHandleOpenedInBinaryWriteMode)
{
   FILE writeModeBinaryFileHandle;
#ifdef __linux__
   fopenMock.Return(&writeModeBinaryFileHandle);
#elif _WIN32
   _wfsopenMock.Return(&writeModeBinaryFileHandle);
#endif
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   FILE* const returnedWriteModeBinaryFileHandle = _fileOpenerCloser.CreateWriteModeBinaryFile(filePath);
   //
#ifdef __linux__
   METALMOCK(fopenMock.CalledOnceWith(filePath.c_str(), "wb"));
#elif _WIN32
   METALMOCK(_wfsopenMock.CalledOnceWith(filePath.c_str(), L"wb", _SH_DENYWR));
#endif
   ARE_EQUAL(&writeModeBinaryFileHandle, returnedWriteModeBinaryFileHandle);
}

TEST(CreateWriteModeTextFile_ReturnsFileHandleOpenedInTextWriteMode)
{
   FILE writeModeTextFileHandle;
#ifdef __linux__
   fopenMock.Return(&writeModeTextFileHandle);
#elif _WIN32
   _wfsopenMock.Return(&writeModeTextFileHandle);
#endif
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   FILE* const returnedWriteModeTextFileHandle = _fileOpenerCloser.CreateWriteModeTextFile(filePath);
   //
#ifdef __linux__
   METALMOCK(fopenMock.CalledOnceWith(filePath.c_str(), "w"));
#elif _WIN32
   METALMOCK(_wfsopenMock.CalledOnceWith(filePath.c_str(), L"w", _SH_DENYWR));
#endif
   ARE_EQUAL(&writeModeTextFileHandle, returnedWriteModeTextFileHandle);
}

TEST(OpenReadModeBinaryFile_ReturnsFileHandleOpenedInBinaryReadMode)
{
   FILE readModeBinaryFileHandle;
#ifdef __linux__
   fopenMock.Return(&readModeBinaryFileHandle);
#elif _WIN32
   _wfsopenMock.Return(&readModeBinaryFileHandle);
#endif
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   FILE* const returnedReadModeBinaryFileHandle = _fileOpenerCloser.OpenReadModeBinaryFile(filePath);
   //
#ifdef __linux__
   METALMOCK(fopenMock.CalledOnceWith(filePath.c_str(), "rb"));
#elif _WIN32
   METALMOCK(_wfsopenMock.CalledOnceWith(filePath.c_str(), L"rb", _SH_DENYWR));
#endif
   ARE_EQUAL(&readModeBinaryFileHandle, returnedReadModeBinaryFileHandle);
}

TEST(OpenReadModeTextFile_ReturnsFileHandleOpenedInTextReadMode)
{
   FILE readModeTextFileHandle;
#ifdef __linux__
   fopenMock.Return(&readModeTextFileHandle);
#elif _WIN32
   _wfsopenMock.Return(&readModeTextFileHandle);
#endif
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   FILE* const returnedReadModeTextFileHandle = _fileOpenerCloser.OpenReadModeTextFile(filePath);
   //
#ifdef __linux__
   METALMOCK(fopenMock.CalledOnceWith(filePath.c_str(), "r"));
#elif _WIN32
   METALMOCK(_wfsopenMock.CalledOnceWith(filePath.c_str(), L"r", _SH_DENYWR));
#endif
   ARE_EQUAL(&readModeTextFileHandle, returnedReadModeTextFileHandle);
}

TEST(OpenAppendModeTextFile_ReturnsFileHandleOpenedInTextAppendMode)
{
   FILE appendModeTextFileHandle;
#ifdef __linux__
   fopenMock.Return(&appendModeTextFileHandle);
#elif _WIN32
   _wfsopenMock.Return(&appendModeTextFileHandle);
#endif
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   FILE* const returnedAppendModeTextFileHandle = _fileOpenerCloser.OpenAppendModeTextFile(filePath);
   //
#ifdef __linux__
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
   _fileOpenerCloser.ThrowFileOpenExceptionIfFileOpenFailed(&nonNullFileHandle, filePath);
}

RUN_TESTS(FileOpenerCloserTests)
