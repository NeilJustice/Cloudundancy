#pragma once
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgram.h"

class ExampleLinuxIniFileSubProgram : public CloudundancySubProgram
{
public:
   int Run(const CloudundancyArgs& args) override;
   ~ExampleLinuxIniFileSubProgram() override = default;
};
