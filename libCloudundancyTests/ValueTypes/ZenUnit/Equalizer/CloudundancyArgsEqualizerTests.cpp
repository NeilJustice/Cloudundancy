#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/CloudundancyArgsEqualizer.h"

TESTS(CloudundancyArgsEqualizerTests)
AFACT(AssertEqual_ThrowsIfAnyFieldNotEqual)
EVIDENCE

TEST(AssertEqual_ThrowsIfAnyFieldNotEqual)
{
   ZENUNIT_EQUALIZER_TEST_SETUP(CloudundancyArgs);
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyArgs, programMode, ZenUnit::RandomNon0Enum<ProgramMode>(ProgramMode::MaxValue));
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyArgs, iniFilePath, ZenUnit::Random<fs::path>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyArgs, sevenZipIniFilePath, ZenUnit::Random<fs::path>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyArgs, backupStagingFolderPath, ZenUnit::Random<fs::path>());
}

RUN_TESTS(CloudundancyArgsEqualizerTests)
