#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/AbsoluteFilePathToRelativeFolderPathEqualizer.h"

namespace ZenUnit
{
   void Equalizer<AbsoluteFilePathToRelativeFolderPath>::AssertEqual(
      const AbsoluteFilePathToRelativeFolderPath& expectedCloudundancyIniFileCopyInstruction, const AbsoluteFilePathToRelativeFolderPath& actualCloudundancyIniFileCopyInstruction)
   {
      ARE_EQUAL(expectedCloudundancyIniFileCopyInstruction.absoluteSourceFilePath, actualCloudundancyIniFileCopyInstruction.absoluteSourceFilePath);
      ARE_EQUAL(expectedCloudundancyIniFileCopyInstruction.relativeDestinationFolderPath, actualCloudundancyIniFileCopyInstruction.relativeDestinationFolderPath);
   }
}
