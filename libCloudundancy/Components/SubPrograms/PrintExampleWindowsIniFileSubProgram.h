#pragma once
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgram.h"

class PrintExampleWindowsIniFileSubProgram : public CloudundancySubProgram
{
public:
   int Run(const CloudundancyArgs& args) override;
   ~PrintExampleWindowsIniFileSubProgram() = default;
};
