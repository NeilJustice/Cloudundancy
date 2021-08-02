#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/AbsoluteFilePathToRelativeDestinationFolderPathEqualizerAndRandom.h"

TESTS(AbsoluteFilePathToRelativeDestinationFolderPathEqualizerAndRandomTests)
AFACT(ZenUnitEqualizer_ThrowsZenUnitAnomalyIfAnyFieldNotEqual)
AFACT(TestableRandomAbsoluteFilePathToRelativeDestinationFolderPath_ReturnsAbsoluteFilePathToRelativeDestinationFolderPathWithAllRandomFields)
AFACT(ZenUnitRandomAbsoluteFilePathToRelativeDestinationFolderPath_ReturnsResultOfCallingTestableRandomAbsoluteFilePathToRelativeDestinationFolderPath)
EVIDENCE

TEST(ZenUnitEqualizer_ThrowsZenUnitAnomalyIfAnyFieldNotEqual)
{
   ZENUNIT_EQUALIZER_TEST_SETUP(AbsoluteFilePathToRelativeDestinationFolderPath);
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(AbsoluteFilePathToRelativeDestinationFolderPath, absoluteSourceFilePath, ZenUnit::Random<fs::path>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(AbsoluteFilePathToRelativeDestinationFolderPath, relativeDestinationFolderPath, ZenUnit::Random<fs::path>());
}

TEST(TestableRandomAbsoluteFilePathToRelativeDestinationFolderPath_ReturnsAbsoluteFilePathToRelativeDestinationFolderPathWithAllRandomFields)
{
   ZenUnit::RandomGeneratorMock randomGeneratorMock;
   fs::path absoluteSourceFilePath = randomGeneratorMock.FilesystemPathMock.ReturnRandom();

   Utils::UtilsRandomGeneratorMock utilsRandomGeneratorMock;
   fs::path relativeDestinationFolderPath = utilsRandomGeneratorMock.RelativeFolderPathMock.ReturnRandom();
   //
   const AbsoluteFilePathToRelativeDestinationFolderPath randomAbsoluteFilePathToRelativeDestinationFolderPath =
      ZenUnit::TestableRandomAbsoluteFilePathToRelativeDestinationFolderPath(&randomGeneratorMock, &utilsRandomGeneratorMock);
   //
   METALMOCK(randomGeneratorMock.FilesystemPathMock.CalledOnce());
   METALMOCK(utilsRandomGeneratorMock.RelativeFolderPathMock.CalledOnce());
   AbsoluteFilePathToRelativeDestinationFolderPath expected;
   expected.absoluteSourceFilePath = absoluteSourceFilePath;
   expected.relativeDestinationFolderPath = relativeDestinationFolderPath;
   ARE_EQUAL(expected, randomAbsoluteFilePathToRelativeDestinationFolderPath);
}

TEST(ZenUnitRandomAbsoluteFilePathToRelativeDestinationFolderPath_ReturnsResultOfCallingTestableRandomAbsoluteFilePathToRelativeDestinationFolderPath)
{
   ZenUnit::Random<AbsoluteFilePathToRelativeDestinationFolderPath>();
}

RUN_TESTS(AbsoluteFilePathToRelativeDestinationFolderPathEqualizerAndRandomTests)
