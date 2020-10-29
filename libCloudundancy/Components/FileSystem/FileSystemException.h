#pragma once

class FileSystemException : public exception
{
private:
   const string _exceptionMessage;
public:
   FileSystemException(FileSystemExceptionType fileSystemExceptionType, const fs::path& filePath);
   FileSystemException(FileSystemExceptionType fileSystemExceptionType, const fs::path& filePath, string_view exceptionMessage);
   FileSystemException(FileSystemExceptionType fileSystemExceptionType, const fs::path& filePath, size_t lineNumber, string_view exceptionMessage);
   const char* what() const noexcept override;
};
