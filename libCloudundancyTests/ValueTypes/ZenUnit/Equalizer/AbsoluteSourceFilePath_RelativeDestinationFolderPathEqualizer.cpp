#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/Equalizer/AbsoluteSourceFilePath_RelativeDestinationFolderPathEqualizer.h"

namespace ZenUnit
{
   void Equalizer<AbsoluteSourceFilePath_RelativeDestinationFolderPath>::AssertEqual(
      const AbsoluteSourceFilePath_RelativeDestinationFolderPath& expected,
      const AbsoluteSourceFilePath_RelativeDestinationFolderPath& actual)
   {
      ARE_EQUAL(expected.absoluteSourceFilePath, actual.absoluteSourceFilePath);
      ARE_EQUAL(expected.relativeDestinationFolderPath, actual.relativeDestinationFolderPath);
   }
}
