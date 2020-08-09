#pragma once

template<typename ReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
class NonVoidThreeArgFunctionCaller
{
public:
   virtual ReturnType Call(ReturnType(*func)(Arg1Type, Arg2Type, Arg3Type), Arg1Type arg1, Arg2Type arg2, Arg3Type arg3) const
   {
      const ReturnType returnValue = func(arg1, arg2, arg3);
      return returnValue;
   }

   virtual ~NonVoidThreeArgFunctionCaller() = default;
};
