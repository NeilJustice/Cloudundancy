#pragma once
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgramFactory.h"

class CloudundancySubProgramFactoryMock : public Metal::Mock<CloudundancySubProgramFactory>
{
public:
   METALMOCK_NONVOID1_CONST(shared_ptr<CloudundancySubProgram>, NewCloudundancySubProgram, ProgramMode)
};
