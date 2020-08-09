#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/CloudundancyArgsEqualizer.h"

namespace ZenUnit
{
   void Equalizer<CloudundancyArgs>::AssertEqual(
      const CloudundancyArgs& expectedCloudundancyArgs, const CloudundancyArgs& actualCloudundancyArgs)
   {
      ARE_EQUAL(expectedCloudundancyArgs.programMode, actualCloudundancyArgs.programMode);
      ARE_EQUAL(expectedCloudundancyArgs.iniFilePath, actualCloudundancyArgs.iniFilePath);
      ARE_EQUAL(expectedCloudundancyArgs.sevenZipIniFilePath, actualCloudundancyArgs.sevenZipIniFilePath);
      ARE_EQUAL(expectedCloudundancyArgs.backupStagingFolderPath, actualCloudundancyArgs.backupStagingFolderPath);
   }
}
