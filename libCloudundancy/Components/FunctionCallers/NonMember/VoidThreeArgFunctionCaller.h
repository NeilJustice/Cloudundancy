#pragma once

template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
class VoidThreeArgFunctionCaller
{
public:
   virtual void Call(void(*func)(Arg1Type, Arg2Type, Arg3Type), Arg1Type arg1, Arg2Type arg2, Arg3Type arg3) const
   {
      func(arg1, arg2, arg3);
   }

   virtual ~VoidThreeArgFunctionCaller() = default;
};
