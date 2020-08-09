#pragma once
#include "libCloudundancy/Components/Memory/CharVectorAllocator.h"

class CharVectorAllocatorMock : public Zen::Mock<CharVectorAllocator>
{
public:
   ZENMOCK_NONVOID1_CONST(vector<char>*, NewCharVector, size_t)
};
