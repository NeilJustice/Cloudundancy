#pragma once
#include "libCloudundancy/Components/Function/NonMember/VoidZeroArgFunctionCaller.h"

class VoidZeroArgFunctionCallerMock : public Zen::Mock<VoidZeroArgFunctionCaller>
{
public:
   using FunctionType = void(*)();
   ZENMOCK_VOID1_CONST(Call, FunctionType)
};
