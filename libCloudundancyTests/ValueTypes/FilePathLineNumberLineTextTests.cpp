#include "pch.h"
#include "libCloudundancy/ValueTypes/FilePathLineNumberLineText.h"

TESTS(FilePathLineNumberLineTextTests)
AFACT(DefaultConstructor_SetsFieldsToDefaults)
AFACT(ThreeArgumentConstructor_SetsFields)
AFACT(Equalizer_ThrowsIfAnyFieldNotEqual)
EVIDENCE

TEST(DefaultConstructor_SetsFieldsToDefaults)
{
   const FilePathLineNumberLineText filePathLineNumberLineText;
   ARE_EQUAL(fs::path(), filePathLineNumberLineText.filePath);
   ARE_EQUAL(0, filePathLineNumberLineText.lineNumber);
   ARE_EQUAL("", filePathLineNumberLineText.lineText);
}

TEST(ThreeArgumentConstructor_SetsFields)
{
   const fs::path filePath = ZenUnit::RandomRelativeFilePath();
   const size_t lineNumber = ZenUnit::Random<size_t>();
   const string lineText = ZenUnit::Random<string>();
   //
   const FilePathLineNumberLineText filePathLineNumberLineText(filePath, lineNumber, lineText);
   //
   ARE_EQUAL(filePath, filePathLineNumberLineText.filePath);
   ARE_EQUAL(lineNumber, filePathLineNumberLineText.lineNumber);
   ARE_EQUAL(lineText, filePathLineNumberLineText.lineText);
}

TEST(Equalizer_ThrowsIfAnyFieldNotEqual)
{
   SETUP_EQUALIZER_TEST(FilePathLineNumberLineText);
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FilePathLineNumberLineText, filePath, ZenUnit::Random<fs::path>());
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FilePathLineNumberLineText, lineNumber, ZenUnit::RandomNon0<int>());
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FilePathLineNumberLineText, lineText, ZenUnit::Random<string>());
}

RUN_TESTS(FilePathLineNumberLineTextTests)
