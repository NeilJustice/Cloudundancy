#pragma once
#include "libCloudundancy/ValueTypes/CloudundancyIni.h"

namespace ZenUnit
{
   template<>
   class Equalizer<CloudundancyIni>
   {
   public:
      static void AssertEqual(const CloudundancyIni& expectedCloudundancyIni, const CloudundancyIni& actualCloudundancyIni);
   };
}
