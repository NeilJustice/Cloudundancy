#include "pch.h"

TESTS(CloudundancyIniCopyInstructionEqualizerAndRandomTests)
AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
AFACT(TestableRandomCloudundancyIniCopyInstruction_ReturnsCloudundancyIniCopyInstructionWithAllRandomFields)
AFACT(ZenUnitRandomCloudundancyIniCopyInstruction_ReturnsResultOfCallingTestableRandomCloudundancyIniCopyInstruction)
EVIDENCE

TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
{
   ZENUNIT_EQUALIZER_TEST_SETUP(CloudundancyIniCopyInstruction);
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyIniCopyInstruction, absoluteSourceFileOrFolderPath, ZenUnit::Random<fs::path>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyIniCopyInstruction, relativeDestinationFolderPath, ZenUnit::Random<fs::path>());
}

TEST(TestableRandomCloudundancyIniCopyInstruction_ReturnsCloudundancyIniCopyInstructionWithAllRandomFields)
{
   Utils::UtilsRandomGeneratorMock utilsRandomGeneratorMock;
   const fs::path absoluteSourceFileOrFolderPath = utilsRandomGeneratorMock.RelativeFilePathMock.ReturnRandom();
   const fs::path relativeDestinationFolderPath = utilsRandomGeneratorMock.RelativeFolderPathMock.ReturnRandom();
   //
   const CloudundancyIniCopyInstruction randomCloudundancyIniCopyInstruction =
      ZenUnit::TestableRandomCloudundancyIniCopyInstruction(&utilsRandomGeneratorMock);
   //
   METALMOCK(utilsRandomGeneratorMock.RelativeFilePathMock.CalledOnce());
   METALMOCK(utilsRandomGeneratorMock.RelativeFolderPathMock.CalledOnce());
   CloudundancyIniCopyInstruction expectedRandomCloudundancyIniCopyInstruction;
   expectedRandomCloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath = absoluteSourceFileOrFolderPath;
   expectedRandomCloudundancyIniCopyInstruction.relativeDestinationFolderPath = relativeDestinationFolderPath;
   ARE_EQUAL(expectedRandomCloudundancyIniCopyInstruction, randomCloudundancyIniCopyInstruction);
}

TEST(ZenUnitRandomCloudundancyIniCopyInstruction_ReturnsResultOfCallingTestableRandomCloudundancyIniCopyInstruction)
{
   ZenUnit::Random<CloudundancyIniCopyInstruction>();
}

RUN_TESTS(CloudundancyIniCopyInstructionEqualizerAndRandomTests)
