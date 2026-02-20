#pragma once
#include "libCloudundancy/Components/Args/ProgramModeSpecificArgsParserFactory.h"

class ProgramModeSpecificArgsParserFactoryMock : public Metal::Mock<ProgramModeSpecificArgsParserFactory>
{
public:
   METALMOCK_NONVOID1_CONST(shared_ptr<const ProgramModeSpecificArgsParser>, NewProgramModeSpecificArgsParser,
      ProgramMode)
};
