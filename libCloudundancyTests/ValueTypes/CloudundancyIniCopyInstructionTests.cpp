#include "pch.h"
#include "libCloudundancy/ValueTypes/CloudundancyIniCopyInstruction.h"

TESTS(AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPathTests)
AFACT(DefaultConstructor_SetsFieldsToDefaultValues)
AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
EVIDENCE

TEST(DefaultConstructor_SetsFieldsToDefaultValues)
{
   CloudundancyIniCopyInstruction absoluteFileOrFolderPathToRelativeFolderPath;
   CloudundancyIniCopyInstruction expected;
   expected.absoluteSourceFileOrFolderPath = fs::path();
   expected.relativeDestinationFolderPath = fs::path();
   ARE_EQUAL(expected, absoluteFileOrFolderPathToRelativeFolderPath);
}

TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
{
   ZENUNIT_EQUALIZER_TEST_SETUP(CloudundancyIniCopyInstruction);
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyIniCopyInstruction,
      absoluteSourceFileOrFolderPath, ZenUnit::Random<fs::path>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyIniCopyInstruction,
      relativeDestinationFolderPath, ZenUnit::Random<fs::path>());
}

RUN_TESTS(AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPathTests)
