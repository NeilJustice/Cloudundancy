#pragma once
#include "libCloudundancy/Components/Iteration/Transform/OneExtraArgMemberFunctionTransformer.h"

template<typename ClassType, typename ElementType, typename TransformedElementType, typename SecondArgType>
class OneExtraArgMemberFunctionTransformerMock : public Metal::Mock<OneExtraArgMemberFunctionTransformer<ClassType, ElementType, TransformedElementType, SecondArgType>>
{
public:
   using MemberFunctionType = TransformedElementType(ClassType::*)(const ElementType&, SecondArgType) const;
   METALMOCK_NONVOID4_CONST(vector<TransformedElementType>, Transform, const vector<ElementType>&, const ClassType*, MemberFunctionType, SecondArgType)
};
