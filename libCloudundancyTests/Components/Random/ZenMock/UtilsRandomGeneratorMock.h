#pragma once
#include "libCloudundancyTests/Components/Random/UtilsRandomGenerator.h"

class UtilsRandomGeneratorMock : public Zen::Mock<UtilsRandomGenerator>
{
public:
   ZENMOCK_NONVOID0_CONST(fs::path, RelativeFilePath)
   ZENMOCK_NONVOID0_CONST(fs::path, RelativeFolderPath)
};
