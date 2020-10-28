#pragma once

template<typename ReturnType, typename Arg1Type, typename Arg2Type>
class NonVoidTwoArgFunctionCaller
{
public:
   virtual ReturnType Call(ReturnType(*func)(Arg1Type, Arg2Type), Arg1Type arg1, Arg2Type arg2) const
   {
      const ReturnType returnValue = func(arg1, arg2);
      return returnValue;
   }

   virtual ~NonVoidTwoArgFunctionCaller() = default;
};
