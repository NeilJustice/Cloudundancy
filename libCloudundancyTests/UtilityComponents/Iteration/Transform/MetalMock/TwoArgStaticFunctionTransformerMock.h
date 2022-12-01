#pragma once
#include "libCloudundancy/UtilityComponents/Iteration/Transform/TwoArgStaticFunctionTransformer.h"

namespace Utils
{
   template<
      typename TransformedContainerType,
      typename SourceContainerType,
      typename TransformFunctionType,
      typename ExtraArgType>
   class TwoArgStaticFunctionTransformerMock : public Metal::Mock<
      TwoArgStaticFunctionTransformer<TransformedContainerType, SourceContainerType, TransformFunctionType, ExtraArgType>>
   {
   public:
      METALMOCK_NONVOID3_CONST(TransformedContainerType, Transform, const SourceContainerType&, TransformFunctionType, ExtraArgType)
   };
}