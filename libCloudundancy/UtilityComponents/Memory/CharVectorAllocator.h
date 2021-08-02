#pragma once

namespace Utils
{
   class CharVectorAllocator
   {
   public:
      CharVectorAllocator();
      virtual vector<char>* NewCharVector(size_t size) const;
      virtual ~CharVectorAllocator() = default;
   };
}
