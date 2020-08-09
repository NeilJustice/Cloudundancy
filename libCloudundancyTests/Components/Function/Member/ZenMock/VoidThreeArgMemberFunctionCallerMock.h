#pragma once
#include "libCloudundancy/Components/Function/Member/VoidThreeArgMemberFunctionCaller.h"

template<typename ClassType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
class VoidThreeArgMemberFunctionCallerMock : public Zen::Mock<VoidThreeArgMemberFunctionCaller<ClassType, Arg1Type, Arg2Type, Arg3Type>>
{
public:
   using ConstMemberFunctionType = void (ClassType::*)(Arg1Type, Arg2Type, Arg3Type) const;
   ZENMOCK_VOID5_CONST(ConstCall, const ClassType*, ConstMemberFunctionType, Arg1Type, Arg2Type, Arg3Type)

   using NonConstMemberFunctionType = void (ClassType::*)(Arg1Type, Arg2Type, Arg3Type);
   ZENMOCK_VOID5_CONST(NonConstCall, ClassType*, NonConstMemberFunctionType, Arg1Type, Arg2Type, Arg3Type)
};
