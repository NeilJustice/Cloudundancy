#pragma once

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

BEGIN_ENUM_STRING_ARRAY(FileSystemExceptionType)
ENUM_STRING_ARRAY_ELEMENT(Unset)
ENUM_STRING_ARRAY_ELEMENT(CloseFileFailed)
ENUM_STRING_ARRAY_ELEMENT(DeleteFolderFailed)
ENUM_STRING_ARRAY_ELEMENT(DeleteFileFailed)
ENUM_STRING_ARRAY_ELEMENT(FileCannotBeEmpty)
ENUM_STRING_ARRAY_ELEMENT(FileDoesNotExist)
ENUM_STRING_ARRAY_ELEMENT(FileOrFolderDoesNotExist)
ENUM_STRING_ARRAY_ELEMENT(FolderDoesNotExist)
ENUM_STRING_ARRAY_ELEMENT(MalformedFile)
ENUM_STRING_ARRAY_ELEMENT(OpenFileFailed)
ENUM_STRING_ARRAY_ELEMENT(RenameFolderFailed)
ENUM_STRING_ARRAY_ELEMENT(Windows_SetFileAttributeFailed)
ENUM_STRING_ARRAY_ELEMENT(Windows_FindFirstFileExFailed)
ENUM_STRING_ARRAY_ELEMENT(MaxValue)
END_ENUM_STRING_ARRAY
