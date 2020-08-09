#pragma once
#include "libCloudundancy/Components/Function/Member/NonVoidOneArgMemberFunctionCaller.h"

template<typename ReturnType, typename ClassType, typename ArgType>
class NonVoidOneArgMemberFunctionCallerMock : public Zen::Mock<NonVoidOneArgMemberFunctionCaller<ReturnType, ClassType, ArgType>>
{
public:
   using MemberFunctionType = ReturnType (ClassType::*)(ArgType) const;
   ZENMOCK_NONVOID3_CONST(ReturnType, CallConstMemberFunction, MemberFunctionType, const ClassType*, ArgType)
};
