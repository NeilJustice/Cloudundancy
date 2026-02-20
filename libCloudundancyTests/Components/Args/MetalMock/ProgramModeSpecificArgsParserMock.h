#pragma once
#include "libCloudundancy/Components/Args/ProgramModeSpecificArgsParser.h"

class ProgramModeSpecificArgsParserMock : public Metal::Mock<ProgramModeSpecificArgsParser>
{
public:
   using DocoptArgsMapType = map<string, docopt::value>;
   METALMOCK_NONVOID1_CONST(CloudundancyArgs, ParseDocoptArgs, const DocoptArgsMapType&)
};
