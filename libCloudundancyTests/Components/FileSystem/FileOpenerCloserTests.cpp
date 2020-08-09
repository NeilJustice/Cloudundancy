#include "pch.h"
#include "libCloudundancy/Components/FileSystem/FileOpenerCloser.h"

TESTS(FileOpenerCloserTests)
AFACT(DefaultConstructor_SetsFunctionPointers)
AFACT(OpenTextFileInReadMode_ReturnsFilePointerOpenedInTextReadMode)
AFACT(CreateTextFileInWriteMode_ReturnsFilePointerOpenedInTextWriteMode)
AFACT(OpenBinaryFileInReadMode_ReturnsFilePointerOpenedInBinaryReadMode)
AFACT(CreateBinaryFileInWriteMode_ReturnsFilePointerOpenedInBinaryWriteMode)
AFACT(CloseFile_CallsFCloseOnFileHandle)
// Private Functions
AFACT(ThrowFileOpenExceptionIfFileOpenFailed_FileHandleIsNullptr_ThrowsFileOpenException)
AFACT(ThrowFileOpenExceptionIfFileOpenFailed_FileHandleIsNotNullptr_DoesNotThrowException)
EVIDENCE

FileOpenerCloser _fileOpenerCloser;
AsserterMock* _asserterMock = nullptr;
ZENMOCK_NONVOID1_FREE(int, fclose, FILE*)
#ifdef __linux__
ZENMOCK_NONVOID2_FREE(FILE*, fopen, const char*, const char*)
#elif _WIN32
ZENMOCK_NONVOID2_FREE(FILE*, _wfopen, const wchar_t*, const wchar_t*)
#endif

STARTUP
{
   _fileOpenerCloser._asserter.reset(_asserterMock = new AsserterMock);
   _fileOpenerCloser._call_fclose = BIND_1ARG_ZENMOCK_OBJECT(fcloseMock);
#ifdef __linux__
   _fileOpenerCloser._call_fopen = BIND_2ARG_ZENMOCK_OBJECT(fopenMock);
#elif _WIN32
   _fileOpenerCloser._call_wfopen = BIND_2ARG_ZENMOCK_OBJECT(_wfopenMock);
#endif
}

TEST(DefaultConstructor_SetsFunctionPointers)
{
   FileOpenerCloser fileOpenerCloser;
   STD_FUNCTION_TARGETS(::fclose, fileOpenerCloser._call_fclose);
#ifdef __linux__
   STD_FUNCTION_TARGETS(::fopen, fileOpenerCloser._call_fopen);
#elif _WIN32
   STD_FUNCTION_TARGETS(::_wfopen, fileOpenerCloser._call_wfopen);
#endif
}

TEST(OpenTextFileInReadMode_ReturnsFilePointerOpenedInTextReadMode)
{
   FILE filePointer;
#ifdef __linux__
   fopenMock.Return(&filePointer);
#elif _WIN32
   _wfopenMock.Return(&filePointer);
#endif
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   _fileOpenerCloser.OpenTextFileInReadMode(filePath);
   //
#ifdef __linux__
   ZENMOCK(fopenMock.CalledOnceWith(filePath.c_str(), "r"));
#elif _WIN32
   ZENMOCK(_wfopenMock.CalledOnceWith(filePath.c_str(), L"r"));
#endif
}

TEST(CreateTextFileInWriteMode_ReturnsFilePointerOpenedInTextWriteMode)
{
   FILE filePointer;
#ifdef __linux__
   fopenMock.Return(&filePointer);
#elif _WIN32
   _wfopenMock.Return(&filePointer);
#endif
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   _fileOpenerCloser.CreateTextFileInWriteMode(filePath);
   //
#ifdef __linux__
   ZENMOCK(fopenMock.CalledOnceWith(filePath.c_str(), "w"));
#elif _WIN32
   ZENMOCK(_wfopenMock.CalledOnceWith(filePath.c_str(), L"w"));
#endif
}

TEST(OpenBinaryFileInReadMode_ReturnsFilePointerOpenedInBinaryReadMode)
{
   FILE filePointer;
#ifdef __linux__
   fopenMock.Return(&filePointer);
#elif _WIN32
   _wfopenMock.Return(&filePointer);
#endif
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   _fileOpenerCloser.OpenBinaryFileInReadMode(filePath);
   //
#ifdef __linux__
   ZENMOCK(fopenMock.CalledOnceWith(filePath.c_str(), "rb"));
#elif _WIN32
   ZENMOCK(_wfopenMock.CalledOnceWith(filePath.c_str(), L"rb"));
#endif
}

TEST(CreateBinaryFileInWriteMode_ReturnsFilePointerOpenedInBinaryWriteMode)
{
   FILE filePointer;
#ifdef __linux__
   fopenMock.Return(&filePointer);
#elif _WIN32
   _wfopenMock.Return(&filePointer);
#endif
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   _fileOpenerCloser.CreateBinaryFileInWriteMode(filePath);
   //
#ifdef __linux__
   ZENMOCK(fopenMock.CalledOnceWith(filePath.c_str(), "wb"));
#elif _WIN32
   ZENMOCK(_wfopenMock.CalledOnceWith(filePath.c_str(), L"wb"));
#endif
}

TEST(CloseFile_CallsFCloseOnFileHandle)
{
   const int fcloseReturnValue = fcloseMock.ReturnRandom();
   _asserterMock->ThrowIfNotEqualMock.Expect();
   FILE fileHandle{};
   //
   _fileOpenerCloser.CloseFile(&fileHandle);
   //
   ZENMOCK(fcloseMock.CalledOnceWith(&fileHandle));
   ZENMOCK(_asserterMock->ThrowIfNotEqualMock.CalledOnceWith(0, fcloseReturnValue,
      "fclose(filePointer) in FileOpenerCloser::CloseFile() unexpectedly returned a non-0 value"));
}

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
   FILE nonNullFilePointer{};
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   _fileOpenerCloser.ThrowFileOpenExceptionIfFileOpenFailed(&nonNullFilePointer, filePath);
}

RUN_TESTS(FileOpenerCloserTests)
