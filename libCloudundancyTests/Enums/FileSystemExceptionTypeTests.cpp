#include "pch.h"

TESTS(FileSystemExceptionTypeTests)
AFACT(ENUM_AS_STRING_ReturnsExpectedStringForEachEnumValue)
EVIDENCE

TEST(ENUM_AS_STRING_ReturnsExpectedStringForEachEnumValue)
{
   ARE_EQUAL("Unset", ENUM_AS_STRING(FileSystemExceptionType, FileSystemExceptionType::Unset));
   ARE_EQUAL("CloseFileFailed", ENUM_AS_STRING(FileSystemExceptionType, FileSystemExceptionType::CloseFileFailed));
   ARE_EQUAL("DeleteFolderFailed", ENUM_AS_STRING(FileSystemExceptionType, FileSystemExceptionType::DeleteFolderFailed));
   ARE_EQUAL("DeleteFileFailed", ENUM_AS_STRING(FileSystemExceptionType, FileSystemExceptionType::DeleteFileFailed));
   ARE_EQUAL("FileCannotBeEmpty", ENUM_AS_STRING(FileSystemExceptionType, FileSystemExceptionType::FileCannotBeEmpty));
   ARE_EQUAL("FileDoesNotExist", ENUM_AS_STRING(FileSystemExceptionType, FileSystemExceptionType::FileDoesNotExist));
   ARE_EQUAL("FileOrFolderDoesNotExist", ENUM_AS_STRING(FileSystemExceptionType, FileSystemExceptionType::FileOrFolderDoesNotExist));
   ARE_EQUAL("FolderDoesNotExist", ENUM_AS_STRING(FileSystemExceptionType, FileSystemExceptionType::FolderDoesNotExist));
   ARE_EQUAL("MalformedFile", ENUM_AS_STRING(FileSystemExceptionType, FileSystemExceptionType::MalformedFile));
   ARE_EQUAL("OpenFileFailed", ENUM_AS_STRING(FileSystemExceptionType, FileSystemExceptionType::OpenFileFailed));
   ARE_EQUAL("RenameFolderFailed", ENUM_AS_STRING(FileSystemExceptionType, FileSystemExceptionType::RenameFolderFailed));
   ARE_EQUAL("Windows_SetFileAttributeFailed", ENUM_AS_STRING(FileSystemExceptionType, FileSystemExceptionType::Windows_SetFileAttributeFailed));
   ARE_EQUAL("Windows_FindFirstFileExFailed", ENUM_AS_STRING(FileSystemExceptionType, FileSystemExceptionType::Windows_FindFirstFileExFailed));
   ARE_EQUAL("MaxValue", ENUM_AS_STRING(FileSystemExceptionType, FileSystemExceptionType::MaxValue));
}

RUN_TESTS(FileSystemExceptionTypeTests)
