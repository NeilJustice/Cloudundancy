#pragma once
#include "libCloudundancy/Components/Function/NonMember/VoidOneArgFunctionCaller.h"

template<typename ArgType>
class VoidOneArgFunctionCallerMock : public Metal::Mock<VoidOneArgFunctionCaller<ArgType>>
{
public:
   using FunctionType = void(*)(ArgType);
   METALMOCK_VOID2_CONST(Call, FunctionType, ArgType)
};
