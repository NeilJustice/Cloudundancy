#include "pch.h"
#include "libCloudundancy/Components/Args/CloudundancyArgsParser.h"
#include "libCloudundancy/Components/Args/ProgramModeDeterminer.h"
#include "libCloudundancy/Components/Args/ProgramModeSpecificArgsParser.h"
#include "libCloudundancy/Components/Args/ProgramModeSpecificArgsParserFactory.h"
#include "libCloudundancy/Components/Docopt/DocoptParser.h"

CloudundancyArgsParser::CloudundancyArgsParser()
   // Constant Components
   : _console(make_unique<Utils::Console>())
   , _docoptParser(make_unique<DocoptParser>())
   , _fileSystem(make_unique<Utils::FileSystem>())
   , _processRunner(make_unique<Utils::ProcessRunner>())
   , _programModeDeterminer(make_unique<ProgramModeDeterminer>())
   , _programModeSpecificArgsParserFactory(make_unique<ProgramModeSpecificArgsParserFactory>())
{
}

CloudundancyArgsParser::~CloudundancyArgsParser()
{
}

CloudundancyArgs CloudundancyArgsParser::ParseStringArgs(const vector<string>& stringArgs) const
{
   const map<string, docopt::value> docoptArgs =
      _docoptParser->ParseArgs(CloudundancyArgs::CommandLineUsage, stringArgs, false);

   const ProgramMode programMode = _programModeDeterminer->DetermineProgramMode(docoptArgs);

   const shared_ptr<const ProgramModeSpecificArgsParser> programModeSpecificArgsParser =
      _programModeSpecificArgsParserFactory->NewProgramModeSpecificArgsParser(programMode);

   CloudundancyArgs cloudundancyArgs = programModeSpecificArgsParser->ParseDocoptArgs(docoptArgs);
   return cloudundancyArgs;
}
