#include "pch.h"
#include "libCloudundancy/ValueTypes/FilePathLineNumberLineText.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/FilePathLineNumberLineTextEqualizer.h"

TESTS(FilePathLineNumberLineTextEqualizerTests)
AFACT(AssertEqual_ThrowsIfAnyFieldNotEqual)
EVIDENCE

TEST(AssertEqual_ThrowsIfAnyFieldNotEqual)
{
   ZENUNIT_EQUALIZER_TEST_SETUP(FilePathLineNumberLineText);
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FilePathLineNumberLineText, filePath, ZenUnit::Random<fs::path>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FilePathLineNumberLineText, lineNumber, ZenUnit::RandomNon0<size_t>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FilePathLineNumberLineText, lineText, ZenUnit::Random<string>());
}

RUN_TESTS(FilePathLineNumberLineTextEqualizerTests)
