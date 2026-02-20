#pragma once
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgram.h"

class ExampleLinuxIniFileSubProgram : public CloudundancySubProgram
{
public:
   ~ExampleLinuxIniFileSubProgram() override = default;

   int Run() override;
};
