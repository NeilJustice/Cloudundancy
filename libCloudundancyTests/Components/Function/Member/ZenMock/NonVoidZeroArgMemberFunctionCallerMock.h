#pragma once
#include "libCloudundancy/Components/Function/Member/NonVoidZeroArgMemberFunctionCaller.h"

template<typename ReturnType, typename ClassType>
class NonVoidZeroArgMemberFunctionCallerMock : public Zen::Mock<NonVoidZeroArgMemberFunctionCaller<ReturnType, ClassType>>
{
public:
   using ConstMemberFunctionType = ReturnType(ClassType::*)() const;
   ZENMOCK_NONVOID2_CONST(ReturnType, ConstCall, const ClassType*, ConstMemberFunctionType)

   using NonConstMemberFunctionType = ReturnType(ClassType::*)();
   ZENMOCK_NONVOID2_CONST(ReturnType, NonConstCall, ClassType*, NonConstMemberFunctionType)
};
