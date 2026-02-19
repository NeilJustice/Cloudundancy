#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/docoptvalueRandom.h"

TESTS(docoptvalueRandomTests)
AFACT(ZenUnitRandomDocoptValue_ReturnsdocoptvalueThatIsEitherALongOrAString)
EVIDENCE

TEST(ZenUnitRandomDocoptValue_ReturnsdocoptvalueThatIsEitherALongOrAString)
{
   const docopt::value randomDocoptValue = ZenUnit::Random<docopt::value>();
   IS_TRUE(randomDocoptValue.isLong() || randomDocoptValue.isString());
}

RUN_TESTS(docoptvalueRandomTests)
