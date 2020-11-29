#pragma once

namespace ZenUnit
{
   template<>
   class Equalizer<tm>
   {
   public:
      static void AssertEqual(const tm& expectedTm, const tm& actualTm);
   };

   template<>
   tm Random();

   tm TestableTmRandom(const RandomGenerator* randomGenerator);
}
