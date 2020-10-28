#include "pch.h"
#include "libCloudundancyTests/Components/FileSystem/ZenUnit/FilesystemPathRandom.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Random/RandomCloudundancyIni.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Random/RandomFileCopyInstruction.h"

namespace ZenUnit
{
   template<>
   CloudundancyIni Random()
   {
      CloudundancyIni randomCloudundancyIni;
      randomCloudundancyIni.destinationFolderPaths = RandomRelativeFolderPaths();
      randomCloudundancyIni.absoluteFileOrFolderPathAndRelativeFolderPaths = ZenUnit::RandomVector<AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath>();
      randomCloudundancyIni.fileSubpathsToNotCopy = ZenUnit::RandomVector<string>();
      return randomCloudundancyIni;
   }
}
