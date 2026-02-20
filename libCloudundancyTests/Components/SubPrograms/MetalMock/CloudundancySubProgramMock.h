#pragma once
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgram.h"

class CloudundancySubProgramMock : public Metal::Mock<CloudundancySubProgram>
{
public:
   METALMOCK_VOID1(Initialize, const CloudundancyArgs&)
   METALMOCK_NONVOID0(int, Run)
};
