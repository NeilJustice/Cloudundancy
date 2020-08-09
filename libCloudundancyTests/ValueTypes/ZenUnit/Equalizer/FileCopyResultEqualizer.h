#pragma once
#include "libCloudundancy/ValueTypes/FileCopyResult.h"

namespace ZenUnit
{
   template<>
   struct Equalizer<FileCopyResult>
   {
      static void AssertEqual(const FileCopyResult& expectedFileCopyResult, const FileCopyResult& actualFileCopyResult);
   };
}
