#pragma once
#include "libCloudundancy/Components/Function/NonMember/NonVoidOneArgFunctionCaller.h"

template<typename ReturnType, typename ArgType>
class NonVoidOneArgFunctionCallerMock : public Zen::Mock<NonVoidOneArgFunctionCaller<ReturnType, ArgType>>
{
public:
   using FunctionType = ReturnType(*)(ArgType);
   METALMOCK_NONVOID2_CONST(ReturnType, Call, FunctionType, ArgType)
};
