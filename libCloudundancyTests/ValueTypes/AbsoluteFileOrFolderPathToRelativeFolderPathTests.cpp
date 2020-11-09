#include "pch.h"
#include "libCloudundancy/ValueTypes/AbsoluteFileOrFolderPathToRelativeFolderPath.h"

TESTS(AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPathTests)
AFACT(DefaultConstructor_SetsFieldsToDefaultValues)
AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
EVIDENCE

TEST(DefaultConstructor_SetsFieldsToDefaultValues)
{
   AbsoluteFileOrFolderPathToRelativeFolderPath absoluteFileOrFolderPathToRelativeFolderPath;
   AbsoluteFileOrFolderPathToRelativeFolderPath expected;
   expected.absoluteSourceFileOrFolderPath = fs::path();
   expected.relativeDestinationFolderPath = fs::path();
   ARE_EQUAL(expected, absoluteFileOrFolderPathToRelativeFolderPath);
}

TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
{
   ZENUNIT_EQUALIZER_TEST_SETUP(AbsoluteFileOrFolderPathToRelativeFolderPath);
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(AbsoluteFileOrFolderPathToRelativeFolderPath,
      absoluteSourceFileOrFolderPath, ZenUnit::Random<fs::path>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(AbsoluteFileOrFolderPathToRelativeFolderPath,
      relativeDestinationFolderPath, ZenUnit::Random<fs::path>());
}

RUN_TESTS(AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPathTests)