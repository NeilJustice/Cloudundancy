#pragma once
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgramFactory.h"

class CloudundancySubProgramFactoryMock : public Zen::Mock<CloudundancySubProgramFactory>
{
public:
   ZENMOCK_NONVOID1_CONST(shared_ptr<CloudundancySubProgram>, NewCloudundancySubProgram, ProgramMode)
};
