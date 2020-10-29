#include "pch.h"

TESTS(FileSystemExceptionTypeTests)
AFACT(OStreamLeftShiftOperator_FileSystemExceptionTypeValueIsWithinRange_WritesFileSystemExceptionTypeAsString)
AFACT(OStreamLeftShiftOperator_FileSystemExceptionTypeValueIsNotWithinRange_WritesFileSystemExceptionTypeAsInt)
EVIDENCE

TEST(OStreamLeftShiftOperator_FileSystemExceptionTypeValueIsWithinRange_WritesFileSystemExceptionTypeAsString)
{
   ostringstream oss;
   const FileSystemExceptionType firstFileSystemExceptionTypeValue =
      ZenUnit::RandomEnum<FileSystemExceptionType>(FileSystemExceptionType::MaxValue);
   const FileSystemExceptionType secondFileSystemExceptionTypeValue =
      ZenUnit::RandomEnum<FileSystemExceptionType>(FileSystemExceptionType::MaxValue);
   //
   oss << firstFileSystemExceptionTypeValue << secondFileSystemExceptionTypeValue;
   //
   const string ossString = oss.str();
   const string expectedOssString =
      ENUM_TO_STRING(FileSystemExceptionType, firstFileSystemExceptionTypeValue) +
      ENUM_TO_STRING(FileSystemExceptionType, secondFileSystemExceptionTypeValue);
   ARE_EQUAL(expectedOssString, ossString);
}

TEST(OStreamLeftShiftOperator_FileSystemExceptionTypeValueIsNotWithinRange_WritesFileSystemExceptionTypeAsInt)
{
   ostringstream oss;

   const FileSystemExceptionType firstFileSystemExceptionTypeValue =
      static_cast<FileSystemExceptionType>(ZenUnit::RandomBetween<int>(
         static_cast<int>(FileSystemExceptionType::MaxValue) + 1, static_cast<int>(FileSystemExceptionType::MaxValue) + 3));

   const FileSystemExceptionType secondFileSystemExceptionTypeValue =
      static_cast<FileSystemExceptionType>(ZenUnit::RandomBetween<int>(
         static_cast<int>(FileSystemExceptionType::MaxValue) + 1, static_cast<int>(FileSystemExceptionType::MaxValue) + 3));
   //
   oss << firstFileSystemExceptionTypeValue << secondFileSystemExceptionTypeValue;
   //
   const string ossString = oss.str();
   const string expectedOssString =
      to_string(static_cast<int>(firstFileSystemExceptionTypeValue)) +
      to_string(static_cast<int>(secondFileSystemExceptionTypeValue));
   ARE_EQUAL(expectedOssString, ossString);
}

RUN_TESTS(FileSystemExceptionTypeTests)
