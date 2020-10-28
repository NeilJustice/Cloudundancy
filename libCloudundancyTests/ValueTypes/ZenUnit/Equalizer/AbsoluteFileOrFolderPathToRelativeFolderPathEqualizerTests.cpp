#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/AbsoluteFileOrFolderPathToRelativeFolderPathEqualizer.h"

TESTS(AbsoluteFileOrFolderPathToRelativeFolderPathEqualizerTests)
AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
EVIDENCE

TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
{
   SETUP_EQUALIZER_TEST(AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath);
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath, absoluteSourceFileOrFolderPath, ZenUnit::Random<fs::path>());
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath, relativeDestinationFolderPath, ZenUnit::Random<fs::path>());
}

RUN_TESTS(AbsoluteFileOrFolderPathToRelativeFolderPathEqualizerTests)
