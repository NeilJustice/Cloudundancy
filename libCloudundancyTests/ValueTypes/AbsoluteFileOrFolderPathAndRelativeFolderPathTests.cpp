#include "pch.h"
#include "libCloudundancy/ValueTypes/AbsoluteFileOrFolderPathToRelativeFolderPath.h"

TESTS(AbsoluteFileOrFolderPathToRelativeFolderPathTests)
AFACT(DefaultConstructor_SetsFieldsToDefaultValues)
AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
EVIDENCE

TEST(DefaultConstructor_SetsFieldsToDefaultValues)
{
   AbsoluteFileOrFolderPathToRelativeFolderPath cloudundancyIniCopyInstruction;
   ARE_EQUAL(fs::path(), cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath);
   ARE_EQUAL(fs::path(), cloudundancyIniCopyInstruction.relativeDestinationFolderPath);
}

TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
{
   SETUP_EQUALIZER_TEST(AbsoluteFileOrFolderPathToRelativeFolderPath);
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(AbsoluteFileOrFolderPathToRelativeFolderPath, absoluteSourceFileOrFolderPath, ZenUnit::Random<fs::path>());
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(AbsoluteFileOrFolderPathToRelativeFolderPath, relativeDestinationFolderPath, ZenUnit::Random<fs::path>());
}

RUN_TESTS(AbsoluteFileOrFolderPathToRelativeFolderPathTests)
