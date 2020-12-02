#pragma once
#include "libCloudundancy/UtilityComponents/FunctionCallers/MemberFunctions/VoidThreeArgMemberFunctionCaller.h"

template<typename ClassType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
class VoidThreeArgMemberFunctionCallerMock : public Metal::Mock<VoidThreeArgMemberFunctionCaller<ClassType, Arg1Type, Arg2Type, Arg3Type>>
{
public:
   using ConstMemberFunctionType = void (ClassType::*)(Arg1Type, Arg2Type, Arg3Type) const;
   METALMOCK_VOID5_CONST(ConstCall, ConstMemberFunctionType, const ClassType*, Arg1Type, Arg2Type, Arg3Type)

   using NonConstMemberFunctionType = void (ClassType::*)(Arg1Type, Arg2Type, Arg3Type);
   METALMOCK_VOID5_CONST(NonConstCall, NonConstMemberFunctionType, ClassType*, Arg1Type, Arg2Type, Arg3Type)
};
