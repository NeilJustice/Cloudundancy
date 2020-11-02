#include "pch.h"
#include "libCloudundancy/ValueTypes/AbsoluteFilePathToRelativeDestinationFolderPath.h"

TESTS(AbsoluteFilePathToRelativeDestinationFolderPathTests)
AFACT(DefaultConstructor_SetsFieldsToDefaults)
AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
EVIDENCE

TEST(DefaultConstructor_SetsFieldsToDefaults)
{
   AbsoluteFilePathToRelativeDestinationFolderPath defaultAbsoluteSourceFilePath_RelativeDestinationFolderPath;
   AbsoluteFilePathToRelativeDestinationFolderPath expectedDefaultAbsoluteSourceFilePath_RelativeDestinationFolderPath;
   expectedDefaultAbsoluteSourceFilePath_RelativeDestinationFolderPath.absoluteSourceFilePath = fs::path();
   expectedDefaultAbsoluteSourceFilePath_RelativeDestinationFolderPath.relativeDestinationFolderPath = fs::path();
   ARE_EQUAL(
      expectedDefaultAbsoluteSourceFilePath_RelativeDestinationFolderPath,
      defaultAbsoluteSourceFilePath_RelativeDestinationFolderPath);
}

TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
{
   ZENUNIT_EQUALIZER_TEST_SETUP(AbsoluteFilePathToRelativeDestinationFolderPath);
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(
      AbsoluteFilePathToRelativeDestinationFolderPath, absoluteSourceFilePath, ZenUnit::Random<fs::path>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(
      AbsoluteFilePathToRelativeDestinationFolderPath, relativeDestinationFolderPath, ZenUnit::Random<fs::path>());
}

RUN_TESTS(AbsoluteFilePathToRelativeDestinationFolderPathTests)
