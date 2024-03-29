#pragma once
#include "libCloudundancy/UtilityComponents/FunctionCallers/Member/VoidThreeArgMemberFunctionCaller.h"

namespace Utils
{
   template<typename ClassType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
   class VoidThreeArgMemberFunctionCallerMock : public Metal::Mock<VoidThreeArgMemberFunctionCaller<ClassType, Arg1Type, Arg2Type, Arg3Type>>
   {
   public:
      using ConstMemberFunctionType = void (ClassType::*)(Arg1Type, Arg2Type, Arg3Type) const;
      METALMOCK_VOID5_CONST(CallConstMemberFunction, const ClassType*, ConstMemberFunctionType, Arg1Type, Arg2Type, Arg3Type)

      using NonConstMemberFunctionType = void (ClassType::*)(Arg1Type, Arg2Type, Arg3Type);
      METALMOCK_VOID5_CONST(CallNonConstMemberFunction, ClassType*, NonConstMemberFunctionType, Arg1Type, Arg2Type, Arg3Type)
   };
}