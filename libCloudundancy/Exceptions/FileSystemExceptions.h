#pragma once

namespace Utils
{
   string MakeFilePathReasonExceptionMessage(const fs::path& filePath, string_view reason);
   string MakeFilePathErrnoDescriptionExceptionMessage(const fs::path& filePath, int errnoValue, string_view errnoDescription);
   string MakeFilePathLineNumberReasonExceptionMessage(const fs::path& filePath, size_t lineNumber, string_view reason);

   class FileNotFoundException : public runtime_error
   {
   public:
      explicit FileNotFoundException(const fs::path& filePath);
   };

   class FileOpenException : public runtime_error
   {
   public:
      FileOpenException(const fs::path& filePath, int errnoValue, string_view errnoDescription);
   };

   class FileMalformedException : public runtime_error
   {
   public:
      FileMalformedException(const fs::path& filePath, string_view reason);
      FileMalformedException(const fs::path& filePath, size_t lineNumber, string_view reason);
   };
}
