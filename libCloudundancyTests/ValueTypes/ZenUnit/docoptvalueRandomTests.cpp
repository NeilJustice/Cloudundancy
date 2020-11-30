#include "pch.h"
#include "libCloudundancyTests/ValueTypes/ZenUnit/docoptvalueRandom.h"

TESTS(docoptvalueRandomTests)
AFACT(ZenUnitRandomDocoptValue_ReturnsdocoptvalueThatIsEitherALongOrAString)
EVIDENCE

TEST(ZenUnitRandomDocoptValue_ReturnsdocoptvalueThatIsEitherALongOrAString)
{
   const docopt::Value randomDocoptValue = ZenUnit::Random<docopt::Value>();
   IS_TRUE(randomDocoptValue.IsLong() || randomDocoptValue.IsString());
}

RUN_TESTS(docoptvalueRandomTests)
