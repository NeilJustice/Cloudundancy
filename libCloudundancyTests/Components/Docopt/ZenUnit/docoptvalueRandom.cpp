#include "pch.h"
#include "libCloudundancyTests/Components/Docopt/ZenUnit/docoptvalueRandom.h"

namespace ZenUnit
{
   template<>
   docopt::Value Random()
   {
      const long randomLong = ZenUnit::Random<long>();
      if (randomLong % 2 == 0)
      {
         const docopt::Value randomLongDocoptValue(randomLong);
         return randomLongDocoptValue;
      }
      const string randomString = ZenUnit::Random<string>();
      const docopt::Value randomStringDocoptValue(randomString);
      return randomStringDocoptValue;
   }
}
