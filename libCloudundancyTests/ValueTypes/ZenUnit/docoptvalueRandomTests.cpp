#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/docoptvalueRandom.h"

TESTS(docoptvalueRandomTests)
AFACT(RandomDocoptValue_ReturnsdocoptvalueWithAllNonDefaultFields)
EVIDENCE

TEST(RandomDocoptValue_ReturnsdocoptvalueWithAllNonDefaultFields)
{
   const docopt::Value randomDocoptValue = ZenUnit::Random<docopt::Value>();
   IS_TRUE(randomDocoptValue.IsLong() || randomDocoptValue.IsString());
}

RUN_TESTS(docoptvalueRandomTests)
