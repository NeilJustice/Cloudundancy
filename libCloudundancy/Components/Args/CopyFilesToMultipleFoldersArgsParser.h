#pragma once
#include "libCloudundancy/Components/Args/ProgramModeSpecificArgsParser.h"

class CopyFilesToMultipleFoldersArgsParser : public ProgramModeSpecificArgsParser
{
public:
   virtual ~CopyFilesToMultipleFoldersArgsParser() = default;

   virtual CloudundancyArgs ParseDocoptArgs(const map<string, docopt::value>& docoptArgs) const override;
};
