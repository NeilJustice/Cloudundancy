#include "pch.h"
#include "libCloudundancy/Components/Assertion/Asserter.h"
#include "libCloudundancy/Components/FileSystem/FileOpenerCloser.h"

FileOpenerCloser::FileOpenerCloser()
   : _asserter(make_unique<Asserter>())
#ifdef __linux__
   , _call_fopen(::fopen)
#elif _WIN32
   , _call_wfopen(::_wfopen)
#endif
   , _call_fclose(::fclose)
{
}

FileOpenerCloser::~FileOpenerCloser()
{
}

void FileOpenerCloser::CloseFile(FILE* filePointer) const
{
   const int fcloseReturnValue = _call_fclose(filePointer);
   _asserter->ThrowIfNotEqual(0, fcloseReturnValue,
      "fclose(filePointer) in FileOpenerCloser::CloseFile() unexpectedly returned a non-0 value");
}

FILE* FileOpenerCloser::OpenTextFileInReadMode(const fs::path& filePath) const
{
#ifdef __linux__
   FILE* const filePointer = OpenFileOnLinux(filePath, "r");
#elif _WIN32
   FILE* const filePointer = OpenFileOnWindows(filePath, L"r");
#endif
   return filePointer;
}

FILE* FileOpenerCloser::CreateTextFileInWriteMode(const fs::path& filePath) const
{
#ifdef __linux__
   FILE* const filePointer = OpenFileOnLinux(filePath, "w");
#elif _WIN32
   FILE* const filePointer = OpenFileOnWindows(filePath, L"w");
#endif
   return filePointer;
}

FILE* FileOpenerCloser::OpenBinaryFileInReadMode(const fs::path& filePath) const
{
#ifdef __linux__
   FILE* const filePointer = OpenFileOnLinux(filePath, "rb");
#elif _WIN32
   FILE* const filePointer = OpenFileOnWindows(filePath, L"rb");
#endif
   return filePointer;
}

FILE* FileOpenerCloser::CreateBinaryFileInWriteMode(const fs::path& filePath) const
{
#ifdef __linux__
   FILE* const filePointer = OpenFileOnLinux(filePath, "wb");
#elif _WIN32
   FILE* const filePointer = OpenFileOnWindows(filePath, L"wb");
#endif
   return filePointer;
}

// Private Functions

#ifdef __linux__

FILE* FileOpenerCloser::OpenFileOnLinux(const fs::path& filePath, const char* fileOpenMode) const
{
   FILE* const filePointer = _call_fopen(filePath.c_str(), fileOpenMode);
   ThrowFileOpenExceptionIfFileOpenFailed(filePointer, filePath);
   return filePointer;
}

#elif _WIN32

FILE* FileOpenerCloser::OpenFileOnWindows(const fs::path& filePath, const wchar_t* fileOpenMode) const
{
   FILE* const filePointer = _call_wfopen(filePath.c_str(), fileOpenMode);
   ThrowFileOpenExceptionIfFileOpenFailed(filePointer, filePath);
   return filePointer;
}

#endif

void FileOpenerCloser::ThrowFileOpenExceptionIfFileOpenFailed(FILE* filePointer, const fs::path& filePath) const
{
   if (filePointer == nullptr)
   {
      const string exceptionMessage = "fopen() returned nullptr. filePath=\"" + filePath.string() + "\"";
      throw runtime_error(exceptionMessage);
   }
}
