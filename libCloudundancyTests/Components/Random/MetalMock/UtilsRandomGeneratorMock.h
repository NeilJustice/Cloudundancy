#pragma once
#include "libCloudundancyTests/Components/Random/UtilsRandomGenerator.h"

namespace Utils
{
   class UtilsRandomGeneratorMock : public Metal::Mock<UtilsRandomGenerator>
   {
   public:
      METALMOCK_NONVOID0_CONST(fs::path, RelativeFilePath)
      METALMOCK_NONVOID0_CONST(fs::path, RelativeFolderPath)
      METALMOCK_NONVOID0_CONST(vector<fs::path>, RelativeFolderPaths)
   };
}
