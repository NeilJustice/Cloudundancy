#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/CloudundancyArgsEqualizerAndRandom.h"

namespace ZenUnit
{
   void Equalizer<CloudundancyArgs>::AssertEqual(
      const CloudundancyArgs& expectedCloudundancyArgs, const CloudundancyArgs& actualCloudundancyArgs)
   {
      ARE_EQUAL(expectedCloudundancyArgs.programMode, actualCloudundancyArgs.programMode);
      ARE_EQUAL(expectedCloudundancyArgs.iniFilePath, actualCloudundancyArgs.iniFilePath);
      ARE_EQUAL(expectedCloudundancyArgs.sevenZipIniFilePath, actualCloudundancyArgs.sevenZipIniFilePath);
      ARE_EQUAL(expectedCloudundancyArgs.backupStagingFolderPath, actualCloudundancyArgs.backupStagingFolderPath);
      ARE_EQUAL(expectedCloudundancyArgs.deleteDestinationFoldersFirst, actualCloudundancyArgs.deleteDestinationFoldersFirst);
   }

   CloudundancyArgs TestableRandomCloudundancyArgs(
      const ZenUnit::RandomGenerator* randomGenerator, const UtilsRandomGenerator* utilsRandomGenerator)
   {
      CloudundancyArgs randomCloudundancyArgs;
      randomCloudundancyArgs.programMode = static_cast<ProgramMode>(randomGenerator->Enum(static_cast<int>(ProgramMode::MaxValue)));
      randomCloudundancyArgs.iniFilePath = utilsRandomGenerator->RelativeFilePath();
      randomCloudundancyArgs.sevenZipIniFilePath = utilsRandomGenerator->RelativeFilePath();
      randomCloudundancyArgs.backupStagingFolderPath = utilsRandomGenerator->RelativeFolderPath();
      randomCloudundancyArgs.deleteDestinationFoldersFirst = randomGenerator->Bool();
      return randomCloudundancyArgs;
   }

   template<>
   CloudundancyArgs Random()
   {
      const CloudundancyArgs randomCloudundancyArgs = TestableRandomCloudundancyArgs(
         ZenUnit::RandomGenerator::Instance(), UtilsRandomGenerator::Instance());
      return randomCloudundancyArgs;
   }
}
