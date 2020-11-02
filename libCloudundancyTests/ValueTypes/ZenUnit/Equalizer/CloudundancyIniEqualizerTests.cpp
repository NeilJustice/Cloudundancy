#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/CloudundancyIniEqualizer.h"

TESTS(CloudundancyIniEqualizerTests)
AFACT(Test)
EVIDENCE

TEST(Test)
{
   ZENUNIT_EQUALIZER_TEST_SETUP(CloudundancyIni);
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(
      CloudundancyIni, destinationFolderPaths, vector<fs::path> { fs::path() });
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(
      CloudundancyIni, absoluteFileOrFolderPathAndRelativeFolderPaths, vector<AbsoluteFileOrFolderPathToRelativeFolderPath> { ZenUnit::Random<AbsoluteFileOrFolderPathToRelativeFolderPath>() });
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(
      CloudundancyIni, fileSubpathsToNotCopy, vector<string> { ZenUnit::Random<string>() });
}

RUN_TESTS(CloudundancyIniEqualizerTests)
