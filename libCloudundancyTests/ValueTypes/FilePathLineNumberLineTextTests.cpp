#include "pch.h"
#include "libCloudundancy/ValueTypes/FilePathLineNumberLineText.h"

TESTS(FilePathLineNumberLineTextTests)
AFACT(DefaultConstructor_SetsFieldsToDefaults)
AFACT(ThreeArgumentConstructor_SetsFields)
EVIDENCE

TEST(DefaultConstructor_SetsFieldsToDefaults)
{
   const FilePathLineNumberLineText defaultFilePathLineNumberLineText;
   FilePathLineNumberLineText expectedDefaultFilePathLineNumberLineText;
   expectedDefaultFilePathLineNumberLineText.filePath = fs::path();
   expectedDefaultFilePathLineNumberLineText.lineNumber = 0;
   expectedDefaultFilePathLineNumberLineText.lineText = "";
   ARE_EQUAL(expectedDefaultFilePathLineNumberLineText, defaultFilePathLineNumberLineText);
}

TEST(ThreeArgumentConstructor_SetsFields)
{
   const fs::path filePath = ZenUnit::Random<fs::path>();
   const size_t lineNumber = ZenUnit::Random<size_t>();
   const string lineText = ZenUnit::Random<string>();
   //
   const FilePathLineNumberLineText filePathLineNumberLineText(filePath, lineNumber, lineText);
   //
   FilePathLineNumberLineText expectedFilePathLineNumberLineText;
   expectedFilePathLineNumberLineText.filePath = filePath;
   expectedFilePathLineNumberLineText.lineNumber = lineNumber;
   expectedFilePathLineNumberLineText.lineText = lineText;
   ARE_EQUAL(expectedFilePathLineNumberLineText, filePathLineNumberLineText);
}

RUN_TESTS(FilePathLineNumberLineTextTests)
