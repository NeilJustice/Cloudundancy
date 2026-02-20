#pragma once
#include "libCloudundancy/Components/Args/ProgramModeSpecificArgsParser.h"

class ExampleWindowsIniFileArgsParser : public ProgramModeSpecificArgsParser
{
public:
   virtual ~ExampleWindowsIniFileArgsParser() = default;

   virtual CloudundancyArgs ParseDocoptArgs(const map<string, docopt::value>& docoptArgs) const override;
};
