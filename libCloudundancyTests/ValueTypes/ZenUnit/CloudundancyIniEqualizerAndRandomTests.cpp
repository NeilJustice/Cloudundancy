#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/CloudundancyIniEqualizerAndRandom.h"

TESTS(CloudundancyIniEqualizerAndRandomTests)
AFACT(ZenUnitEqualizer_ThrowsZenUnitAnomalyIfAnyFieldNotEqual)
AFACT(TestableRandomCloudundancyIni_ReturnsCloudundancyIniWithAllRandomFields)
AFACT(ZenUnitRandomCloudundancyIni_DoesNotThrowException)
EVIDENCE

TEST(ZenUnitEqualizer_ThrowsZenUnitAnomalyIfAnyFieldNotEqual)
{
   ZENUNIT_EQUALIZER_TEST_SETUP(CloudundancyIni);
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyIni, destinationFolderPaths,
      ZenUnit::RandomNonEmptyVector<fs::path>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyIni, cloudundancyIniCopyInstructions,
      ZenUnit::RandomNonEmptyVector<CloudundancyIniCopyInstruction>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyIni, fileSubpathsToNotCopy,
      ZenUnit::RandomNonEmptyVector<string>());
}

TEST(TestableRandomCloudundancyIni_ReturnsCloudundancyIniWithAllRandomFields)
{
   //ZenUnit::RandomGeneratorMock randomGeneratorMock;
   //const int field1 = randomGeneratorMock.IntMock.ReturnRandom();
   //
   //const T randomT = ZenUnit::TestableRandomCloudundancyIni(&randomGeneratorMock);
   //
   //METALMOCK(randomGeneratorMock.IntMock.CalledOnce());
   //T expectedRandomT;
   //ARE_EQUAL(expectedRandomT, randomT);
}

TEST(ZenUnitRandomCloudundancyIni_DoesNotThrowException)
{
   ZenUnit::Random<CloudundancyIni>();
}

RUN_TESTS(CloudundancyIniEqualizerAndRandomTests)
