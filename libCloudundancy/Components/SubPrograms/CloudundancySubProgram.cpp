#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgram.h"

CloudundancySubProgram::CloudundancySubProgram()
   // Constant Components
   : _console(make_unique<Utils::Console>())
{
}

CloudundancySubProgram::~CloudundancySubProgram()
{
}

int CloudundancySubProgram::Run(const CloudundancyArgs& /*args*/)
{
   return 0;
}
