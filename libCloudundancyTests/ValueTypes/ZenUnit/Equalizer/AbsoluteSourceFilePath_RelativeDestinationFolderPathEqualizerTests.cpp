#include "pch.h"
#include "libCloudundancy/ValueTypes/AbsoluteSourceFilePath_RelativeDestinationFolderPath.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/AbsoluteSourceFilePath_RelativeDestinationFolderPathEqualizer.h"

TESTS(AbsoluteSourceFilePath_RelativeDestinationFolderPathEqualizerTests)
AFACT(AssertEqual_ThrowsIfAnyFieldNotEqual)
EVIDENCE

TEST(AssertEqual_ThrowsIfAnyFieldNotEqual)
{
   SETUP_EQUALIZER_TEST(AbsoluteSourceFilePath_RelativeDestinationFolderPath);
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(
      AbsoluteSourceFilePath_RelativeDestinationFolderPath, absoluteSourceFilePath, ZenUnit::Random<fs::path>());
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(
      AbsoluteSourceFilePath_RelativeDestinationFolderPath, relativeDestinationFolderPath, ZenUnit::Random<fs::path>());
}

RUN_TESTS(AbsoluteSourceFilePath_RelativeDestinationFolderPathEqualizerTests)
