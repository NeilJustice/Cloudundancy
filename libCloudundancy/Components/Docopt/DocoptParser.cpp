#include "pch.h"
#include "libCloudundancy/Components/Docopt/DocoptParser.h"
#include "libCloudundancy/Utilities/Map.h"

DocoptParser::DocoptParser()
   : _call_docopt_docopt(docopt::docopt)
{
}

DocoptParser::~DocoptParser()
{
}

map<string, docopt::Value> DocoptParser::ParseArgs(const string& commandLineUsage, const vector<string>& argv) const
{
   if (argv.empty())
   {
      throw invalid_argument("argv cannot be empty");
   }
   const vector<string> argvWithoutFirstArgument(argv.data() + 1, argv.data() + argv.size());
   const map<string, docopt::Value> argPairs =
      _call_docopt_docopt(commandLineUsage, argvWithoutFirstArgument, true, "", false);
   return argPairs;
}

string DocoptParser::GetRequiredString(const map<string, docopt::Value>& docoptArgs, const string& argName) const
{
   const docopt::Value docoptValue = Map::At(docoptArgs, argName);
   const string& stringArg = docoptValue.AsString();
   return stringArg;
}

bool DocoptParser::GetRequiredBool(const map<string, docopt::Value>& docoptArgs, const string& argName) const
{
   const docopt::Value docoptValue = Map::At(docoptArgs, argName);
   const bool boolValue = docoptValue.AsBool();
   return boolValue;
}

string DocoptParser::GetProgramModeSpecificRequiredString(
   const map<string, docopt::Value>& docoptArgs,
   int programModeAsInt,
   int fieldIsRequiredIfProgramModeIntEqualsThisValue,
   const string& argName) const
{
   if (programModeAsInt == fieldIsRequiredIfProgramModeIntEqualsThisValue)
   {
      const docopt::Value docoptValue = Map::At(docoptArgs, argName);
      const string& stringValue = docoptValue.AsString();
      return stringValue;
   }
   return string();
}

bool DocoptParser::GetOptionalBool(const map<string, docopt::Value>& docoptArgs, const string& argName) const
{
   const pair<bool, docopt::Value> didGetDocoptValueAndDocoptValue = Map::TryGetValue(docoptArgs, argName);
   if (!didGetDocoptValueAndDocoptValue.first)
   {
      return false;
   }
   const bool boolValue = didGetDocoptValueAndDocoptValue.second.AsBool();
   return boolValue;
}

string DocoptParser::GetOptionalString(const map<string, docopt::Value>& docoptArgs, const string& argName) const
{
   const pair<bool, docopt::Value> didGetDocoptValueAndDocoptValue = Map::TryGetValue(docoptArgs, argName);
   if (!didGetDocoptValueAndDocoptValue.first)
   {
      return string();
   }
   const string& optionalStringValue = didGetDocoptValueAndDocoptValue.second.AsString();
   return optionalStringValue;
}
