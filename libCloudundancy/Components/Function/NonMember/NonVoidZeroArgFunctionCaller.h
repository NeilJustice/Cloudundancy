#pragma once

template<typename ReturnType>
class NonVoidZeroArgFunctionCaller
{
public:
   virtual ReturnType Call(ReturnType(*func)()) const
   {
      const ReturnType returnValue = func();
      return returnValue;
   }

   virtual ~NonVoidZeroArgFunctionCaller() = default;
};
