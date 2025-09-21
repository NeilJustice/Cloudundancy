#include "pch.h"
#include "libCloudundancy/Components/Iteration/Transform/Transformer.h"

template<typename T, typename TransformedT>
TEMPLATE_TESTS(TransformerTests, T, TransformedT)
AFACT(Transform_EmptyRange_DoesNothing)
AFACT(Transform_OneItemRange_CallsTransformerOnce)
AFACT(Transform_TwoItemRange_CallsTransformerTwice)
EVIDENCE

using TransformerType = Utils::Transformer<T, TransformedT>;
TransformerType _transformer;

static TransformedT PlusOne(const T& element)
{
   return element + 1;
}

TEST(Transform_EmptyRange_DoesNothing)
{
   const vector<T> source{};
   //
   const vector<TransformedT> dest = _transformer.Transform(source, PlusOne);
   //
   IS_EMPTY(dest);
}

TEST(Transform_OneItemRange_CallsTransformerOnce)
{
   const vector<T> source{ 1 };
   //
   const vector<TransformedT> dest = _transformer.Transform(source, PlusOne);
   //
   VECTORS_ARE_EQUAL(vector<TransformedT>{ 2 }, dest);
}

TEST(Transform_TwoItemRange_CallsTransformerTwice)
{
   const vector<T> source{ 1, 2 };
   //
   const vector<TransformedT> dest = _transformer.Transform(source, PlusOne);
   //
   VECTORS_ARE_EQUAL((vector<TransformedT>{ 2, 3 }), dest);
}

RUN_TEMPLATE_TESTS(TransformerTests, int, long long)
THEN_RUN_TEMPLATE_TESTS(TransformerTests, unsigned long long, unsigned long long)
