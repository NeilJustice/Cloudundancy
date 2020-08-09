#pragma once
#include "libCloudundancy/Components/Memory/CharVectorAllocator.h"

class CharVectorAllocatorMock : public Zen::Mock<CharVectorAllocator>
{
public:
   METALMOCK_NONVOID1_CONST(vector<char>*, NewCharVector, size_t)
};
