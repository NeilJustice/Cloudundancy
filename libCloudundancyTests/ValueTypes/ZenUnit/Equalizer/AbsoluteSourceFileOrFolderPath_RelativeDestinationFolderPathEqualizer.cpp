#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPathEqualizer.h"

namespace ZenUnit
{
   void Equalizer<AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath>::AssertEqual(
      const AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath& expected,
      const AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath& actual)
   {
      ARE_EQUAL(expected.absoluteSourceFileOrFolderPath, actual.absoluteSourceFileOrFolderPath);
      ARE_EQUAL(expected.relativeDestinationFolderPath, actual.relativeDestinationFolderPath);
   }
}
