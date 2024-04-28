#pragma once
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgram.h"

class ExampleWindowsIniFileSubProgram : public CloudundancySubProgram
{
public:
   ~ExampleWindowsIniFileSubProgram() override = default;
   int Run(const CloudundancyArgs& args) override;
};
