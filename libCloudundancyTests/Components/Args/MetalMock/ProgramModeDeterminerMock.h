#pragma once
#include "libCloudundancy/Components/Args/ProgramModeDeterminer.h"

class ProgramModeDeterminerMock : public Metal::Mock<ProgramModeDeterminer>
{
public:
   METALMOCK_NONVOID4_CONST(ProgramMode, DetermineProgramMode, bool, bool, bool, bool)
};
