#pragma once
#include "libCloudundancy/Components/Iteration/ForEach/ForEacher.h"

template<typename CollectionType, typename FunctionType>
class ForEacherMock : public Zen::Mock<ForEacher<CollectionType, FunctionType>>
{
public:
   ZENMOCK_VOID2_CONST(ForEach, const CollectionType&, FunctionType)
};
