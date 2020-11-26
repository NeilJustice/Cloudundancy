#pragma once
#include "libCloudundancy/Components/FunctionCallers/Member/VoidTwoArgMemberFunctionCaller.h"

template<typename ClassType, typename Arg1Type, typename Arg2Type>
class VoidTwoArgMemberFunctionCallerMock : public Metal::Mock<VoidTwoArgMemberFunctionCaller<ClassType, Arg1Type, Arg2Type>>
{
public:
   using ConstMemberFunctionType = void (ClassType::*)(Arg1Type, Arg2Type) const;
   METALMOCK_VOID4_CONST(ConstCall, ConstMemberFunctionType, const ClassType*, Arg1Type, Arg2Type)

   using NonConstMemberFunctionType = void (ClassType::*)(Arg1Type, Arg2Type);
   METALMOCK_VOID4_CONST(NonConstCall, NonConstMemberFunctionType, ClassType*, Arg1Type, Arg2Type)
};
