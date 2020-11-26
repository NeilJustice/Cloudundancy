#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPathEqualizer.h"

namespace ZenUnit
{
   void Equalizer<AbsoluteFileOrFolderPathToRelativeFolderPath>::AssertEqual(
      const AbsoluteFileOrFolderPathToRelativeFolderPath& expected,
      const AbsoluteFileOrFolderPathToRelativeFolderPath& actual)
   {
      ARE_EQUAL(expected.absoluteSourceFileOrFolderPath, actual.absoluteSourceFileOrFolderPath);
      ARE_EQUAL(expected.relativeDestinationFolderPath, actual.relativeDestinationFolderPath);
   }
}
