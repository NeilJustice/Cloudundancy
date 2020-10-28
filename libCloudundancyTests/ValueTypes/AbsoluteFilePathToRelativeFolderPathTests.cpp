#include "pch.h"
#include "libCloudundancy/ValueTypes/AbsoluteFilePathToRelativeFolderPath.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/AbsoluteFilePathToRelativeFolderPathEqualizer.h"

TESTS(AbsoluteFilePathToRelativeFolderPathTests)
AFACT(DefaultConstructor_SetsFieldsToDefaults)
AFACT(FromCloudundancyIniCopyInstruction_ReturnsNewDefaultAbsoluteFilePathToRelativeFolderPath)
AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
EVIDENCE

TEST(DefaultConstructor_SetsFieldsToDefaults)
{
   AbsoluteFilePathToRelativeFolderPath absoluteFilePathAndRelativeFolderPath;
   ARE_EQUAL(fs::path(), absoluteFilePathAndRelativeFolderPath.absoluteSourceFilePath);
   ARE_EQUAL(fs::path(), absoluteFilePathAndRelativeFolderPath.relativeDestinationFolderPath);
}

TEST(FromCloudundancyIniCopyInstruction_ReturnsNewDefaultAbsoluteFilePathToRelativeFolderPath)
{
   const size_t elementIndex = ZenUnit::Random<size_t>();
   const AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath absoluteFileOrFolderPathToRelativeFolderPath;
   const vector<string> fileSubpathsToNotCopy;
   //
   const AbsoluteFilePathToRelativeFolderPath returnedAbsoluteFilePathToRelativeFolderPath =
      AbsoluteFilePathToRelativeFolderPath::FromCloudundancyIniCopyInstruction(
         elementIndex, absoluteFileOrFolderPathToRelativeFolderPath, fileSubpathsToNotCopy);
   //
   const AbsoluteFilePathToRelativeFolderPath expectedReturnValue;
   ARE_EQUAL(expectedReturnValue, returnedAbsoluteFilePathToRelativeFolderPath);
}

TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
{
   SETUP_EQUALIZER_TEST(AbsoluteFilePathToRelativeFolderPath);
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(AbsoluteFilePathToRelativeFolderPath, absoluteSourceFilePath, ZenUnit::Random<fs::path>());
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(AbsoluteFilePathToRelativeFolderPath, relativeDestinationFolderPath, ZenUnit::Random<fs::path>());
}

RUN_TESTS(AbsoluteFilePathToRelativeFolderPathTests)
