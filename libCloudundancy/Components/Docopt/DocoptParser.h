#pragma once
namespace Utils
{
   class FileSystemPather;
}

class DocoptParser
{
   friend class DocoptParserTests;
private:
   // Function Pointers
   function<size_t(const map<string, docopt::value>&, const string&)> _call_StaticGetRequiredSizeT;
   function<string(const map<string, docopt::value>&, const string&)> _call_StaticGetRequiredString;
   // Constant Components
   unique_ptr<const Utils::FileSystemPather> _fileSystemPather;
public:
   DocoptParser();
   virtual ~DocoptParser();

   virtual bool DocoptArgsAreForProgramMode(
      const map<string, docopt::value>& docoptArgs, const string& programModeString) const;

   virtual map<string, docopt::value> ParseArgs(
      const string& usage,
      const vector<string>& argv,
      bool doExitIfInvalid) const;

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
      const map<string, docopt::value>& docoptArgs,
      string_view argName,
      string_view defaultValue) const;

   virtual size_t GetRequiredSizeT(
      const map<string, docopt::value>& docoptArgs, const string& argName) const;

   virtual fs::path GetRequiredFilePathWhichMustExist(
      const map<string, docopt::value>& docoptArgs, const string& argName) const;

   virtual fs::path GetRequiredFolderPathWhichNeedNotExist(
      const map<string, docopt::value>& docoptArgs, const string& argName) const;
   private:
      static size_t StaticGetRequiredSizeT(
         const map<string, docopt::value>& docoptArgs, const string& argName);

      static string StaticGetRequiredString(
         const map<string, docopt::value>& docoptArgs, const string& argName);
};
