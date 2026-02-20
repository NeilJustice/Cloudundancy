#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/CloudundancySubProgram.h"

CloudundancySubProgram::CloudundancySubProgram()
   // Constant Components
   : p_console(make_unique<Utils::Console>())
{
}

CloudundancySubProgram::~CloudundancySubProgram()
{
}

void CloudundancySubProgram::Initialize(const CloudundancyArgs& args)
{
   p_args = args;
}

int CloudundancySubProgram::Run()
{
   return 0;
}
