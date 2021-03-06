#pragma once
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"

namespace ZenUnit
{
   template<>
   class Equalizer<CloudundancyArgs>
   {
   public:
      static void AssertEqual(const CloudundancyArgs& expectedCloudundancyArgs, const CloudundancyArgs& actualCloudundancyArgs);
   };

   CloudundancyArgs TestableRandomCloudundancyArgs(const ZenUnit::RandomGenerator* randomGenerator);
   template<>
   CloudundancyArgs Random();
}
