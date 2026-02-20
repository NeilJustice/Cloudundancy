#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/CloudundancyArgsEqualizerAndRandom.h"

namespace ZenUnit
{
   void Equalizer<CloudundancyArgs>::AssertEqual(
      const CloudundancyArgs& expectedCloudundancyArgs, const CloudundancyArgs& actualCloudundancyArgs)
   {
      ARE_EQUAL(expectedCloudundancyArgs.programMode, actualCloudundancyArgs.programMode);
      ARE_EQUAL(expectedCloudundancyArgs.iniInputFilePath, actualCloudundancyArgs.iniInputFilePath);
      ARE_EQUAL(expectedCloudundancyArgs.deleteDestinationFoldersFirst, actualCloudundancyArgs.deleteDestinationFoldersFirst);
      ARE_EQUAL(expectedCloudundancyArgs.sevenZipModeIniInputFilePath, actualCloudundancyArgs.sevenZipModeIniInputFilePath);
      ARE_EQUAL(expectedCloudundancyArgs.sevenZipStagingFolderPath, actualCloudundancyArgs.sevenZipStagingFolderPath);
      ARE_EQUAL(expectedCloudundancyArgs.sevenZipFileCopyingIniInputFilePath, actualCloudundancyArgs.sevenZipFileCopyingIniInputFilePath);
   }

   CloudundancyArgs TestableRandomCloudundancyArgs(const ZenUnit::RandomGenerator* randomGenerator)
   {
      CloudundancyArgs randomCloudundancyArgs;
      randomCloudundancyArgs.programMode = static_cast<ProgramMode>(randomGenerator->Enum(static_cast<int>(ProgramMode::MaxValue)));
      randomCloudundancyArgs.iniInputFilePath = randomGenerator->FilesystemPath();
      randomCloudundancyArgs.deleteDestinationFoldersFirst = randomGenerator->Bool();
      randomCloudundancyArgs.sevenZipModeIniInputFilePath = randomGenerator->FilesystemPath();
      randomCloudundancyArgs.sevenZipStagingFolderPath = randomGenerator->FilesystemPath();
      randomCloudundancyArgs.sevenZipFileCopyingIniInputFilePath = randomGenerator->FilesystemPath();
      return randomCloudundancyArgs;
   }

   template<>
   CloudundancyArgs Random()
   {
      CloudundancyArgs randomCloudundancyArgs = TestableRandomCloudundancyArgs(ZenUnit::RandomGenerator::Instance());
      return randomCloudundancyArgs;
   }
}
