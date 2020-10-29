#pragma once
#include "libCloudundancy/ValueTypes/AbsoluteSourceFilePath_RelativeDestinationFolderPath.h"

namespace ZenUnit
{
   template<>
   class Equalizer<AbsoluteSourceFilePath_RelativeDestinationFolderPath>
   {
   public:
      static void AssertEqual(
         const AbsoluteSourceFilePath_RelativeDestinationFolderPath& expected,
         const AbsoluteSourceFilePath_RelativeDestinationFolderPath& actual);
   };
}
