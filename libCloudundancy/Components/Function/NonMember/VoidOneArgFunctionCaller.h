#pragma once

template<typename ArgType>
class VoidOneArgFunctionCaller
{
public:
   virtual void Call(void(*func)(ArgType), ArgType arg) const
   {
      func(arg);
   }

   virtual ~VoidOneArgFunctionCaller() = default;
};
