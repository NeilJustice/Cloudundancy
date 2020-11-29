#pragma once
#include "libCloudundancy/Components/Iteration/ForEach/OneExtraArgMemberFunctionForEacher.h"

template<typename T, typename MemberFunctionType, typename ClassType, typename ExtraArgType>
class OneExtraArgMemberFunctionForEacherMock : public Metal::Mock<OneExtraArgMemberFunctionForEacher<T, MemberFunctionType, ClassType, ExtraArgType>>
{
public:
   METALMOCK_VOID4_CONST(OneExtraArgMemberFunctionForEach, const vector<T>&, MemberFunctionType, const ClassType*, ExtraArgType)
};
