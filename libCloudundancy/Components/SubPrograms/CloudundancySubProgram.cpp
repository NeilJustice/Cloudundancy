#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgram.h"

CloudundancySubProgram::CloudundancySubProgram()
   : _console(make_unique<Console>())
{
}

int CloudundancySubProgram::Run(const CloudundancyArgs& /*args*/)
{
   return 0;
}
