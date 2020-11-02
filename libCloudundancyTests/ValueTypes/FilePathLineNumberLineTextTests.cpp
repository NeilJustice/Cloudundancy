#include "pch.h"
#include "libCloudundancy/ValueTypes/FilePathLineNumberLineText.h"

TESTS(FilePathLineNumberLineTextTests)
AFACT(DefaultConstructor_SetsFieldsToDefaults)
AFACT(ThreeArgumentConstructor_SetsFields)
AFACT(Equalizer_ThrowsIfAnyFieldNotEqual)
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
   const fs::path filePath = ZenUnit::RandomRelativeFilePath();
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

TEST(Equalizer_ThrowsIfAnyFieldNotEqual)
{
   ZENUNIT_EQUALIZER_TEST_SETUP(FilePathLineNumberLineText);
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FilePathLineNumberLineText, filePath, ZenUnit::Random<fs::path>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FilePathLineNumberLineText, lineNumber, ZenUnit::RandomNon0<int>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FilePathLineNumberLineText, lineText, ZenUnit::Random<string>());
}

RUN_TESTS(FilePathLineNumberLineTextTests)
