#pragma once
#include "libCloudundancy/ValueTypes/AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath.h"

namespace ZenUnit
{
   template<>
   class Equalizer<AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath>
   {
   public:
      static void AssertEqual(
         const AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath& expectedFileCopyInstruction,
         const AbsoluteSourceFileOrFolderPath_RelativeDestinationFolderPath& actualFileCopyInstruction);
   };
}
