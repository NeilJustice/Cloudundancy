#pragma once

namespace ZenUnit
{
   template<>
   class Equalizer<tm>
   {
   public:
      static void AssertEqual(const tm& expectedTm, const tm& actualTm);
   };

   tm TestableRandomtm(const RandomGenerator* randomGenerator);
   template<>
   tm Random();
}
