#pragma once
#include "libCloudundancy/Components/Args/ProgramModeSpecificArgsParser.h"
namespace Utils
{
   class Console;
   class ProcessRunner;
}

class SevenZipArgsParser : public ProgramModeSpecificArgsParser
{
   friend class SevenZipArgsParserTests;
private:
   // Constant Components
   unique_ptr<const Utils::Console> _console;
   unique_ptr<const Utils::ProcessRunner> _processRunner;
public:
   SevenZipArgsParser();
   virtual ~SevenZipArgsParser() override;

   virtual CloudundancyArgs ParseDocoptArgs(const map<string, docopt::value>& docoptArgs) const override;
};
