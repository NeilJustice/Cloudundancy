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
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyIni, iniFileLines, ZenUnit::RandomNonEmptyVector<string>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyIni, destinationFolderPaths, ZenUnit::RandomNonEmptyVector<fs::path>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyIni, cloudundancyIniCopyInstructions, ZenUnit::RandomNonEmptyVector<CloudundancyIniCopyInstruction>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyIni, fileSubpathsToNotCopy, ZenUnit::RandomNonEmptyVector<string>());
}

TEST(TestableRandomCloudundancyIni_ReturnsCloudundancyIniWithAllRandomFields)
{
   ZenUnit::RandomGeneratorMock randomGeneratorMock;

   const vector<string> iniFileLines = ZenUnit::RandomNonEmptyVector<string>();
   const vector<string> fileSubpathsToNotCopy = ZenUnit::RandomNonEmptyVector<string>();
   randomGeneratorMock.StringVectorMock.ReturnValues(iniFileLines, fileSubpathsToNotCopy);

   const vector<fs::path> destinationFolderPaths = randomGeneratorMock.FilesystemPathVectorMock.ReturnRandom();
   const size_t cloudundancyIniCopyInstructionsVectorSize = ZenUnit::RandomBetween<size_t>(0, 2);
   randomGeneratorMock.SizeTBetweenMock.Return(cloudundancyIniCopyInstructionsVectorSize);
   //
   const CloudundancyIni randomCloudundancyIni = ZenUnit::TestableRandomCloudundancyIni(&randomGeneratorMock);
   //
   METALMOCK(randomGeneratorMock.FilesystemPathVectorMock.CalledOnce());
   METALMOCK(randomGeneratorMock.SizeTBetweenMock.CalledOnceWith(0, 2));
   METALMOCK(randomGeneratorMock.StringVectorMock.CalledNTimes(2));
   VECTORS_ARE_EQUAL(iniFileLines, randomCloudundancyIni.iniFileLines);
   VECTORS_ARE_EQUAL(destinationFolderPaths, randomCloudundancyIni.destinationFolderPaths);
   ARE_EQUAL(cloudundancyIniCopyInstructionsVectorSize, randomCloudundancyIni.cloudundancyIniCopyInstructions.size());
   VECTORS_ARE_EQUAL(fileSubpathsToNotCopy, randomCloudundancyIni.fileSubpathsToNotCopy);
}

TEST(ZenUnitRandomCloudundancyIni_DoesNotThrowException)
{
   ZenUnit::Random<CloudundancyIni>();
}

RUN_TESTS(CloudundancyIniEqualizerAndRandomTests)
