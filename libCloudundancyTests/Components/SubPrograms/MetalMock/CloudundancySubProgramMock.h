#pragma once
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgram.h"

class CloudundancySubProgramMock : public Zen::Mock<CloudundancySubProgram>
{
public:
   METALMOCK_VOID1(Run, const CloudundancyArgs&)
};
