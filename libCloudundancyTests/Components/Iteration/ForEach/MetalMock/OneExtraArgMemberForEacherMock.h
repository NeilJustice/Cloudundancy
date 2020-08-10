#pragma once
#include "libCloudundancy/Components/Iteration/ForEach/OneExtraArgMemberForEacher.h"

template<typename T, typename ClassType, typename MemberFunctionType, typename ExtraArgType>
class OneExtraArgMemberForEacherMock : public Metal::Mock<OneExtraArgMemberForEacher<T, ClassType, MemberFunctionType, ExtraArgType>>
{
public:
   METALMOCK_VOID4_CONST(OneExtraArgMemberForEach, const vector<T>&, const ClassType*, MemberFunctionType, ExtraArgType)
};
