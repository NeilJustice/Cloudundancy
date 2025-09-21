#pragma once
#include "libCloudundancy/Components/Iteration/ForEach/TwoArgMemberFunctionForEacher.h"

namespace Utils
{
   template<typename ClassType, typename ElementType, typename Arg2Type>
   class TwoArgMemberFunctionForEacherMock :
      public Metal::Mock<TwoArgMemberFunctionForEacher<ClassType, ElementType, Arg2Type>>
   {
   public:
      using ConstMemberFunctionType = void(ClassType::*)(const ElementType&, Arg2Type) const;
      METALMOCK_VOID4_CONST(CallConstMemberFunctionWithEachElement,
         const vector<ElementType>&, const ClassType*, ConstMemberFunctionType, Arg2Type)
   };
}