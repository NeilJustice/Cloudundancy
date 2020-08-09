#pragma once
#include "libCloudundancy/Components/Function/Member/VoidOneArgMemberFunctionCaller.h"

template<typename ClassType, typename ArgType>
class VoidOneArgMemberFunctionCallerMock : public Zen::Mock<VoidOneArgMemberFunctionCaller<ClassType, ArgType>>
{
public:
   using ConstMemberFunctionType = void (ClassType::*)(ArgType) const;
   ZENMOCK_VOID3_CONST(ConstCall, const ClassType*, ConstMemberFunctionType, ArgType)

   using NonConstMemberFunctionType = void (ClassType::*)(ArgType);
   ZENMOCK_VOID3_CONST(NonConstCall, ClassType*, NonConstMemberFunctionType, ArgType)
};
