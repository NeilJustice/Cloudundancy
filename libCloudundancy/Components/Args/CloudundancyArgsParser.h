#pragma once
namespace Utils
{
   class DocoptParser;
}
class CloudundancyArgsParserTests;
class ProgramModeDeterminer;

class CloudundancyArgsParser
{
   friend class ::CloudundancyArgsParserTests;
private:
   // Constant Components
   unique_ptr<const Time::Console> _console;
   unique_ptr<const Time::DocoptParser> _docoptParser;
   unique_ptr<const Utils::FileSystem> _fileSystem;
   unique_ptr<const Utils::ProcessRunner> _processRunner;
   unique_ptr<const ProgramModeDeterminer> _programModeDeterminer;
public:
   CloudundancyArgsParser();
   virtual ~CloudundancyArgsParser();
   virtual CloudundancyArgs ParseStringArgs(const vector<string>& stringArgs) const;
};
