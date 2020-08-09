#pragma once
#include "libCloudundancy/Components/Function/Member/VoidTwoArgMemberFunctionCaller.h"

template<typename ClassType, typename Arg1Type, typename Arg2Type>
class VoidTwoArgMemberFunctionCallerMock : public Zen::Mock<VoidTwoArgMemberFunctionCaller<ClassType, Arg1Type, Arg2Type>>
{
public:
   using ConstMemberFunctionType = void (ClassType::*)(Arg1Type, Arg2Type) const;
   ZENMOCK_VOID4_CONST(ConstCall, const ClassType*, ConstMemberFunctionType, Arg1Type, Arg2Type)

   using NonConstMemberFunctionType = void (ClassType::*)(Arg1Type, Arg2Type);
   ZENMOCK_VOID4_CONST(NonConstCall, ClassType*, NonConstMemberFunctionType, Arg1Type, Arg2Type)
};
