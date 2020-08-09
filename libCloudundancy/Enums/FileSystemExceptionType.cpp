#include "pch.h"
#include "libCloudundancy/Enums/FileSystemExceptionType.h"

ostream& operator<<(ostream& os, FileSystemExceptionType fileSystemExceptionType)
{
   if (fileSystemExceptionType >= FileSystemExceptionType::Unset &&
       fileSystemExceptionType <= FileSystemExceptionType::MaxValue)
   {
      const string fileSystemExceptionTypeAsString = ENUM_TO_STRING(FileSystemExceptionType, fileSystemExceptionType);
      os << fileSystemExceptionTypeAsString;
   }
   else
   {
      os << static_cast<int>(fileSystemExceptionType);
   }
   return os;
}

INITIALIZE_ENUM_TO_STRING_AND_STRING_TO_ENUM_MAPS(FileSystemExceptionType)
