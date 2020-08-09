#pragma once
#include "libCloudundancy/Components/Iteration/MemberFunctionTransformer.h"

template<typename ClassType, typename ElementType, typename TransformedElementType>
class MemberFunctionTransformerMock : public Zen::Mock<MemberFunctionTransformer<ClassType, ElementType, TransformedElementType>>
{
public:
   using MemberFunctionType = TransformedElementType(ClassType::*)(const ElementType&) const;
   ZENMOCK_NONVOID3_CONST(vector<TransformedElementType>, Transform, const vector<ElementType>&, const ClassType*, MemberFunctionType)
};
