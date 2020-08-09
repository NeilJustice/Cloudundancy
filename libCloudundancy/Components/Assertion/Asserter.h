#pragma once

class Asserter
{
public:
   virtual ~Asserter();
   virtual void ThrowIfNotEqual(size_t expected, size_t actual, string_view message) const;
};
