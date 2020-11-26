#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/RandomCloudundancyArgs.h"

CloudundancyArgs RandomCloudundancyArgs(
   const ZenUnit::RandomGenerator* randomGenerator, const UtilsRandomGenerator* utilsRandomGenerator)
{
   CloudundancyArgs randomCloudundancyArgs;
   randomCloudundancyArgs.programMode = static_cast<ProgramMode>(randomGenerator->Enum(static_cast<int>(ProgramMode::MaxValue)));
   randomCloudundancyArgs.iniFilePath = utilsRandomGenerator->RelativeFilePath();
   randomCloudundancyArgs.sevenZipIniFilePath = utilsRandomGenerator->RelativeFilePath();
   randomCloudundancyArgs.backupStagingFolderPath = utilsRandomGenerator->RelativeFolderPath();
   return randomCloudundancyArgs;
}

namespace ZenUnit
{
   template<>
   CloudundancyArgs Random()
   {
      const ZenUnit::RandomGenerator randomGenerator;
      const UtilsRandomGenerator utilsRandomGenerator;
      const CloudundancyArgs randomCloudundancyArgs = RandomCloudundancyArgs(&randomGenerator, &utilsRandomGenerator);
      return randomCloudundancyArgs;
   }
}
