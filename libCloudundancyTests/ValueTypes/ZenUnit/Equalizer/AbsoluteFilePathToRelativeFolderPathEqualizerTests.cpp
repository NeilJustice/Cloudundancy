#include "pch.h"
#include "libCloudundancy/ValueTypes/AbsoluteFilePathToRelativeFolderPath.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/AbsoluteFilePathToRelativeFolderPathEqualizer.h"

TESTS(AbsoluteFilePathToRelativeFolderPathEqualizerTests)
AFACT(AssertEqual_ThrowsIfAnyFieldNotEqual)
EVIDENCE

TEST(AssertEqual_ThrowsIfAnyFieldNotEqual)
{
   SETUP_EQUALIZER_TEST(AbsoluteFilePathToRelativeFolderPath);
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(AbsoluteFilePathToRelativeFolderPath, absoluteSourceFilePath, ZenUnit::Random<fs::path>());
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(AbsoluteFilePathToRelativeFolderPath, relativeDestinationFolderPath, ZenUnit::Random<fs::path>());
}

RUN_TESTS(AbsoluteFilePathToRelativeFolderPathEqualizerTests)
