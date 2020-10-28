#pragma once
#include "libCloudundancy/Components/FunctionCallers/NonMember/VoidThreeArgFunctionCaller.h"

template<typename Arg1Type, typename Arg2Type, typename Arg3Type>
class VoidThreeArgFunctionCallerMock : public Metal::Mock<VoidThreeArgFunctionCaller<Arg1Type, Arg2Type, Arg3Type>>
{
public:
   using FunctionType = void(*)(Arg1Type, Arg2Type, Arg3Type);
   METALMOCK_VOID4_CONST(Call, FunctionType, Arg1Type, Arg2Type, Arg3Type)
};