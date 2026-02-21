#pragma once
#include "libCloudundancy/Components/Args/ProgramModeSpecificArgsParser.h"

class ExampleLinuxIniFileArgsParser : public ProgramModeSpecificArgsParser
{
public:
   virtual ~ExampleLinuxIniFileArgsParser() override = default;

   virtual CloudundancyArgs ParseDocoptArgs(const map<string, docopt::value>& docoptArgs) const override;
};
