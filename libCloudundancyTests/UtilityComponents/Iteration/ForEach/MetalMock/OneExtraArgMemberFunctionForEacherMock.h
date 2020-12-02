#pragma once
#include "libCloudundancy/UtilityComponents/Iteration/ForEach/OneExtraArgMemberFunctionForEacher.h"

template<typename ClassType, typename ElementType, typename ExtraArgType>
class OneExtraArgMemberFunctionForEacherMock :
   public Metal::Mock<OneExtraArgMemberFunctionForEacher<ClassType, ElementType, ExtraArgType>>
{
public:
   using ConstMemberFunctionType = void(ClassType::*)(const ElementType&, ExtraArgType) const;
   METALMOCK_VOID4_CONST(CallConstMemberFunctionForEachElement,
      const vector<ElementType>&, ConstMemberFunctionType, const ClassType*, ExtraArgType)
};
