#pragma once
#include "libCloudundancy/UtilityComponents/Docopt/docopt.h"
namespace docopt
{
   struct value;
}
class DocoptParserTests;

class DocoptParser
{
   friend class DocoptParserTests;
private:
   function<map<string, docopt::Value>(string, const vector<string>&, bool help, string, bool)> _call_docopt_docopt;
public:
   DocoptParser();
   virtual ~DocoptParser();
   virtual map<string, docopt::Value> ParseArgs(const string& commandLineUsage, const vector<string>& argv) const;
   virtual string GetRequiredString(const map<string, docopt::Value>& docoptArgs, const string& argName) const;
   virtual bool GetRequiredBool(const map<string, docopt::Value>& docoptArgs, const string& argName) const;
   virtual string GetProgramModeSpecificRequiredString(
      const map<string, docopt::Value>& docoptArgs,
      int programModeAsInt,
      int fieldIsRequiredIfProgramModeIntEqualsThisValue,
      const string& argName) const;
   virtual bool GetOptionalBool(const map<string, docopt::Value>& docoptArgs, const string& argName) const;
   virtual string GetOptionalString(const map<string, docopt::Value>& docoptArgs, const string& argName) const;
};
