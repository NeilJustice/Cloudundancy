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
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyArgs, programMode, ZenUnit::RandomNon0Enum<ProgramMode>(ProgramMode::MaxValue));
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyArgs, iniFilePath, ZenUnit::Random<fs::path>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyArgs, sevenZipIniFilePath, ZenUnit::Random<fs::path>());
   ZENUNIT_EQUALIZER_THROWS_WHEN_FIELD_NOT_EQUAL(CloudundancyArgs, backupStagingFolderPath, ZenUnit::Random<fs::path>());
}

TEST(TestableRandomCloudundancyArgs_ReturnsCloudundancyArgsWithAllRandomFields)
{
   ZenUnit::RandomGeneratorMock randomGeneratorMock;
   const ProgramMode programMode = static_cast<ProgramMode>(randomGeneratorMock.EnumMock.ReturnRandom());

   UtilsRandomGeneratorMock utilsRandomGeneratorMock;
   const fs::path iniFilePath = ZenUnit::Random<fs::path>();
   const fs::path sevenZipIniFilePath = ZenUnit::Random<fs::path>();
   utilsRandomGeneratorMock.RelativeFilePathMock.ReturnValues(iniFilePath, sevenZipIniFilePath);

   const fs::path backupStagingFolderPath = utilsRandomGeneratorMock.RelativeFolderPathMock.ReturnRandom();
   //
   const CloudundancyArgs cloundundancyArgs = TestableRandomCloudundancyArgs(&randomGeneratorMock, &utilsRandomGeneratorMock);
   //
   METALMOCK(randomGeneratorMock.EnumMock.CalledOnceWith(static_cast<int>(ProgramMode::MaxValue)));
   METALMOCK(utilsRandomGeneratorMock.RelativeFilePathMock.CalledNTimes(2));
   METALMOCK(utilsRandomGeneratorMock.RelativeFolderPathMock.CalledOnce());
   CloudundancyArgs expectedCloundundancyArgs;
   expectedCloundundancyArgs.programMode = programMode;
   expectedCloundundancyArgs.iniFilePath = iniFilePath;
   expectedCloundundancyArgs.sevenZipIniFilePath = sevenZipIniFilePath;
   expectedCloundundancyArgs.backupStagingFolderPath = backupStagingFolderPath;
   ARE_EQUAL(expectedCloundundancyArgs, cloundundancyArgs);
}

TEST(ZenUnitRandomCloudundancyArgs_DoesNotThrowException)
{
   ZenUnit::Random<CloudundancyArgs>();
}

RUN_TESTS(CloudundancyArgsEqualizerAndRandomTests)
