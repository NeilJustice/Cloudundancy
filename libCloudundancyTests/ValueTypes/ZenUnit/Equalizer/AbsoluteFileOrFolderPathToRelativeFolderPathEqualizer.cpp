#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/AbsoluteFileOrFolderPathToRelativeFolderPathEqualizer.h"

namespace ZenUnit
{
   void Equalizer<AbsoluteFileOrFolderPathToRelativeFolderPath>::AssertEqual(
      const AbsoluteFileOrFolderPathToRelativeFolderPath& expectedFileCopyInstruction, const AbsoluteFileOrFolderPathToRelativeFolderPath& actualFileCopyInstruction)
   {
      ARE_EQUAL(expectedFileCopyInstruction.absoluteSourceFileOrFolderPath, actualFileCopyInstruction.absoluteSourceFileOrFolderPath);
      ARE_EQUAL(expectedFileCopyInstruction.relativeDestinationFolderPath, actualFileCopyInstruction.relativeDestinationFolderPath);
   }
}
