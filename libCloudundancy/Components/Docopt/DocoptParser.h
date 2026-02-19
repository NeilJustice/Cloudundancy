#pragma once
#include "libCloudundancy/docopt/docopt.h"

class DocoptParser
{
   friend class DocoptParserTests;
public:
   virtual ~DocoptParser() = default;

   virtual map<string, docopt::value> ParseArgs(
      const string& usage, const vector<string>& argv) const;

   virtual string GetRequiredString(
      const map<string, docopt::value>& docoptArgs, const string& argName) const;

   virtual bool GetRequiredBool(
      const map<string, docopt::value>& docoptArgs, const string& argName) const;

   virtual string GetProgramModeSpecificRequiredString(
      const map<string, docopt::value>& docoptArgs,
      unsigned modeValue,
      unsigned fieldIsRequiredIfModeEqualsThisValue,
      const string& argName) const;

   virtual bool GetOptionalBool(
      const map<string, docopt::value>& docoptArgs, const string& argName) const;

   virtual string GetOptionalString(
      const map<string, docopt::value>& docoptArgs, const string& argName) const;

   virtual string GetOptionalStringWithDefaultValue(
      const map<string, docopt::value>& docoptArgs, string_view argName, string_view defaultValue) const;
};
