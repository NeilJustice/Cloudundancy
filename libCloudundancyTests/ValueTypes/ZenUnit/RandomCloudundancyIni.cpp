#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/RandomCloudundancyIni.h"

namespace ZenUnit
{
   template<>
   CloudundancyIni Random()
   {
      CloudundancyIni randomCloudundancyIni;
      randomCloudundancyIni.destinationFolderPaths = RandomRelativeFolderPaths();
      randomCloudundancyIni.absoluteFileOrFolderPathAndRelativeFolderPaths =
         ZenUnit::RandomNonEmptyVector<AbsoluteFileOrFolderPathToRelativeFolderPath>();
      randomCloudundancyIni.fileSubpathsToNotCopy = ZenUnit::RandomNonEmptyVector<string>();
      return randomCloudundancyIni;
   }
}
