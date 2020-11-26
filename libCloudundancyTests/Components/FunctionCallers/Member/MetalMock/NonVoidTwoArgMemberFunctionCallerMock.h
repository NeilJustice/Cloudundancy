#pragma once
#include "libCloudundancy/Components/FunctionCallers/Member/NonVoidTwoArgMemberFunctionCaller.h"

template<typename ReturnType, typename ClassType, typename Arg1Type, typename Arg2Type>
class NonVoidTwoArgMemberFunctionCallerMock : public Metal::Mock<NonVoidTwoArgMemberFunctionCaller<ReturnType, ClassType, Arg1Type, Arg2Type>>
{
public:
   using ConstMemberFunctionType = ReturnType (ClassType::*)(Arg1Type, Arg2Type) const;
   METALMOCK_NONVOID4_CONST(ReturnType, ConstCall, ConstMemberFunctionType, const ClassType*, Arg1Type, Arg2Type)

   using NonConstMemberFunctionType = ReturnType(ClassType::*)(Arg1Type, Arg2Type);
   METALMOCK_NONVOID4_CONST(ReturnType, NonConstCall, NonConstMemberFunctionType, ClassType*, Arg1Type, Arg2Type)
};
