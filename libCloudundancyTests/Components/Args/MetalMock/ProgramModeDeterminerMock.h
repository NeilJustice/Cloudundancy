#pragma once
#include "libCloudundancy/Components/Args/ProgramModeDeterminer.h"

class ProgramModeDeterminerMock : public Metal::Mock<ProgramModeDeterminer>
{
public:
   using DocoptMapType = map<string, docopt::value>;
   METALMOCK_NONVOID1_CONST(ProgramMode, DetermineProgramMode, const DocoptMapType&)
};
