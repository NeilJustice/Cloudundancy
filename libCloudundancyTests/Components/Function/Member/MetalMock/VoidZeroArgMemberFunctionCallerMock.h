#pragma once
#include "libCloudundancy/Components/Function/Member/VoidZeroArgMemberFunctionCaller.h"

template<typename ClassType>
class VoidZeroArgMemberFunctionCallerMock : public Metal::Mock<VoidZeroArgMemberFunctionCaller<ClassType>>
{
public:
   using ConstMemberFunctionType = void (ClassType::*)() const;
   METALMOCK_VOID2_CONST(ConstCall, const ClassType*, ConstMemberFunctionType)

   using NonConstMemberFunctionType = void (ClassType::*)();
   METALMOCK_VOID2_CONST(NonConstCall, ClassType*, NonConstMemberFunctionType)
};
