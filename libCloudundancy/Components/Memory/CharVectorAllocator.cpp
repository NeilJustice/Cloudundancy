#include "pch.h"
#include "libCloudundancy/Components/Memory/CharVectorAllocator.h"

vector<char>* CharVectorAllocator::NewCharVector(size_t size) const
{
   return new vector<char>(size);
}
