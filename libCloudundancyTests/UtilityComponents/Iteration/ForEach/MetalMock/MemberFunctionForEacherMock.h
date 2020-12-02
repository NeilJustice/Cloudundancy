#pragma once
#include "libCloudundancy/UtilityComponents/Iteration/ForEach/MemberFunctionForEacher.h"

template<typename ClassType, typename ElementType>
class MemberFunctionForEacherMock : public Metal::Mock<MemberFunctionForEacher<ClassType, ElementType>>
{
public:
   using ConstMemberFunctionType = void(ClassType::*)(const ElementType&) const;
   METALMOCK_VOID3_CONST(CallConstMemberFunctionForEachElement,
      const vector<ElementType>&, ConstMemberFunctionType, const ClassType*)
};
