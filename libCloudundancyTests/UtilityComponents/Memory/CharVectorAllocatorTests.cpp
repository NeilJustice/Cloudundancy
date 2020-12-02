#include "pch.h"
#include "libCloudundancy/UtilityComponents/Memory/CharVectorAllocator.h"

TESTS(CharVectorAllocatorTests)
AFACT(NewCharVector_ReturnsOperatorNewedCharVectorWithSpecifiedSize)
EVIDENCE

CharVectorAllocator _charVectorAllocator;

TEST(NewCharVector_ReturnsOperatorNewedCharVectorWithSpecifiedSize)
{
   CharVectorAllocator charVectorAllocator;
   const size_t size = ZenUnit::RandomBetween<size_t>(0, 3);
   //
   const vector<char>* charVector = charVectorAllocator.NewCharVector(size);
   //
   ARE_EQUAL(size, charVector->size());
   DELETE_TO_ASSERT_NEWED(charVector);
}

RUN_TESTS(CharVectorAllocatorTests)
