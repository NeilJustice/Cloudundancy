#include "pch.h"
#include "libCloudundancy/Exceptions/FileSystemExceptions.h"

namespace Utils
{
   string MakeFilePathReasonExceptionMessage(const fs::path& filePath, string_view reason)
   {
      string exceptionMessage = Utils::String::ConcatStrings(filePath.string(), ": ", reason);
      return exceptionMessage;
   }

   string MakeFilePathErrnoDescriptionExceptionMessage(const fs::path& filePath, int errnoValue, string_view errnoDescription)
   {
      string exceptionMessage = Utils::String::ConcatValues(filePath.string(), ": errno=", errnoValue, " (", errnoDescription, ")");
      return exceptionMessage;
   }

   string MakeFilePathLineNumberReasonExceptionMessage(const fs::path& filePath, size_t lineNumber, string_view reason)
   {
      string exceptionMessage = Utils::String::ConcatValues(filePath.string(), '(', lineNumber, "): ", reason);
      return exceptionMessage;
   }

   FileNotFoundException::FileNotFoundException(const fs::path& filePath)
      : runtime_error(filePath.string())
   {
   }

	FileOpenException::FileOpenException(const fs::path& filePath, int errnoValue, string_view errnoDescription)
		: runtime_error(MakeFilePathErrnoDescriptionExceptionMessage(filePath, errnoValue, errnoDescription))
	{
	}

   FileMalformedException::FileMalformedException(const fs::path& filePath, string_view reason)
      : runtime_error(MakeFilePathReasonExceptionMessage(filePath, reason))
   {

   }

	FileMalformedException::FileMalformedException(const fs::path& filePath, size_t lineNumber, string_view reason)
		: runtime_error(MakeFilePathLineNumberReasonExceptionMessage(filePath, lineNumber, reason))
	{
	}
}
