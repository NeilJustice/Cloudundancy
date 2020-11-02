#include "pch.h"
#include "libCloudundancy/ValueTypes/AbsoluteFilePathToRelativeDestinationFolderPath.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/AbsoluteSourceFilePath_RelativeDestinationFolderPathEqualizer.h"

TESTS(AbsoluteSourceFilePath_RelativeDestinationFolderPathEqualizerTests)
AFACT(AssertEqual_ThrowsIfAnyFieldNotEqual)
EVIDENCE

TEST(AssertEqual_ThrowsIfAnyFieldNotEqual)
{
   ZENUNIT_EQUALIZER_TEST_SETUP(AbsoluteFilePathToRelativeDestinationFolderPath);
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(
      AbsoluteFilePathToRelativeDestinationFolderPath, absoluteSourceFilePath, ZenUnit::Random<fs::path>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(
      AbsoluteFilePathToRelativeDestinationFolderPath, relativeDestinationFolderPath, ZenUnit::Random<fs::path>());
}

RUN_TESTS(AbsoluteSourceFilePath_RelativeDestinationFolderPathEqualizerTests)
