#include "pch.h"
#include "libCloudundancy/Components/ErrorHandling/ErrorCodeTranslator.h"
#include "libCloudundancy/UtilityComponents/FileSystem/FileOpenerCloser.h"

FileOpenerCloser::FileOpenerCloser()
   // Function Pointers
   : _call_fclose(fclose)
#if defined __linux__ || defined __APPLE__
   , _call_fopen(fopen)
#elif _WIN32
   , _call_wfsopen(_wfsopen)
#endif
   // Constant Components
   , _errorCodeTranslator(make_unique<ErrorCodeTranslator>())
{
}

FileOpenerCloser::~FileOpenerCloser()
{
}

FILE* FileOpenerCloser::CreateWriteModeBinaryFile(const fs::path& filePath) const
{
#if defined __linux__ || defined __APPLE__
   FILE* const writeModeBinaryFileHandle = OpenFileOnLinux(filePath, "wb");
#elif _WIN32
   FILE* const writeModeBinaryFileHandle = OpenFileOnWindows(filePath, L"wb");
#endif
   return writeModeBinaryFileHandle;
}

FILE* FileOpenerCloser::CreateWriteModeTextFile(const fs::path& filePath) const
{
#if defined __linux__ || defined __APPLE__
   FILE* const writeModeTextFileHandle = OpenFileOnLinux(filePath, "w");
#elif _WIN32
   FILE* const writeModeTextFileHandle = OpenFileOnWindows(filePath, L"w");
#endif
   return writeModeTextFileHandle;
}

FILE* FileOpenerCloser::OpenReadModeBinaryFile(const fs::path& filePath) const
{
#if defined __linux__ || defined __APPLE__
   FILE* const readModeBinaryFileHandle = OpenFileOnLinux(filePath, "rb");
#elif _WIN32
   FILE* const readModeBinaryFileHandle = OpenFileOnWindows(filePath, L"rb");
#endif
   return readModeBinaryFileHandle;
}

FILE* FileOpenerCloser::OpenReadModeTextFile(const fs::path& filePath) const
{
#if defined __linux__ || defined __APPLE__
   FILE* const readModeTextFileHandle = OpenFileOnLinux(filePath, "r");
#elif _WIN32
   FILE* const readModeTextFileHandle = OpenFileOnWindows(filePath, L"r");
#endif
   return readModeTextFileHandle;
}

FILE* FileOpenerCloser::OpenAppendModeTextFile(const fs::path& filePath) const
{
#if defined __linux__ || defined __APPLE__
   FILE* const appendModeTextFileHandle = OpenFileOnLinux(filePath, "a");
#elif _WIN32
   FILE* const appendModeTextFileHandle = OpenFileOnWindows(filePath, L"a");
#endif
   return appendModeTextFileHandle;
}

void FileOpenerCloser::CloseFile(FILE* fileHandle) const
{
   const int fcloseReturnValue = _call_fclose(fileHandle);
   if (fcloseReturnValue != 0)
   {
      const pair<int, string> errnoWithDescription = _errorCodeTranslator->GetErrnoWithDescription();
      const string exceptionMessage = String::ConcatValues("fclose(FILE*) unexpectedly returned ", fcloseReturnValue,
         ". errno=", errnoWithDescription.first, " (", errnoWithDescription.second, ")");
      throw runtime_error(exceptionMessage);
   }
}

// Private Functions

#if defined __linux__ || defined __APPLE__

FILE* FileOpenerCloser::OpenFileOnLinux(const fs::path& filePath, const char* fileOpenMode) const
{
   FILE* const fileHandle = _call_fopen(filePath.c_str(), fileOpenMode);
   ThrowFileOpenExceptionIfFileOpenFailed(fileHandle, filePath);
   return fileHandle;
}

#elif _WIN32

FILE* FileOpenerCloser::OpenFileOnWindows(const fs::path& filePath, const wchar_t* fileOpenMode) const
{
   FILE* const fileHandle = _call_wfsopen(filePath.c_str(), fileOpenMode, _SH_DENYWR);
   ThrowFileOpenExceptionIfFileOpenFailed(fileHandle, filePath);
   return fileHandle;
}

#endif

void FileOpenerCloser::ThrowFileOpenExceptionIfFileOpenFailed(FILE* fileHandle, const fs::path& filePath) const
{
   if (fileHandle == nullptr)
   {
      const pair<int, string> errnoWithDescription = _errorCodeTranslator->GetErrnoWithDescription();
      const string exceptionMessage = String::ConcatValues("fopen() returned nullptr. filePath=\"",
         filePath.string(), "\". errno=", errnoWithDescription.first, " (", errnoWithDescription.second, ")");
      throw runtime_error(exceptionMessage);
   }
}
