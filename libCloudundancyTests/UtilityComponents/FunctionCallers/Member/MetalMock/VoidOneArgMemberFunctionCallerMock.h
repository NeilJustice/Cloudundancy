#pragma once
#include "libCloudundancy/UtilityComponents/FunctionCallers/Member/VoidOneArgMemberFunctionCaller.h"

namespace Utils
{
   template<typename ClassType, typename ArgType>
   class VoidOneArgMemberFunctionCallerMock : public Metal::Mock<VoidOneArgMemberFunctionCaller<ClassType, ArgType>>
   {
   public:
      using ConstMemberFunctionType = void (ClassType::*)(ArgType) const;
      METALMOCK_VOID3_CONST(CallConstMemberFunction, const ClassType*, ConstMemberFunctionType, ArgType)

      using NonConstMemberFunctionType = void (ClassType::*)(ArgType);
      METALMOCK_VOID3_CONST(CallNonConstCallMemberFunction, ClassType*, NonConstMemberFunctionType, ArgType)
   };
}