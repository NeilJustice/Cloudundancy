#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/CloudundancyIniEqualizer.h"

namespace ZenUnit
{
   void Equalizer<CloudundancyIni>::AssertEqual(
      const CloudundancyIni& expectedCloudundancyIni, const CloudundancyIni& actualCloudundancyIni)
   {
      VECTORS_ARE_EQUAL(expectedCloudundancyIni.destinationFolderPaths, actualCloudundancyIni.destinationFolderPaths);
      VECTORS_ARE_EQUAL(expectedCloudundancyIni.absoluteFileOrFolderPathAndRelativeFolderPaths, actualCloudundancyIni.absoluteFileOrFolderPathAndRelativeFolderPaths);
      VECTORS_ARE_EQUAL(expectedCloudundancyIni.fileSubpathsToNotCopy, actualCloudundancyIni.fileSubpathsToNotCopy);
   }
}
