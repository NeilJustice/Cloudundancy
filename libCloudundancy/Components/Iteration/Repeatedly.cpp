#include "pch.h"
#include "libCloudundancy/Components/Iteration/Repeatedly.h"

void Repeatedly::Call(size_t iterations, const function<void()>& func)
{
   for (size_t i = 0; i < iterations; ++i)
   {
      func();
   }
}
