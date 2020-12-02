#pragma once
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgram.h"

class PrintExampleLinuxIniFileSubProgram : public CloudundancySubProgram
{
public:
   int Run(const CloudundancyArgs& args) override;
   ~PrintExampleLinuxIniFileSubProgram() = default;
};
