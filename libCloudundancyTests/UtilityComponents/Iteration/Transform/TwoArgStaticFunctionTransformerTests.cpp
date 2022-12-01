#include "pch.h"
#include "libCloudundancy/UtilityComponents/Iteration/Transform/TwoArgStaticFunctionTransformer.h"

template<
   template<typename...>
   class TransformedContainerType, typename TransformedElementType,
   template<typename...>
   class SourceContainerType, typename SourceElementType,
   typename ExtraArgType>
TEMPLATE_TESTS(TwoArgStaticFunctionTransformerTests, TransformedContainerType, TransformedElementType, SourceContainerType, SourceElementType, ExtraArgType)
AFACT(Transform_EmptyRange_DoesNothing)
AFACT(Transform_OneItemRange_CallsTransformerOnce)
AFACT(Transform_TwoItemRange_CallsTransformerTwice)
EVIDENCE

using TransformerType = Utils::TwoArgStaticFunctionTransformer<
   TransformedContainerType<TransformedElementType>,
   SourceContainerType<SourceElementType>,
   TransformedElementType(*)(size_t, SourceElementType, ExtraArgType),
   ExtraArgType>;
TransformerType _oneExtraArgTransformer;

CLEANUP
{
   s_transformFunctionCalls.clear();
}

static vector<tuple<size_t, SourceElementType, ExtraArgType>> s_transformFunctionCalls;

static TransformedElementType TransformFunction(size_t index, SourceElementType sourceElement, ExtraArgType metadata)
{
   s_transformFunctionCalls.emplace_back(index, sourceElement, metadata);
   return sourceElement + 1;
};

TEST(Transform_EmptyRange_DoesNothing)
{
   const SourceContainerType<SourceElementType> sourceElements{};
   //
   const TransformedContainerType<TransformedElementType> transformedElements = _oneExtraArgTransformer.Transform(sourceElements, TransformFunction, 0);
   //
   IS_EMPTY(s_transformFunctionCalls);
   IS_EMPTY(transformedElements);
}

TEST(Transform_OneItemRange_CallsTransformerOnce)
{
   const SourceContainerType<SourceElementType> source = { 1 };
   //
   const TransformedContainerType<TransformedElementType> transformedElements = _oneExtraArgTransformer.Transform(source, TransformFunction, 10);
   //
   const vector<tuple<size_t, SourceElementType, ExtraArgType>> expectedTransformFunctionCalls =
   {
      {0, SourceElementType(1), 10}
   };
   VECTORS_ARE_EQUAL(expectedTransformFunctionCalls, s_transformFunctionCalls);

   const TransformedContainerType<TransformedElementType> expectedTransformedElements = { 2 };
   ARE_EQUAL(expectedTransformedElements, transformedElements);
}

TEST(Transform_TwoItemRange_CallsTransformerTwice)
{
   const Utils::TwoArgStaticFunctionTransformer<
      TransformedContainerType<TransformedElementType>,
      SourceContainerType<SourceElementType>,
      decltype(TransformFunction),
      ExtraArgType> oneExtraArgTransformer{};
   SourceContainerType<SourceElementType> sourceElements = { 1, 2 };
   //
   const TransformedContainerType<TransformedElementType> transformedElements = oneExtraArgTransformer.Transform(sourceElements, TransformFunction, 20);
   //
   const vector<tuple<size_t, SourceElementType, ExtraArgType>> expectedTransformFunctionCalls =
   {
      {0, SourceElementType{1}, 20},
      {1, SourceElementType{2}, 20}
   };
   VECTORS_ARE_EQUAL(expectedTransformFunctionCalls, s_transformFunctionCalls);

   const TransformedContainerType<TransformedElementType> expectedTransformedElements = { 2, 3 };
   ARE_EQUAL(expectedTransformedElements, transformedElements);
}

RUN_TEMPLATE_TESTS(TwoArgStaticFunctionTransformerTests, vector, int, vector, int, int)
THEN_RUN_TEMPLATE_TESTS(TwoArgStaticFunctionTransformerTests, vector, double, vector, int, unsigned)

template<
   template<typename...>
   class TransformedContainerType, typename TransformedElementType,
   template<typename...>
   class SourceContainerType,
   typename SourceElementType, typename ExtraArgType>
vector<tuple<size_t, SourceElementType, ExtraArgType>> TwoArgStaticFunctionTransformerTests<
   TransformedContainerType, TransformedElementType, SourceContainerType, SourceElementType, ExtraArgType>::s_transformFunctionCalls;
