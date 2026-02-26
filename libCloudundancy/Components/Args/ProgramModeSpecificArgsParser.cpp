#include "pch.h"
#include "libCloudundancy/Components/Args/ProgramModeSpecificArgsParser.h"
#include "libCloudundancy/Components/Docopt/DocoptParser.h"

ProgramModeSpecificArgsParser::ProgramModeSpecificArgsParser()
   // Constant Components
   : p_docoptParser(make_unique<DocoptParser>())
{
}

ProgramModeSpecificArgsParser::~ProgramModeSpecificArgsParser()
{
}

CloudundancyArgs ProgramModeSpecificArgsParser::ParseDocoptArgs(const map<string, docopt::value>& /*docoptArgs*/) const
{
   throw logic_error("Unimplemented call to ProgramModeSpecificArgsParser::ParseDocoptArgs");
}
