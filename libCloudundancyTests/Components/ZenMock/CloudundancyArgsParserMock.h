#pragma once
#include "libCloudundancy/Components/CloudundancyArgsParser.h"

class CloudundancyArgsParserMock : public Zen::Mock<CloudundancyArgsParser>
{
public:
   ZENMOCK_NONVOID1_CONST(CloudundancyArgs, ParseStringArgs, const vector<string>&)
};
