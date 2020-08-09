#include "pch.h"
#include "libCloudundancy/Components/FileSystem/FileSystemException.h"
#include "libCloudundancy/Components/Strings/StringUtil.h"

FileSystemException::FileSystemException(
   FileSystemExceptionType fileSystemExceptionType, const fs::path& filePath)
   : _exceptionMessage(String::Concat(
      ENUM_TO_STRING(FileSystemExceptionType, fileSystemExceptionType), " for file ", filePath.string()))
{
}

FileSystemException::FileSystemException(
   FileSystemExceptionType fileSystemExceptionType, const fs::path& filePath, string_view exceptionMessage)
   : _exceptionMessage(String::Concat(
      ENUM_TO_STRING(FileSystemExceptionType, fileSystemExceptionType), " for file ", filePath.string(), ": ", exceptionMessage))
{
}

FileSystemException::FileSystemException(
   FileSystemExceptionType fileSystemExceptionType, const fs::path& filePath, size_t lineNumber, string_view exceptionMessage)
   : _exceptionMessage(String::Concat(
      ENUM_TO_STRING(FileSystemExceptionType, fileSystemExceptionType), " at ", filePath.string(), " line ", lineNumber, ": ", exceptionMessage))
{
}

const char* FileSystemException::what() const noexcept
{
   return _exceptionMessage.c_str();
}
