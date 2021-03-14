#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgram.h"

CloudundancySubProgram::CloudundancySubProgram()
   // Constant Components
   : _console(make_unique<Console>())
{
}

CloudundancySubProgram::~CloudundancySubProgram()
{
}

int CloudundancySubProgram::Run(const CloudundancyArgs& /*args*/)
{
   return 0;
}
