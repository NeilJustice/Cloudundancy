#pragma once
class DocoptParser;

class ProgramModeSpecificArgsParser
{
   friend class ProgramModeSpecificArgsParserTests;
   friend class CopyFilesToMultipleFoldersArgsParserTests;
   friend class SevenZipArgsParserTests;
protected:
   // Constant Components
   unique_ptr<const DocoptParser> p_docoptParser;
public:
   ProgramModeSpecificArgsParser();
   virtual ~ProgramModeSpecificArgsParser();

   virtual CloudundancyArgs ParseDocoptArgs(const map<string, docopt::value>& docoptArgs) const;
};
