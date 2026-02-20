#pragma once
#include "libCloudundancy/docopt/docopt.h"
namespace Utils
{
   template<typename KeyType, typename ValueType>
   class MapHelper;
}

class DocoptParser
{
   friend class DocoptParserTests;
private:
   // Function Pointers
   function<size_t(const map<string, docopt::value>&, const string&)> _call_StaticGetRequiredSizeT;
   // Constant Components
   using _mapHelperType = Utils::MapHelper<string, docopt::value>;
   unique_ptr<const _mapHelperType> _mapHelper;
public:
   DocoptParser();
   virtual ~DocoptParser();

   virtual bool DocoptArgsAreForProgramMode(
      const map<string, docopt::value>& docoptArgs,
      const string& programModeString) const;

   virtual map<string, docopt::value> ParseArgs(
      const string& usage,
      const vector<string>& argv,
      bool doExitIfInvalid) const;

   virtual string GetRequiredString(
      const map<string, docopt::value>& docoptArgs,
      const string& argName) const;

   virtual bool GetRequiredBool(
      const map<string, docopt::value>& docoptArgs,
      const string& argName) const;

   virtual string GetProgramModeSpecificRequiredString(
      const map<string, docopt::value>& docoptArgs,
      unsigned modeValue,
      unsigned fieldIsRequiredIfModeEqualsThisValue,
      const string& argName) const;

   virtual bool GetOptionalBool(
      const map<string, docopt::value>& docoptArgs,
      const string& argName) const;

   virtual string GetOptionalString(
      const map<string, docopt::value>& docoptArgs,
      const string& argName) const;

   virtual string GetOptionalStringWithDefaultValue(
      const map<string, docopt::value>& docoptArgs,
      string_view argName,
      string_view defaultValue) const;

   virtual size_t GetRequiredSizeT(
      const map<string, docopt::value>& docoptArgs,
      const string& argName) const;
   private:
      static size_t StaticGetRequiredSizeT(
         const map<string, docopt::value>& docoptArgs,
         const string& argName);
};
