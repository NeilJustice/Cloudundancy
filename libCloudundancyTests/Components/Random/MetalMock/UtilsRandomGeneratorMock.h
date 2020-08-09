#pragma once
#include "libCloudundancyTests/Components/Random/UtilsRandomGenerator.h"

class UtilsRandomGeneratorMock : public Zen::Mock<UtilsRandomGenerator>
{
public:
   METALMOCK_NONVOID0_CONST(fs::path, RelativeFilePath)
   METALMOCK_NONVOID0_CONST(fs::path, RelativeFolderPath)
};
