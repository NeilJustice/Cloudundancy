#pragma once
#include "libCloudundancy/Components/Function/NonMember/VoidZeroArgFunctionCaller.h"

class VoidZeroArgFunctionCallerMock : public Metal::Mock<VoidZeroArgFunctionCaller>
{
public:
   using FunctionType = void(*)();
   METALMOCK_VOID1_CONST(Call, FunctionType)
};
