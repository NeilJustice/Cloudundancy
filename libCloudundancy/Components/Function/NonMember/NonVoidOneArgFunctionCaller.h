#pragma once

template<typename ReturnType, typename ArgType>
class NonVoidOneArgFunctionCaller
{
public:
   virtual ReturnType Call(ReturnType(*func)(ArgType), ArgType arg) const
   {
      const ReturnType returnValue = func(arg);
      return returnValue;
   }

   virtual ~NonVoidOneArgFunctionCaller() = default;
};
