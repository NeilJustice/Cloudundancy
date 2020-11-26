#pragma once
#include "libCloudundancy/Components/Iteration/ForEach/OneExtraArgMemberForEacher.h"

template<typename T, typename MemberFunctionType, typename ClassType, typename ExtraArgType>
class OneExtraArgMemberForEacherMock : public Metal::Mock<OneExtraArgMemberForEacher<T, MemberFunctionType, ClassType, ExtraArgType>>
{
public:
   METALMOCK_VOID4_CONST(OneExtraArgMemberForEach, const vector<T>&, MemberFunctionType, const ClassType*, ExtraArgType)
};
