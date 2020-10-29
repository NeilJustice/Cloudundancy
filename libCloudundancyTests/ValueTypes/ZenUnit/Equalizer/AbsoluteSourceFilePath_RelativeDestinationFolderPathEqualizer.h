#pragma once
#include "libCloudundancy/ValueTypes/AbsoluteFilePathToRelativeDestinationFolderPath.h"

namespace ZenUnit
{
   template<>
   class Equalizer<AbsoluteFilePathToRelativeDestinationFolderPath>
   {
   public:
      static void AssertEqual(
         const AbsoluteFilePathToRelativeDestinationFolderPath& expected,
         const AbsoluteFilePathToRelativeDestinationFolderPath& actual);
   };
}
