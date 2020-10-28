#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/CloudundancyIniEqualizer.h"

TESTS(CloudundancyIniEqualizerTests)
AFACT(Test)
EVIDENCE

TEST(Test)
{
   SETUP_EQUALIZER_TEST(CloudundancyIni);
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyIni, destinationFolderPaths, vector<fs::path> { fs::path() });
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyIni, absoluteFileOrFolderPathAndRelativeFolderPaths, vector<AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath> { ZenUnit::Random<AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath>() });
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyIni, fileSubpathsToNotCopy, vector<string> { ZenUnit::Random<string>() });
}

RUN_TESTS(CloudundancyIniEqualizerTests)
