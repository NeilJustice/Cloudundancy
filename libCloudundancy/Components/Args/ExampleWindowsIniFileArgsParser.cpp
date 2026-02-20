#include "pch.h"
#include "libCloudundancy/Components/Args/ExampleWindowsIniFileArgsParser.h"

CloudundancyArgs ExampleWindowsIniFileArgsParser::ParseDocoptArgs(const map<string, docopt::value>& /*docoptArgs*/) const
{
   CloudundancyArgs cloudundancyArgs;
   cloudundancyArgs.programMode = ProgramMode::ExampleWindowsIniFile;
   return cloudundancyArgs;
}
