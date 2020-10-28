#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/AbsoluteFileOrFolderPathToRelativeFolderPathEqualizer.h"

namespace ZenUnit
{
   void Equalizer<AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath>::AssertEqual(
      const AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath& expectedFileCopyInstruction, const AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath& actualFileCopyInstruction)
   {
      ARE_EQUAL(expectedFileCopyInstruction.absoluteSourceFileOrFolderPath, actualFileCopyInstruction.absoluteSourceFileOrFolderPath);
      ARE_EQUAL(expectedFileCopyInstruction.relativeDestinationFolderPath, actualFileCopyInstruction.relativeDestinationFolderPath);
   }
}
