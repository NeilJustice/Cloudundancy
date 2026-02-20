#include "pch.h"
#include "libCloudundancy/Components/Args/ExampleLinuxIniFileArgsParser.h"

CloudundancyArgs ExampleLinuxIniFileArgsParser::ParseDocoptArgs(const map<string, docopt::value>& /*docoptArgs*/) const
{
   CloudundancyArgs cloudundancyArgs;
   cloudundancyArgs.programMode = ProgramMode::ExampleLinuxIniFile;
   return cloudundancyArgs;
}
