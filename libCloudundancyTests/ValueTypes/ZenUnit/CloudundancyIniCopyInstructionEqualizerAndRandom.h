#pragma once
#include "libCloudundancy/ValueTypes/CloudundancyIniCopyInstruction.h"

namespace ZenUnit
{
   template<>
   class Equalizer<CloudundancyIniCopyInstruction>
   {
   public:
      static void AssertEqual(
         const CloudundancyIniCopyInstruction& expectedCloudundancyIniCopyInstruction,
         const CloudundancyIniCopyInstruction& actualCloudundancyIniCopyInstruction);
   };

   CloudundancyIniCopyInstruction TestableRandomCloudundancyIniCopyInstruction(const Utils::UtilsRandomGenerator* utilsRandomGenerator);
   template<>
   CloudundancyIniCopyInstruction Random();
}
