#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/AbsoluteSourceFilePath_RelativeDestinationFolderPathEqualizer.h"

namespace ZenUnit
{
   void Equalizer<AbsoluteFilePathToRelativeDestinationFolderPath>::AssertEqual(
      const AbsoluteFilePathToRelativeDestinationFolderPath& expected,
      const AbsoluteFilePathToRelativeDestinationFolderPath& actual)
   {
      ARE_EQUAL(expected.absoluteSourceFilePath, actual.absoluteSourceFilePath);
      ARE_EQUAL(expected.relativeDestinationFolderPath, actual.relativeDestinationFolderPath);
   }
}