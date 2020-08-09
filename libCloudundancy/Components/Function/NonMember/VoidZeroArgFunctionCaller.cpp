#include "pch.h"
#include "libCloudundancy/Components/Function/NonMember/VoidZeroArgFunctionCaller.h"

VoidZeroArgFunctionCaller::~VoidZeroArgFunctionCaller()
{
}

void VoidZeroArgFunctionCaller::Call(void(*func)()) const
{
   func();
}
