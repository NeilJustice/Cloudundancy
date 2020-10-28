#pragma once
#include "libCloudundancy/Components/FunctionCallers/Member/VoidOneArgMemberFunctionCaller.h"

template<typename ClassType, typename ArgType>
class VoidOneArgMemberFunctionCallerMock : public Metal::Mock<VoidOneArgMemberFunctionCaller<ClassType, ArgType>>
{
public:
   using ConstMemberFunctionType = void (ClassType::*)(ArgType) const;
   METALMOCK_VOID3_CONST(ConstCall, const ClassType*, ConstMemberFunctionType, ArgType)

   using NonConstMemberFunctionType = void (ClassType::*)(ArgType);
   METALMOCK_VOID3_CONST(NonConstCall, ClassType*, NonConstMemberFunctionType, ArgType)
};
