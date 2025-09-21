#pragma once
#include "libCloudundancy/Components/Iteration/ForEach/MemberFunctionForEacher.h"

namespace Utils
{
   template<typename ClassType, typename ElementType>
   class MemberFunctionForEacherMock : public Metal::Mock<MemberFunctionForEacher<ClassType, ElementType>>
   {
   public:
      using ConstMemberFunctionType = void(ClassType::*)(const ElementType&) const;
      METALMOCK_VOID3_CONST(CallConstMemberFunctionWithEachElement,
         const vector<ElementType>&, ConstMemberFunctionType, const ClassType*)
   };
}