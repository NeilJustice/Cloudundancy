#include "pch.h"
#include "libCloudundancy/ValueTypes/CloudundancyIni.h"
#include "libCloudundancy/ValueTypes/CloudundancyIniCopyInstruction.h"

TESTS(CloudundancyIniTests)
AFACT(DefaultConstructor_DefaultInitializesFields)
AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
EVIDENCE

TEST(DefaultConstructor_DefaultInitializesFields)
{
   CloudundancyIni defaultCloudundancyIni;
   CloudundancyIni expectedDefaultCloudundancyIni;
   expectedDefaultCloudundancyIni.iniFileLines = vector<string>();
   expectedDefaultCloudundancyIni.destinationFolderPaths = vector<fs::path>{};
   expectedDefaultCloudundancyIni.cloudundancyIniCopyInstructions = vector<CloudundancyIniCopyInstruction>{};
   expectedDefaultCloudundancyIni.fileSubpathsToIgnore = vector<string>{};
   ARE_EQUAL(expectedDefaultCloudundancyIni, defaultCloudundancyIni);
}

TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
{
   ZENUNIT_EQUALIZER_TEST_SETUP(CloudundancyIni);
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyIni, iniFileLines, ZenUnit::RandomNonEmptyVector<string>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyIni, destinationFolderPaths, ZenUnit::RandomNonEmptyVector<fs::path>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyIni, cloudundancyIniCopyInstructions, ZenUnit::RandomNonEmptyVector<CloudundancyIniCopyInstruction>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyIni, fileSubpathsToIgnore, ZenUnit::RandomNonEmptyVector<string>());
}

RUN_TESTS(CloudundancyIniTests)
