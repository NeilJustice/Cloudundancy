#pragma once
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"
class DocoptParser;
class FileSystem;

class CloudundancyArgsParser
{
   friend class CloudundancyArgsParserTests;
private:
   // Components
   unique_ptr<const DocoptParser> _docoptParser;
   unique_ptr<const FileSystem> _fileSystem;
   // Function Callers
   function<ProgramMode(bool, bool)> _call_GetProgramMode;
public:
   CloudundancyArgsParser();
   virtual ~CloudundancyArgsParser();
   virtual CloudundancyArgs ParseStringArgs(const vector<string>& stringArgs) const;
private:
   static ProgramMode GetProgramMode(bool isBackupFilesAndFoldersMode, bool is7ZipBackupMode);
};
