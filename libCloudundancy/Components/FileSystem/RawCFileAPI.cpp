#include "pch.h"
#include "libCloudundancy/Components/FileSystem/RawCFileAPI.h"
#ifdef _WIN32
#pragma warning(disable: 4996) // warning STL4017: std::wbuffer_convert, std::wstring_convert, and the <codecvt> header (containing std::codecvt_mode, std::codecvt_utf8, std::codecvt_utf16, and std::codecvt_utf8_utf16) are deprecated in C++17.
#endif
#include <codecvt>
#include <locale>

namespace Utils
{
   // LCOV_EXCL_START

#ifdef __linux__

   FILE* RawCFileAPI::fopen(const fs::path& filePath, const char* fileOpenMode) const
   {
      FILE* rawFilePointer = ::fopen(filePath.c_str(), fileOpenMode);
      return rawFilePointer;
   }

#elif _WIN32

   FILE* RawCFileAPI::wfsopen(const fs::path& filePath, const char* fileOpenMode, int fileOpenFlags) const
   {
      wstring_convert<codecvt_utf8_utf16<wchar_t>> narrowToWideConverter;
      const wstring fileOpenModeWideString = narrowToWideConverter.from_bytes(fileOpenMode);
      FILE* rawFilePointer = ::_wfsopen(filePath.c_str(), fileOpenModeWideString.c_str(), fileOpenFlags);
      return rawFilePointer;
   }

#endif

   size_t RawCFileAPI::fread(char* outBuffer, size_t numberOfBytesToRead, FILE* filePointer) const
   {
      size_t numberOfBytesRead = ::fread(outBuffer, 1, numberOfBytesToRead, filePointer);
      return numberOfBytesRead;
   }

   size_t RawCFileAPI::fwrite(const char* bytes, size_t bytesSize, FILE* filePointer) const
   {
      size_t numberOfBytesWritten = ::fwrite(bytes, 1, bytesSize, filePointer);
      return numberOfBytesWritten;
   }

   int RawCFileAPI::fflush(FILE* filePointer) const
   {
      int fflushReturnVlaue = ::fflush(filePointer);
      return fflushReturnVlaue;
   }

   // LCOV_EXCL_STOP
}
