#include "pch.h"
#include "libCloudundancy/UtilityComponents/Memory/CharVectorAllocator.h"

CharVectorAllocator::CharVectorAllocator()
{
}

vector<char>* CharVectorAllocator::NewCharVector(size_t size) const
{
   return new vector<char>(size);
}
