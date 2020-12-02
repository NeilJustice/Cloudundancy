#include "pch.h"
#ifdef __linux__
#include "libCloudundancy/Components/Process/Linux/LinuxProcessRunner.h"

LinuxProcessRunner::~LinuxProcessRunner()
{
}

ProcessResult LinuxProcessRunner::Run(string_view processName, string_view arguments) const
{
   return ProcessResult();
}

ProcessResult LinuxProcessRunner::FailFastRun(string_view processName, string_view arguments) const
{
   return ProcessResult();
}

#else
namespace { char symbolToQuietMSBuildLinkerWarning4221ForDoesNotDefineAPublicSymbol; }
#endif
