#include "pch.h"
#include "libCloudundancy/ValueTypes/AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath.h"

TESTS(AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPathTests)
AFACT(DefaultConstructor_SetsFieldsToDefaultValues)
AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
EVIDENCE

TEST(DefaultConstructor_SetsFieldsToDefaultValues)
{
   AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath absoluteSourceFileOrFolderPath_RelativeDestinationFolderPath;
   AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath expectedAbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath;
   expectedAbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath.absoluteSourceFileOrFolderPath = fs::path();
   expectedAbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath.relativeDestinationFolderPath = fs::path();
   ARE_EQUAL(
      expectedAbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath,
      absoluteSourceFileOrFolderPath_RelativeDestinationFolderPath);
}

TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
{
   SETUP_EQUALIZER_TEST(AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath);
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(
      AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath, absoluteSourceFileOrFolderPath, ZenUnit::Random<fs::path>());
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(
      AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath, relativeDestinationFolderPath, ZenUnit::Random<fs::path>());
}

RUN_TESTS(AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPathTests)
