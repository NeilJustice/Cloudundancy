#pragma once
#include "libCloudundancy/UtilityComponents/Iteration/ForEach/TwoArgMemberFunctionForEacher.h"

namespace Utils
{
   template<typename ClassType, typename ElementType, typename ExtraArgType>
   class TwoArgMemberFunctionForEacherMock :
      public Metal::Mock<TwoArgMemberFunctionForEacher<ClassType, ElementType, ExtraArgType>>
   {
   public:
      using ConstMemberFunctionType = void(ClassType::*)(const ElementType&, ExtraArgType) const;
      METALMOCK_VOID4_CONST(CallConstMemberFunctionWithEachElement,
         const vector<ElementType>&, ConstMemberFunctionType, const ClassType*, ExtraArgType)
   };
}