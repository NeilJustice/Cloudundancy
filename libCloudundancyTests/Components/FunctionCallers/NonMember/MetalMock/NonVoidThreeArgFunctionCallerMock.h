#pragma once
#include "libCloudundancy/Components/FunctionCallers/NonMember/NonVoidThreeArgFunctionCaller.h"

template<typename ReturnType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
class NonVoidThreeArgFunctionCallerMock : public Metal::Mock<NonVoidThreeArgFunctionCaller<ReturnType, Arg1Type, Arg2Type, Arg3Type>>
{
public:
   using FunctionType = ReturnType(*)(Arg1Type, Arg2Type, Arg3Type);
   METALMOCK_NONVOID4_CONST(ReturnType, Call, FunctionType, Arg1Type, Arg2Type, Arg3Type)
};
