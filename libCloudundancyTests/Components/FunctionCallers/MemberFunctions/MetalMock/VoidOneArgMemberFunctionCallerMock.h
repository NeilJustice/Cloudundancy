#pragma once
#include "libCloudundancy/Components/FunctionCallers/MemberFunctions/VoidOneArgMemberFunctionCaller.h"

template<typename ClassType, typename ArgType>
class VoidOneArgMemberFunctionCallerMock : public Metal::Mock<VoidOneArgMemberFunctionCaller<ClassType, ArgType>>
{
public:
   using ConstMemberFunctionType = void (ClassType::*)(ArgType) const;
   METALMOCK_VOID3_CONST(CallConstMemberFunction, ConstMemberFunctionType, const ClassType*, ArgType)

   using NonConstMemberFunctionType = void (ClassType::*)(ArgType);
   METALMOCK_VOID3_CONST(CallNonConstCallMemberFunction, NonConstMemberFunctionType, ClassType*, ArgType)
};
