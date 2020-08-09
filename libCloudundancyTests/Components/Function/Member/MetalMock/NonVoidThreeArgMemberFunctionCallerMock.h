#pragma once
#include "libCloudundancy/Components/Function/Member/NonVoidThreeArgMemberFunctionCaller.h"

template<typename ReturnType, typename ClassType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
class NonVoidThreeArgMemberFunctionCallerMock : public Zen::Mock<NonVoidThreeArgMemberFunctionCaller<ReturnType, ClassType, Arg1Type, Arg2Type, Arg3Type>>
{
public:
   using ConstMemberFunctionType = ReturnType (ClassType::*)(Arg1Type, Arg2Type, Arg3Type) const;
   METALMOCK_NONVOID5_CONST(ReturnType, ConstCall, const ClassType*, ConstMemberFunctionType, Arg1Type, Arg2Type, Arg3Type)

   using NonConstMemberFunctionType = ReturnType(ClassType::*)(Arg1Type, Arg2Type, Arg3Type);
   METALMOCK_NONVOID5_CONST(ReturnType, NonConstCall, ClassType*, NonConstMemberFunctionType, Arg1Type, Arg2Type, Arg3Type)
};
