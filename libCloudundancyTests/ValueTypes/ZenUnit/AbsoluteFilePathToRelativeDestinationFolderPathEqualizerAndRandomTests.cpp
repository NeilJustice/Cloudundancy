#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/AbsoluteFilePathToRelativeDestinationFolderPathEqualizerAndRandom.h"

TESTS(AbsoluteFilePathToRelativeDestinationFolderPathEqualizerAndRandomTests)
AFACT(AssertEqual_ThrowsIfAnyFieldNotEqual)
EVIDENCE

TEST(AssertEqual_ThrowsIfAnyFieldNotEqual)
{
   ZENUNIT_EQUALIZER_TEST_SETUP(AbsoluteFilePathToRelativeDestinationFolderPath);
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(AbsoluteFilePathToRelativeDestinationFolderPath, absoluteSourceFilePath, ZenUnit::Random<fs::path>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(AbsoluteFilePathToRelativeDestinationFolderPath, relativeDestinationFolderPath, ZenUnit::Random<fs::path>());
}

RUN_TESTS(AbsoluteFilePathToRelativeDestinationFolderPathEqualizerAndRandomTests)
