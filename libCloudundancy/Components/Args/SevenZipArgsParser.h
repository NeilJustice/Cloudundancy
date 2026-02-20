#pragma once
#include "libCloudundancy/Components/Args/ProgramModeSpecificArgsParser.h"

class SevenZipArgsParser : public ProgramModeSpecificArgsParser
{
   friend class SevenZipArgsParserTests;
public:
   SevenZipArgsParser();
   virtual ~SevenZipArgsParser();

   virtual CloudundancyArgs ParseDocoptArgs(const map<string, docopt::value>& docoptArgs) const override;
};
