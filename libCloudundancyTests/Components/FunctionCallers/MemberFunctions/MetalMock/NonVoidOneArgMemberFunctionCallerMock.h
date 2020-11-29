#pragma once
#include "libCloudundancy/Components/FunctionCallers/MemberFunctions/NonVoidOneArgMemberFunctionCaller.h"

template<typename ReturnType, typename ClassType, typename ArgType>
class NonVoidOneArgMemberFunctionCallerMock : public Metal::Mock<NonVoidOneArgMemberFunctionCaller<ReturnType, ClassType, ArgType>>
{
public:
   using MemberFunctionType = ReturnType (ClassType::*)(ArgType) const;
   METALMOCK_NONVOID3_CONST(ReturnType, CallConstMemberFunction, MemberFunctionType, const ClassType*, ArgType)
};
