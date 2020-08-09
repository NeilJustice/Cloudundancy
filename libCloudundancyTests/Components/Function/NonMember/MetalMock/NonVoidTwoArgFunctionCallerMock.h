#pragma once
#include "libCloudundancy/Components/Function/NonMember/NonVoidTwoArgFunctionCaller.h"

template<typename ReturnType, typename Arg1Type, typename Arg2Type>
class NonVoidTwoArgFunctionCallerMock : public Zen::Mock<NonVoidTwoArgFunctionCaller<ReturnType, Arg1Type, Arg2Type>>
{
public:
   using FunctionType = ReturnType(*)(Arg1Type, Arg2Type);
   METALMOCK_NONVOID3_CONST(ReturnType, Call, FunctionType, Arg1Type, Arg2Type)
};
