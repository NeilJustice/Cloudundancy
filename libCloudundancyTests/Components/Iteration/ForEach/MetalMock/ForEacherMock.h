#pragma once
#include "libCloudundancy/Components/Iteration/ForEach/ForEacher.h"

template<typename CollectionType, typename FunctionType>
class ForEacherMock : public Metal::Mock<ForEacher<CollectionType, FunctionType>>
{
public:
   METALMOCK_VOID2_CONST(ForEach, const CollectionType&, FunctionType)
};
