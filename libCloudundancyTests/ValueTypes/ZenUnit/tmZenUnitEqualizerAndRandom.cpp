#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/tmZenUnitEqualizerAndRandom.h"

namespace ZenUnit
{
   void Equalizer<tm>::AssertEqual(const tm& expectedTm, const tm& actualTm)
   {
      ARE_EQUAL(expectedTm.tm_sec, actualTm.tm_sec);
      ARE_EQUAL(expectedTm.tm_min, actualTm.tm_min);
      ARE_EQUAL(expectedTm.tm_hour, actualTm.tm_hour);
      ARE_EQUAL(expectedTm.tm_mday, actualTm.tm_mday);
      ARE_EQUAL(expectedTm.tm_mon, actualTm.tm_mon);
      ARE_EQUAL(expectedTm.tm_year, actualTm.tm_year);
      ARE_EQUAL(expectedTm.tm_wday, actualTm.tm_wday);
      ARE_EQUAL(expectedTm.tm_yday, actualTm.tm_yday);
      ARE_EQUAL(expectedTm.tm_isdst, actualTm.tm_isdst);
   }

   tm TestableRandomtm(const RandomGenerator* randomGenerator)
   {
      tm randomTm;
      randomTm.tm_sec = randomGenerator->Int();
      randomTm.tm_min = randomGenerator->Int();
      randomTm.tm_hour = randomGenerator->Int();
      randomTm.tm_mday = randomGenerator->Int();
      randomTm.tm_mon = randomGenerator->Int();
      randomTm.tm_year = randomGenerator->Int();
      randomTm.tm_wday = randomGenerator->Int();
      randomTm.tm_yday = randomGenerator->Int();
      randomTm.tm_isdst = randomGenerator->Int();
      return randomTm;
   }

   template<>
   tm Random<tm>()
   {
      return TestableRandomtm(RandomGenerator::Instance());
   }
}
