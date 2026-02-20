#pragma once
class CloudundancyArgsParserTests;
class DocoptParser;
class ProgramModeDeterminer;
class ProgramModeSpecificArgsParserFactory;

class CloudundancyArgsParser
{
   friend class ::CloudundancyArgsParserTests;
private:
   // Constant Components
   unique_ptr<const Utils::Console> _console;
   unique_ptr<const DocoptParser> _docoptParser;
   unique_ptr<const Utils::FileSystem> _fileSystem;
   unique_ptr<const Utils::ProcessRunner> _processRunner;
   unique_ptr<const ProgramModeDeterminer> _programModeDeterminer;
   unique_ptr<const ProgramModeSpecificArgsParserFactory> _programModeSpecificArgsParserFactory;
public:
   CloudundancyArgsParser();
   virtual ~CloudundancyArgsParser();

   virtual CloudundancyArgs ParseStringArgs(const vector<string>& stringArgs) const;
};
