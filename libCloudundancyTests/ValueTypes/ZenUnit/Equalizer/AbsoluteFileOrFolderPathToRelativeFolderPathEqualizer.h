#pragma once
#include "libCloudundancy/ValueTypes/AbsoluteFileOrFolderPathToRelativeFolderPath.h"

namespace ZenUnit
{
   template<>
   class Equalizer<AbsoluteFileOrFolderPathToRelativeFolderPath>
   {
   public:
      static void AssertEqual(
         const AbsoluteFileOrFolderPathToRelativeFolderPath& expectedFileCopyInstruction,
         const AbsoluteFileOrFolderPathToRelativeFolderPath& actualFileCopyInstruction);
   };
}
