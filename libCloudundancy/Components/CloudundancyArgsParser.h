#pragma once
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"
class DocoptParser;
class FileSystem;
class ProgramModeDeterminer;

class CloudundancyArgsParser
{
   friend class CloudundancyArgsParserTests;
private:
   // Constant Components
   unique_ptr<const DocoptParser> _docoptParser;
   unique_ptr<const FileSystem> _fileSystem;
   unique_ptr<const ProgramModeDeterminer> _programModeDeterminer;
public:
   CloudundancyArgsParser();
   virtual ~CloudundancyArgsParser();
   virtual CloudundancyArgs ParseStringArgs(const vector<string>& stringArgs) const;
};
