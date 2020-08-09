#pragma once

class CharVectorAllocator
{
public:
   virtual vector<char>* NewCharVector(size_t size) const;
   virtual ~CharVectorAllocator() = default;
};
