#pragma once
#include "libCloudundancy/Components/FunctionCallers/Member/VoidZeroArgMemberFunctionCaller.h"

namespace Utils
{
   template<typename ClassType>
   class VoidZeroArgMemberFunctionCallerMock : public Metal::Mock<VoidZeroArgMemberFunctionCaller<ClassType>>
   {
   public:
      using ConstMemberFunctionType = void (ClassType::*)() const;
      using NonConstMemberFunctionType = void (ClassType::*)();

      METALMOCK_VOID2_CONST(CallConstMemberFunction,
         const ClassType*,
         ConstMemberFunctionType)

      METALMOCK_VOID2_CONST(CallCallNonConstMemberFunctionMemberFunction,
         ClassType*,
         NonConstMemberFunctionType)
   };
}
