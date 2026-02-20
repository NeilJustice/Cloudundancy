#pragma once

namespace Utils
{
   class CharVectorAllocator
   {
   public:
      CharVectorAllocator();
      virtual ~CharVectorAllocator() = default;

      virtual vector<char>* NewCharVector(size_t size) const;
   };
}
