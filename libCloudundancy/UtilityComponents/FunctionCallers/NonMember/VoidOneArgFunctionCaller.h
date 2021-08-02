#pragma once

namespace Utils
{
   template<typename ArgType>
   class VoidOneArgFunctionCaller
   {
   public:
      VoidOneArgFunctionCaller() {}

      virtual void Call(void(*func)(ArgType), ArgType arg) const
      {
         func(arg);
      }

      virtual ~VoidOneArgFunctionCaller() = default;
   };
}