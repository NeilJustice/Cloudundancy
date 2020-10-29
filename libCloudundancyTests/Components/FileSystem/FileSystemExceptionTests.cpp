#include "pch.h"
#include "libCloudundancy/Components/FileSystem/FileSystemException.h"

TESTS(FileExceptionTests)
AFACT(TwoArgConstructor_MakesWhatFunctionReturnExpectedExceptionMessage)
AFACT(ThreeArgConstructor_MakesWhatFunctionReturnExpectedExceptionMessage)
AFACT(FourArgConstructor_MakesWhatFunctionReturnExpectedExceptionMessage)
EVIDENCE

TEST(TwoArgConstructor_MakesWhatFunctionReturnExpectedExceptionMessage)
{
   const FileSystemExceptionType fileSystemExceptionType =
      ZenUnit::RandomEnum<FileSystemExceptionType>(FileSystemExceptionType::MaxValue);
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const FileSystemException fileSystemException(fileSystemExceptionType, filePath);
   const char* const fullExceptionMessage = fileSystemException.what();
   //
   const string expectedFullExceptionMessage = String::Concat(
      ENUM_TO_STRING(FileSystemExceptionType, fileSystemExceptionType), ": ", filePath.string());
   ARE_EQUAL(expectedFullExceptionMessage, fullExceptionMessage);
}

TEST(ThreeArgConstructor_MakesWhatFunctionReturnExpectedExceptionMessage)
{
   const FileSystemExceptionType fileSystemExceptionType = ZenUnit::RandomEnum<FileSystemExceptionType>(FileSystemExceptionType::MaxValue);
   const fs::path filePath = ZenUnit::Random<fs::path>();
   const string exceptionMessage = ZenUnit::Random<string>();
   //
   const FileSystemException fileSystemException(
      fileSystemExceptionType,
      filePath,
      exceptionMessage);
   const char* const fullExceptionMessage = fileSystemException.what();
   //
   const string expectedFullExceptionMessage = String::Concat(
      ENUM_TO_STRING(FileSystemExceptionType, fileSystemExceptionType), ": ", filePath.string(), ": ", exceptionMessage);
   ARE_EQUAL(expectedFullExceptionMessage, fullExceptionMessage);
}

TEST(FourArgConstructor_MakesWhatFunctionReturnExpectedExceptionMessage)
{
   const FileSystemExceptionType fileSystemExceptionType = ZenUnit::RandomEnum<FileSystemExceptionType>(FileSystemExceptionType::MaxValue);
   const fs::path filePath = ZenUnit::Random<fs::path>();
   const size_t lineNumber = ZenUnit::Random<size_t>();
   const string exceptionMessage = ZenUnit::Random<string>();
   //
   const FileSystemException fileSystemException(
      fileSystemExceptionType,
      filePath,
      lineNumber,
      exceptionMessage);
   const char* const fullExceptionMessage = fileSystemException.what();
   //
   const string expectedFullExceptionMessage = String::Concat(
      ENUM_TO_STRING(FileSystemExceptionType, fileSystemExceptionType),
      " at ", filePath.string(), " line ", lineNumber, ": ", exceptionMessage);
   ARE_EQUAL(expectedFullExceptionMessage, fullExceptionMessage);
}

RUN_TESTS(FileExceptionTests)
