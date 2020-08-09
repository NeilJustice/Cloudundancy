#pragma once
#include "libCloudundancy/Components/Iteration/Transform/Transformer.h"

template<typename T, typename TransformedT>
class TransformerMock : public Zen::Mock<Transformer<T, TransformedT>>
{
public:
   using TransformerFunctionType = TransformedT(*)(const T&);
   ZENMOCK_NONVOID2_CONST(vector<TransformedT>, Transform, const vector<T>&, TransformerFunctionType)
};
