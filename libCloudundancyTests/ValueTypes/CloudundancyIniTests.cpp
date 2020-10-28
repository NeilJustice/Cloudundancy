#include "pch.h"
#include "libCloudundancy/ValueTypes/CloudundancyIni.h"

TESTS(CloudundancyIniTests)
AFACT(DefaultConstructor_DefaultInitializesFields)
AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
EVIDENCE

TEST(DefaultConstructor_DefaultInitializesFields)
{
   CloudundancyIni cloudundancyIni;
   IS_EMPTY(cloudundancyIni.destinationFolderPaths);
   IS_EMPTY(cloudundancyIni.absoluteFileOrFolderPathAndRelativeFolderPaths);
   IS_EMPTY(cloudundancyIni.fileSubpathsToNotCopy);
}

TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
{
   SETUP_EQUALIZER_TEST(CloudundancyIni);
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyIni, destinationFolderPaths, ZenUnit::RandomNonEmptyVector<fs::path>());
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyIni, absoluteFileOrFolderPathAndRelativeFolderPaths, ZenUnit::RandomNonEmptyVector<AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath>());
   EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyIni, fileSubpathsToNotCopy, ZenUnit::RandomNonEmptyVector<string>());
}

RUN_TESTS(CloudundancyIniTests)
