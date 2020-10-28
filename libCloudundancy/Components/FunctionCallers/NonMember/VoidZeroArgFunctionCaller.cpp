#include "pch.h"
#include "libCloudundancy/Components/FunctionCallers/NonMember/VoidZeroArgFunctionCaller.h"

VoidZeroArgFunctionCaller::~VoidZeroArgFunctionCaller()
{
}

void VoidZeroArgFunctionCaller::Call(void(*func)()) const
{
   func();
}
