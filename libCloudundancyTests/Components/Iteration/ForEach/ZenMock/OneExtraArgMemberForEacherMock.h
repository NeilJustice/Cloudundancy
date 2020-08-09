#pragma once
#include "libCloudundancy/Components/Iteration/ForEach/OneExtraArgMemberForEacher.h"

template<typename T, typename ClassType, typename MemberFunctionType, typename ExtraArgType>
class OneExtraArgMemberForEacherMock : public Zen::Mock<OneExtraArgMemberForEacher<T, ClassType, MemberFunctionType, ExtraArgType>>
{
public:
   ZENMOCK_VOID4_CONST(OneExtraArgMemberForEach, const vector<T>&, const ClassType*, MemberFunctionType, ExtraArgType)
};
