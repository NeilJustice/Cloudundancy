#pragma once
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgram.h"

class ExampleWindowsIniFileSubProgram : public CloudundancySubProgram
{
public:
   int Run(const CloudundancyArgs& args) override;
   ~ExampleWindowsIniFileSubProgram() = default;
};
