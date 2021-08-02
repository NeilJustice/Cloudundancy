#pragma once
#include "libCloudundancy/UtilityComponents/Iteration/Transform/OneExtraArgTransformer.h"

namespace Utils
{
   template<
      typename TransformedContainerType,
      typename SourceContainerType,
      typename TransformFunctionType,
      typename ExtraArgType>
   class OneExtraArgTransformerMock : public Metal::Mock<
      OneExtraArgTransformer<TransformedContainerType, SourceContainerType, TransformFunctionType, ExtraArgType>>
   {
   public:
      METALMOCK_NONVOID3_CONST(TransformedContainerType, Transform, const SourceContainerType&, TransformFunctionType, ExtraArgType)
   };
}