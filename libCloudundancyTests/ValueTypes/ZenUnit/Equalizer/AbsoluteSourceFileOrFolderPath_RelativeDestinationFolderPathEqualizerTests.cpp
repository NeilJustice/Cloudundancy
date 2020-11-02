#include "pch.h"

TESTS(AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPathEqualizerTests)
AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
EVIDENCE

TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
{
   ZENUNIT_EQUALIZER_TEST_SETUP(AbsoluteFileOrFolderPathToRelativeFolderPath);
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(
      AbsoluteFileOrFolderPathToRelativeFolderPath, absoluteSourceFileOrFolderPath, ZenUnit::Random<fs::path>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(
      AbsoluteFileOrFolderPathToRelativeFolderPath, relativeDestinationFolderPath, ZenUnit::Random<fs::path>());
}

RUN_TESTS(AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPathEqualizerTests)
