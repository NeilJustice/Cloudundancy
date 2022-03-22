#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/CloudundancyArgsEqualizerAndRandom.h"

TESTS(CloudundancyArgsEqualizerAndRandomTests)
AFACT(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
AFACT(TestableRandomCloudundancyArgs_ReturnsCloudundancyArgsWithAllRandomFields)
AFACT(ZenUnitRandomCloudundancyArgs_DoesNotThrowException)
EVIDENCE

TEST(ZenUnitEqualizer_ThrowsIfAnyFieldNotEqual)
{
   ZENUNIT_EQUALIZER_TEST_SETUP(CloudundancyArgs);
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyArgs, programMode, ZenUnit::RandomNon0Enum<ProgramMode>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyArgs, iniFilePath, ZenUnit::Random<fs::path>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyArgs, deleteDestinationFoldersFirst, true);
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyArgs, sevenZipModeIniFilePath, ZenUnit::Random<fs::path>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyArgs, sevenZipStagingFolderPath, ZenUnit::Random<fs::path>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyArgs, sevenZipFileCopyingIniFilePath, ZenUnit::Random<fs::path>());
}

TEST(TestableRandomCloudundancyArgs_ReturnsCloudundancyArgsWithAllRandomFields)
{
   ZenUnit::RandomGeneratorMock randomGeneratorMock;
   const ProgramMode programMode = static_cast<ProgramMode>(randomGeneratorMock.EnumMock.ReturnRandom());

   const bool deleteDestinationFoldersFirst = randomGeneratorMock.BoolMock.ReturnRandom();

   const fs::path iniFilePath = ZenUnit::Random<fs::path>();
   const fs::path sevenZipModeIniFilePath = ZenUnit::Random<fs::path>();
   const fs::path sevenZipStagingFolderPath = ZenUnit::Random<fs::path>();
   const fs::path sevenZipFileCopyingIniFilePath = ZenUnit::Random<fs::path>();
   randomGeneratorMock.FilesystemPathMock.ReturnValues(
      iniFilePath, sevenZipModeIniFilePath, sevenZipStagingFolderPath, sevenZipFileCopyingIniFilePath);
   //
   const CloudundancyArgs cloundundancyArgs = TestableRandomCloudundancyArgs(&randomGeneratorMock);
   //
   METALMOCK(randomGeneratorMock.EnumMock.CalledOnceWith(static_cast<int>(ProgramMode::MaxValue)));
   METALMOCK(randomGeneratorMock.FilesystemPathMock.CalledNTimes(4));
   METALMOCK(randomGeneratorMock.BoolMock.CalledOnce());
   CloudundancyArgs expectedCloundundancyArgs;
   expectedCloundundancyArgs.programMode = programMode;
   expectedCloundundancyArgs.iniFilePath = iniFilePath;
   expectedCloundundancyArgs.deleteDestinationFoldersFirst = deleteDestinationFoldersFirst;
   expectedCloundundancyArgs.sevenZipModeIniFilePath = sevenZipModeIniFilePath;
   expectedCloundundancyArgs.sevenZipStagingFolderPath = sevenZipStagingFolderPath;
   expectedCloundundancyArgs.sevenZipFileCopyingIniFilePath = sevenZipFileCopyingIniFilePath;
   ARE_EQUAL(expectedCloundundancyArgs, cloundundancyArgs);
}

TEST(ZenUnitRandomCloudundancyArgs_DoesNotThrowException)
{
   ZenUnit::Random<CloudundancyArgs>();
}

RUN_TESTS(CloudundancyArgsEqualizerAndRandomTests)
