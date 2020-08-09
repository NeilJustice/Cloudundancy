#include "pch.h"
#include "libCloudundancy/Enums/ProgramMode.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Random/RandomCloudundancyArgs.h"
#include "libCloudundancyTests/Components/Random/ZenMock/UtilsRandomGeneratorMock.h"

TESTS(RandomCloudundancyArgsTests)
AFACT(RandomCloudundancyArgs_ReturnsCloudundancyArgsWithAllNonDefaultFields)
EVIDENCE

TEST(RandomCloudundancyArgs_ReturnsCloudundancyArgsWithAllNonDefaultFields)
{
   ZenMock::RandomGeneratorMock randomGeneratorMock;
   const ProgramMode programMode = static_cast<ProgramMode>(randomGeneratorMock.EnumMock.ReturnRandom());

   UtilsRandomGeneratorMock utilsRandomGeneratorMock;
   const fs::path iniFilePath = ZenUnit::Random<fs::path>();
   const fs::path sevenZipIniFilePath = ZenUnit::Random<fs::path>();
   utilsRandomGeneratorMock.RelativeFilePathMock.ReturnValues(iniFilePath, sevenZipIniFilePath);
   const fs::path backupStagingFolderPath = utilsRandomGeneratorMock.RelativeFolderPathMock.ReturnRandom();
   //
   const CloudundancyArgs cloundundancyArgs = RandomCloudundancyArgs(&randomGeneratorMock, &utilsRandomGeneratorMock);
   //
   ZENMOCK(randomGeneratorMock.EnumMock.CalledOnceWith(static_cast<int>(ProgramMode::MaxValue)));
   ZENMOCK(utilsRandomGeneratorMock.RelativeFilePathMock.CalledNTimes(2));
   ZENMOCK(utilsRandomGeneratorMock.RelativeFolderPathMock.CalledOnce());

   CloudundancyArgs expectedCloundundancyArgs;
   expectedCloundundancyArgs.programMode = programMode;
   expectedCloundundancyArgs.iniFilePath = iniFilePath;
   expectedCloundundancyArgs.sevenZipIniFilePath = sevenZipIniFilePath;
   expectedCloundundancyArgs.backupStagingFolderPath = backupStagingFolderPath;
   ARE_EQUAL(expectedCloundundancyArgs, cloundundancyArgs);
}

RUN_TESTS(RandomCloudundancyArgsTests)
