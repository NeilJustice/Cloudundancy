#include "pch.h"
#include "libCloudundancy/Exceptions/FileSystemExceptions.h"

TESTS(FileSystemExceptionsTests)
AFACT(FileNotFoundException_WhatReturnsExpectedText)
AFACT(FileOpenException_WhatReturnsExpected)
AFACT(FileMalformedException_NonLineNumberOverload_WhatReturnsExpected)
AFACT(FileMalformedException_LineNumberOverload_WhatReturnsExpected)
EVIDENCE

TEST(FileNotFoundException_WhatReturnsExpectedText)
{
   const fs::path filePath = ZenUnit::Random<fs::path>();
   //
   const Utils::FileNotFoundException ex(filePath);
   //
   const string expectedExceptionMessage = filePath.string();
   const string actualExceptionMessage = ex.what();
   ARE_EQUAL(expectedExceptionMessage, actualExceptionMessage);
}

TEST(FileOpenException_WhatReturnsExpected)
{
   const fs::path filePath = ZenUnit::Random<fs::path>();
   const int errnoValue = ZenUnit::Random<int>();
   const string errnoDescription = ZenUnit::Random<string>();
   //
   const Utils::FileOpenException ex(filePath, errnoValue, errnoDescription);
   //
   const string expectedExceptionMessage = Utils::String::ConcatValues(filePath.string(), ": errno=", errnoValue, " (", errnoDescription, ")");
   const string actualExceptionMessage = ex.what();
   ARE_EQUAL(expectedExceptionMessage, actualExceptionMessage);
}

TEST(FileMalformedException_NonLineNumberOverload_WhatReturnsExpected)
{
   const fs::path filePath = ZenUnit::Random<fs::path>();
   const string reason = ZenUnit::Random<string>();
   //
   const Utils::FileMalformedException ex(filePath, reason);
   //
   const string expectedExceptionMessage = Utils::String::ConcatStrings(filePath.string(), ": ", reason);
   const string actualExceptionMessage = ex.what();
   ARE_EQUAL(expectedExceptionMessage, actualExceptionMessage);
}

TEST(FileMalformedException_LineNumberOverload_WhatReturnsExpected)
{
   const fs::path filePath = ZenUnit::Random<fs::path>();
   const string reason = ZenUnit::Random<string>();
   const size_t lineNumber = ZenUnit::Random<size_t>();
   //
   const Utils::FileMalformedException ex(filePath, lineNumber, reason);
   //
   const string expectedExceptionMessage = Utils::String::ConcatValues(filePath.string(), '(', lineNumber, "): ", reason);
   const string actualExceptionMessage = ex.what();
   ARE_EQUAL(expectedExceptionMessage, actualExceptionMessage);
}

RUN_TESTS(FileSystemExceptionsTests)
