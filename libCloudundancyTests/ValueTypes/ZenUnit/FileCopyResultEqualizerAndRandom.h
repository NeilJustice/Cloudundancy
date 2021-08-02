#pragma once
#include "libCloudundancy/ValueTypes/FileCopyResult.h"

namespace ZenUnit
{
   template<>
   struct Equalizer<Utils::FileCopyResult>
   {
      static void AssertEqual(
         const Utils::FileCopyResult& expectedFileCopyResult, const Utils::FileCopyResult& actualFileCopyResult);
   };

   Utils::FileCopyResult TestableRandomFileCopyResult(const RandomGenerator* randomGenerator);
   template<>
   Utils::FileCopyResult Random();
}
