#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/docoptvalueRandom.h"

namespace ZenUnit
{
   template<>
   docopt::Value Random()
   {
      const long randomLong = ZenUnit::Random<long>();
      if (randomLong % 2 == 0)
      {
         docopt::Value randomLongDocoptValue(randomLong);
         return randomLongDocoptValue;
      }
      const string randomString = ZenUnit::Random<string>();
      docopt::Value randomStringDocoptValue(randomString);
      return randomStringDocoptValue;
   }
}
