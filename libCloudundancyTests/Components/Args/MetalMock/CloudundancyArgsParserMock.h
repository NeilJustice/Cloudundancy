#pragma once
#include "libCloudundancy/Components/Args/CloudundancyArgsParser.h"

class CloudundancyArgsParserMock : public Metal::Mock<CloudundancyArgsParser>
{
public:
   METALMOCK_NONVOID1_CONST(CloudundancyArgs, ParseStringArgs, const vector<string>&)
};
