#pragma once
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"
#include "libCloudundancyTests/Components/Random/UtilsRandomGenerator.h"

CloudundancyArgs RandomCloudundancyArgs(
   const ZenUnit::RandomGenerator* randomGenerator, const UtilsRandomGenerator* utilsRandomGenerator);

namespace ZenUnit
{
   template<>
   CloudundancyArgs Random();
}
