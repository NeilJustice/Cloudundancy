#pragma once
#include "libCloudundancy/StaticUtilities/STRING_ENUM_MAP.h"

enum class FileSystemExceptionType : unsigned char
{
   Unset,
   CloseFileFailed,
   DeleteFolderFailed,
   DeleteFileFailed,
   FileCannotBeEmpty,
   FileDoesNotExist,
   FileOrFolderDoesNotExist,
   FolderDoesNotExist,
   MalformedFile,
   OpenFileFailed,
   RenameFolderFailed,
   Windows_SetFileAttributeFailed,
   Windows_FindFirstFileExFailed,
   MaxValue
};

ostream& operator<<(ostream& os, FileSystemExceptionType fileSystemExceptionType);

BEGIN_STRING_ENUM_MAP(FileSystemExceptionType)
   ADD_ENUM_TO_STRING_AND_STRING_TO_ENUM_MAPPINGS(FileSystemExceptionType, Unset)
   ADD_ENUM_TO_STRING_AND_STRING_TO_ENUM_MAPPINGS(FileSystemExceptionType, CloseFileFailed)
   ADD_ENUM_TO_STRING_AND_STRING_TO_ENUM_MAPPINGS(FileSystemExceptionType, DeleteFolderFailed)
   ADD_ENUM_TO_STRING_AND_STRING_TO_ENUM_MAPPINGS(FileSystemExceptionType, DeleteFileFailed)
   ADD_ENUM_TO_STRING_AND_STRING_TO_ENUM_MAPPINGS(FileSystemExceptionType, FileCannotBeEmpty)
   ADD_ENUM_TO_STRING_AND_STRING_TO_ENUM_MAPPINGS(FileSystemExceptionType, FileDoesNotExist)
   ADD_ENUM_TO_STRING_AND_STRING_TO_ENUM_MAPPINGS(FileSystemExceptionType, FileOrFolderDoesNotExist)
   ADD_ENUM_TO_STRING_AND_STRING_TO_ENUM_MAPPINGS(FileSystemExceptionType, FolderDoesNotExist)
   ADD_ENUM_TO_STRING_AND_STRING_TO_ENUM_MAPPINGS(FileSystemExceptionType, MalformedFile)
   ADD_ENUM_TO_STRING_AND_STRING_TO_ENUM_MAPPINGS(FileSystemExceptionType, OpenFileFailed)
   ADD_ENUM_TO_STRING_AND_STRING_TO_ENUM_MAPPINGS(FileSystemExceptionType, RenameFolderFailed)
   ADD_ENUM_TO_STRING_AND_STRING_TO_ENUM_MAPPINGS(FileSystemExceptionType, Windows_SetFileAttributeFailed)
   ADD_ENUM_TO_STRING_AND_STRING_TO_ENUM_MAPPINGS(FileSystemExceptionType, Windows_FindFirstFileExFailed)
   ADD_ENUM_TO_STRING_AND_STRING_TO_ENUM_MAPPINGS(FileSystemExceptionType, MaxValue)
END_STRING_ENUM_MAP
