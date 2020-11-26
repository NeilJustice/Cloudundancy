#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/RandomCloudundancyArgs.h"
#include "libCloudundancyTests/Components/Random/MetalMock/UtilsRandomGeneratorMock.h"

TESTS(RandomCloudundancyArgsTests)
AFACT(RandomCloudundancyArgs_ReturnsCloudundancyArgsWithAllNonDefaultFields)
EVIDENCE

TEST(RandomCloudundancyArgs_ReturnsCloudundancyArgsWithAllNonDefaultFields)
{
   ZenUnit::RandomGeneratorMock randomGeneratorMock;
   const ProgramMode programMode = static_cast<ProgramMode>(randomGeneratorMock.EnumMock.ReturnRandom());

   UtilsRandomGeneratorMock utilsRandomGeneratorMock;
   const fs::path iniFilePath = ZenUnit::Random<fs::path>();
   const fs::path sevenZipIniFilePath = ZenUnit::Random<fs::path>();
   utilsRandomGeneratorMock.RelativeFilePathMock.ReturnValues(iniFilePath, sevenZipIniFilePath);
   const fs::path backupStagingFolderPath = utilsRandomGeneratorMock.RelativeFolderPathMock.ReturnRandom();
   //
   const CloudundancyArgs cloundundancyArgs = RandomCloudundancyArgs(&randomGeneratorMock, &utilsRandomGeneratorMock);
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

RUN_TESTS(RandomCloudundancyArgsTests)
