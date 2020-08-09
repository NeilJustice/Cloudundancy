#pragma once
#include "libCloudundancy/Components/Function/Member/VoidZeroArgMemberFunctionCaller.h"

template<typename ClassType>
class VoidZeroArgMemberFunctionCallerMock : public Zen::Mock<VoidZeroArgMemberFunctionCaller<ClassType>>
{
public:
   using ConstMemberFunctionType = void (ClassType::*)() const;
   ZENMOCK_VOID2_CONST(ConstCall, const ClassType*, ConstMemberFunctionType)

   using NonConstMemberFunctionType = void (ClassType::*)();
   ZENMOCK_VOID2_CONST(NonConstCall, ClassType*, NonConstMemberFunctionType)
};
