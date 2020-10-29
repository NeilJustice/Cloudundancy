#include "pch.h"
#include "libCloudundancy/ValueTypes/AbsoluteSourceFilePath_RelativeDestinationFolderPath.h"

TESTS(AbsoluteSourceFilePath_RelativeDestinationFolderPathTests)
AFACT(DefaultConstructor_SetsFieldsToDefaults)
AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
EVIDENCE

TEST(DefaultConstructor_SetsFieldsToDefaults)
{
   AbsoluteSourceFilePath_RelativeDestinationFolderPath defaultAbsoluteSourceFilePath_RelativeDestinationFolderPath;
   AbsoluteSourceFilePath_RelativeDestinationFolderPath expectedDefaultAbsoluteSourceFilePath_RelativeDestinationFolderPath;
   expectedDefaultAbsoluteSourceFilePath_RelativeDestinationFolderPath.absoluteSourceFilePath = fs::path();
   expectedDefaultAbsoluteSourceFilePath_RelativeDestinationFolderPath.relativeDestinationFolderPath = fs::path();
   ARE_EQUAL(
      expectedDefaultAbsoluteSourceFilePath_RelativeDestinationFolderPath,
      defaultAbsoluteSourceFilePath_RelativeDestinationFolderPath);
}

TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
{
   SETUP_EQUALIZER_TEST(AbsoluteSourceFilePath_RelativeDestinationFolderPath);
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(
      AbsoluteSourceFilePath_RelativeDestinationFolderPath, absoluteSourceFilePath, ZenUnit::Random<fs::path>());
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(
      AbsoluteSourceFilePath_RelativeDestinationFolderPath, relativeDestinationFolderPath, ZenUnit::Random<fs::path>());
}

RUN_TESTS(AbsoluteSourceFilePath_RelativeDestinationFolderPathTests)
