#pragma once
class ProgramModeDeterminer;

class CloudundancyArgsParser
{
   friend class CloudundancyArgsParserTests;
private:
   // Constant Components
   unique_ptr<const Console> _console;
   unique_ptr<const DocoptParser> _docoptParser;
   unique_ptr<const FileSystem> _fileSystem;
   unique_ptr<const ProcessRunner> _processRunner;
   unique_ptr<const ProgramModeDeterminer> _programModeDeterminer;
public:
   CloudundancyArgsParser();
   virtual ~CloudundancyArgsParser();
   virtual CloudundancyArgs ParseStringArgs(const vector<string>& stringArgs) const;
};
