#pragma once
#include "libCloudundancy/Components/Iteration/Transform/OneExtraArgTransformer.h"

template<
   typename TransformedContainerType,
   typename SourceContainerType,
   typename TransformFunctionType,
   typename Arg2Type>
class OneExtraArgTransformerMock : public Zen::Mock<OneExtraArgTransformer<TransformedContainerType, SourceContainerType, TransformFunctionType, Arg2Type>>
{
public:
   METALMOCK_NONVOID3_CONST(TransformedContainerType, Transform, const SourceContainerType&, TransformFunctionType, Arg2Type)
};
