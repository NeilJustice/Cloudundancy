#pragma once
#include "libCloudundancy/ValueTypes/AbsoluteFilePathToRelativeFolderPath.h"

namespace ZenUnit
{
   template<>
   class Equalizer<AbsoluteFilePathToRelativeFolderPath>
   {
   public:
      static void AssertEqual(
         const AbsoluteFilePathToRelativeFolderPath& expectedCloudundancyIniFileCopyInstruction,
         const AbsoluteFilePathToRelativeFolderPath& actualCloudundancyIniFileCopyInstruction);
   };
}
