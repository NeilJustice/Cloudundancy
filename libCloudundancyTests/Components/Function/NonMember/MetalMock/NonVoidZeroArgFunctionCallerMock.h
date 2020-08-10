#pragma once
#include "libCloudundancy/Components/Function/NonMember/NonVoidZeroArgFunctionCaller.h"

template<typename ReturnType>
class NonVoidZeroArgFunctionCallerMock : public Metal::Mock<NonVoidZeroArgFunctionCaller<ReturnType>>
{
public:
   using FunctionType = ReturnType(*)();
   METALMOCK_NONVOID1_CONST(ReturnType, Call, FunctionType)
};
