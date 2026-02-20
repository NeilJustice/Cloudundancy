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
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyArgs, iniInputFilePath, ZenUnit::Random<fs::path>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyArgs, deleteDestinationFoldersFirst, true);
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyArgs, sevenZipModeIniInputFilePath, ZenUnit::Random<fs::path>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyArgs, sevenZipStagingFolderPath, ZenUnit::Random<fs::path>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyArgs, sevenZipFileCopyingIniFilePath, ZenUnit::Random<fs::path>());
}

TEST(TestableRandomCloudundancyArgs_ReturnsCloudundancyArgsWithAllRandomFields)
{
   ZenUnit::RandomGeneratorMock randomGeneratorMock;
   const ProgramMode programMode = static_cast<ProgramMode>(randomGeneratorMock.EnumMock.ReturnRandom());

   const bool deleteDestinationFoldersFirst = randomGeneratorMock.BoolMock.ReturnRandom();

   const fs::path iniInputFilePath = ZenUnit::Random<fs::path>();
   const fs::path sevenZipModeIniInputFilePath = ZenUnit::Random<fs::path>();
   const fs::path sevenZipStagingFolderPath = ZenUnit::Random<fs::path>();
   const fs::path sevenZipFileCopyingIniFilePath = ZenUnit::Random<fs::path>();
   randomGeneratorMock.FilesystemPathMock.ReturnValues(
      iniInputFilePath, sevenZipModeIniInputFilePath, sevenZipStagingFolderPath, sevenZipFileCopyingIniFilePath);
   //
   const CloudundancyArgs cloundundancyArgs = TestableRandomCloudundancyArgs(&randomGeneratorMock);
   //
   METALMOCK(randomGeneratorMock.EnumMock.CalledOnceWith(static_cast<int>(ProgramMode::MaxValue)));
   METALMOCK(randomGeneratorMock.FilesystemPathMock.CalledNTimes(4));
   METALMOCK(randomGeneratorMock.BoolMock.CalledOnce());
   CloudundancyArgs expectedCloundundancyArgs;
   expectedCloundundancyArgs.programMode = programMode;
   expectedCloundundancyArgs.iniInputFilePath = iniInputFilePath;
   expectedCloundundancyArgs.deleteDestinationFoldersFirst = deleteDestinationFoldersFirst;
   expectedCloundundancyArgs.sevenZipModeIniInputFilePath = sevenZipModeIniInputFilePath;
   expectedCloundundancyArgs.sevenZipStagingFolderPath = sevenZipStagingFolderPath;
   expectedCloundundancyArgs.sevenZipFileCopyingIniFilePath = sevenZipFileCopyingIniFilePath;
   ARE_EQUAL(expectedCloundundancyArgs, cloundundancyArgs);
}

TEST(ZenUnitRandomCloudundancyArgs_DoesNotThrowException)
{
   ZenUnit::Random<CloudundancyArgs>();
}

RUN_TESTS(CloudundancyArgsEqualizerAndRandomTests)
