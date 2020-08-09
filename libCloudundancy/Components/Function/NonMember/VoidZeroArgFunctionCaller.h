#pragma once

class VoidZeroArgFunctionCaller
{
public:
   virtual ~VoidZeroArgFunctionCaller();
   virtual void Call(void(*func)()) const;
};
