#pragma once
#include "libCloudundancy/Components/CloudundancyArgsParser.h"

class CloudundancyArgsParserMock : public Zen::Mock<CloudundancyArgsParser>
{
public:
   METALMOCK_NONVOID1_CONST(CloudundancyArgs, ParseStringArgs, const vector<string>&)
};
