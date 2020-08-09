#pragma once
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgramFactory.h"

class CloudundancySubProgramFactoryMock : public Zen::Mock<CloudundancySubProgramFactory>
{
public:
   METALMOCK_NONVOID1_CONST(shared_ptr<CloudundancySubProgram>, NewCloudundancySubProgram, ProgramMode)
};
