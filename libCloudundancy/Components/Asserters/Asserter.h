#pragma once

namespace Utils
{
   class Asserter
   {
   public:
      virtual ~Asserter() = default;

      virtual void ThrowIfIntsNotEqual(int expected, int actual, string_view message) const;
      virtual void ThrowIfSizeTsNotEqual(size_t expected, size_t actual, string_view message) const;
   };
}
