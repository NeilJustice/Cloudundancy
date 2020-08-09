#include "pch.h"
#include "libCloudundancy/ValueTypes/FilePathLineNumberLineText.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/FilePathLineNumberLineTextEqualizer.h"

TESTS(FilePathLineNumberLineTextEqualizerTests)
AFACT(AssertEqual_ThrowsIfAnyFieldNotEqual)
EVIDENCE

TEST(AssertEqual_ThrowsIfAnyFieldNotEqual)
{
   SETUP_EQUALIZER_TEST(FilePathLineNumberLineText);
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FilePathLineNumberLineText, filePath, ZenUnit::Random<fs::path>());
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FilePathLineNumberLineText, lineNumber, ZenUnit::RandomNon0<long>());
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(FilePathLineNumberLineText, lineText, ZenUnit::Random<string>());
}

RUN_TESTS(FilePathLineNumberLineTextEqualizerTests)
