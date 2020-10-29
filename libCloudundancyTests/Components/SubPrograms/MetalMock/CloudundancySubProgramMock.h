#pragma once
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgram.h"

class CloudundancySubProgramMock : public Metal::Mock<CloudundancySubProgram>
{
public:
   METALMOCK_NONVOID1(int, Run, const CloudundancyArgs&)
};
