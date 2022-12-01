#pragma once
#include "libCloudundancy/ValueTypes/ProcessResult.h"

namespace ZenUnit
{
   template<>
   struct Equalizer<Utils::ProcessResult>
   {
      static void AssertEqual(const Utils::ProcessResult& expectedProcessResult, const Utils::ProcessResult& actualProcessResult);
   };

   Utils::ProcessResult TestableRandomProcessResult(const ZenUnit::RandomGenerator* randomGenerator);
   template<>
   Utils::ProcessResult Random<Utils::ProcessResult>();
}
