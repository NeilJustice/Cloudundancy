#pragma once
#include "libCloudundancy/Components/Iteration/ForEach/OneArgMemberFunctionForEacher.h"

namespace Utils
{
   template<typename ClassType, typename ElementType>
   class OneArgMemberFunctionForEacherMock : public Metal::Mock<OneArgMemberFunctionForEacher<ClassType, ElementType>>
   {
   public:
      using ConstMemberFunctionType = void(ClassType::*)(const ElementType&) const;

      METALMOCK_VOID3_CONST(CallConstMemberFunctionWithEachElement,
         const vector<ElementType>&,
         const ClassType*, ConstMemberFunctionType)
   };
}
