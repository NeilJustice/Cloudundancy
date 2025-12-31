#pragma once
#include "libCloudundancy/Components/Memory/CharVectorAllocator.h"

namespace Utils
{
   class CharVectorAllocatorMock : public Metal::Mock<CharVectorAllocator>
   {
   public:
      METALMOCK_NONVOID1_CONST(vector<char>*, NewCharVector, size_t)
   };
}
