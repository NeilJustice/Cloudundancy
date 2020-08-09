#pragma once
#include "libCloudundancy/Components/Function/NonMember/VoidTwoArgFunctionCaller.h"

template<typename Arg1Type, typename Arg2Type>
class VoidTwoArgFunctionCallerMock : public Zen::Mock<VoidTwoArgFunctionCaller<Arg1Type, Arg2Type>>
{
public:
   using FunctionType = void(*)(Arg1Type, Arg2Type);
   ZENMOCK_VOID3_CONST(Call, FunctionType, Arg1Type, Arg2Type)
};
