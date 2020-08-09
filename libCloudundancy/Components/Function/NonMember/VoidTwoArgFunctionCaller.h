#pragma once

template<typename Arg1Type, typename Arg2Type>
class VoidTwoArgFunctionCaller
{
public:
   virtual void Call(void(*func)(Arg1Type, Arg2Type), Arg1Type arg1, Arg2Type arg2) const
   {
      func(arg1, arg2);
   }

   virtual ~VoidTwoArgFunctionCaller() = default;
};
