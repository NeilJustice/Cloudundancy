#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/CloudundancyArgsEqualizerAndRandom.h"

namespace ZenUnit
{
   void Equalizer<CloudundancyArgs>::AssertEqual(
      const CloudundancyArgs& expectedCloudundancyArgs, const CloudundancyArgs& actualCloudundancyArgs)
   {
      ARE_EQUAL(expectedCloudundancyArgs.programMode, actualCloudundancyArgs.programMode);
      ARE_EQUAL(expectedCloudundancyArgs.iniFilePath, actualCloudundancyArgs.iniFilePath);
      ARE_EQUAL(expectedCloudundancyArgs.deleteDestinationFoldersFirst, actualCloudundancyArgs.deleteDestinationFoldersFirst);
      ARE_EQUAL(expectedCloudundancyArgs.sevenZipModeIniFilePath, actualCloudundancyArgs.sevenZipModeIniFilePath);
      ARE_EQUAL(expectedCloudundancyArgs.sevenZipStagingFolderPath, actualCloudundancyArgs.sevenZipStagingFolderPath);
      ARE_EQUAL(expectedCloudundancyArgs.sevenZipFileCopyingIniFilePath, actualCloudundancyArgs.sevenZipFileCopyingIniFilePath);
   }

   CloudundancyArgs TestableRandomCloudundancyArgs(const ZenUnit::RandomGenerator* randomGenerator)
   {
      CloudundancyArgs randomCloudundancyArgs;
      randomCloudundancyArgs.programMode = static_cast<ProgramMode>(randomGenerator->Enum(static_cast<int>(ProgramMode::MaxValue)));
      randomCloudundancyArgs.iniFilePath = randomGenerator->FilesystemPath();
      randomCloudundancyArgs.deleteDestinationFoldersFirst = randomGenerator->Bool();
      randomCloudundancyArgs.sevenZipModeIniFilePath = randomGenerator->FilesystemPath();
      randomCloudundancyArgs.sevenZipStagingFolderPath = randomGenerator->FilesystemPath();
      randomCloudundancyArgs.sevenZipFileCopyingIniFilePath = randomGenerator->FilesystemPath();
      return randomCloudundancyArgs;
   }

   template<>
   CloudundancyArgs Random()
   {
      const CloudundancyArgs randomCloudundancyArgs = TestableRandomCloudundancyArgs(ZenUnit::RandomGenerator::Instance());
      return randomCloudundancyArgs;
   }
}
