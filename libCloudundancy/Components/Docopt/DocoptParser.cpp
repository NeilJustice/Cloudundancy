#include "pch.h"
#include "docopt/docopt.h"
#include "libCloudundancy/Components/Docopt/DocoptParser.h"
#include "libCloudundancy/Components/Maps/MapHelper.h"
#include "libCloudundancy/StaticUtilities/Map.h"

DocoptParser::DocoptParser()
   // Function Pointers
   : _call_StaticGetRequiredSizeT(StaticGetRequiredSizeT)
   // Constant Components
   , _mapHelper(make_unique<_mapHelperType>())
{
}

DocoptParser::~DocoptParser()
{
}

bool DocoptParser::DocoptArgsAreForProgramMode(
   const map<string, docopt::value>& docoptArgs,
   const string& programModeString) const
{
   const docopt::value trueDocoptValue(true);
   bool docoptArgsAreForProgramMode = _mapHelper->ContainsKeyWithValue(&docoptArgs, programModeString, trueDocoptValue);
   return docoptArgsAreForProgramMode;
}

map<string, docopt::value> DocoptParser::ParseArgs(
   const string& usage,
   const vector<string>& argv,
   bool doExitIfInvalid) const
{
   if (argv.empty())
   {
      throw invalid_argument("argv cannot be empty");
   }
   const vector<string> argvWithoutFirstArgument(argv.data() + 1, argv.data() + argv.size());
   map<string, docopt::value> argPairs = docopt::docopt(
      usage,
      argvWithoutFirstArgument,
      true,
      "",
      false,
      doExitIfInvalid);
   return argPairs;
}

string DocoptParser::GetRequiredString(
   const map<string, docopt::value>& docoptArgs,
   const string& argName) const
{
   const docopt::value docoptValue = Map::At(docoptArgs, argName);
   const string& stringArg = docoptValue.asString();
   return stringArg;
}

bool DocoptParser::GetRequiredBool(
   const map<string, docopt::value>& docoptArgs,
   const string& argName) const
{
   const docopt::value docoptValue = Map::At(docoptArgs, argName);
   bool boolValue = docoptValue.asBool();
   return boolValue;
}

string DocoptParser::GetProgramModeSpecificRequiredString(
   const map<string, docopt::value>& docoptArgs,
   unsigned modeValue,
   unsigned fieldIsRequiredIfModeEqualsThisValue,
   const string& argName) const
{
   if (modeValue == fieldIsRequiredIfModeEqualsThisValue)
   {
      const docopt::value docoptValue = Map::At(docoptArgs, argName);
      const string& stringValue = docoptValue.asString();
      return stringValue;
   }
   return string();
}

bool DocoptParser::GetOptionalBool(
   const map<string, docopt::value>& docoptArgs,
   const string& argName) const
{
   docopt::value docoptValue;
   if (Map::TryGetValue(docoptArgs, argName, docoptValue))
   {
      bool boolValue = docoptValue.asBool();
      return boolValue;
   }
   return false;
}

string DocoptParser::GetOptionalString(
   const map<string, docopt::value>& docoptArgs,
   const string& argName) const
{
   docopt::value docoptValue;
   if (Map::TryGetValue(docoptArgs, argName, docoptValue))
   {
      const string& stringValue = docoptValue.asString();
      return stringValue;
   }
   return string();
}

string DocoptParser::GetOptionalStringWithDefaultValue(
   const map<string, docopt::value>& docoptArgs,
   string_view argName,
   string_view defaultValue) const
{
   docopt::value docoptValue;
   if (Map::TryGetValue(docoptArgs, string(argName), docoptValue))
   {
      if (docoptValue.isString())
      {
         const string& stringValue = docoptValue.asString();
         return stringValue;
      }
   }
   return string(defaultValue);
}

size_t DocoptParser::GetRequiredSizeT(
   const map<string, docopt::value>& docoptArgs,
   const string& argName) const
{
   size_t sizeTValue = _call_StaticGetRequiredSizeT(docoptArgs, argName);
   return sizeTValue;
}

// Private Functions

size_t DocoptParser::StaticGetRequiredSizeT(
   const map<string, docopt::value>& docoptArgs,
   const string& argName)
{
   const docopt::value& docoptValue = Map::At(docoptArgs, argName);
   size_t sizeTValue = docoptValue.asSizeT();
   return sizeTValue;
}
