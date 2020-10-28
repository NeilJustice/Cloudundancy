#include "pch.h"
#include "libCloudundancy/Components/Docopt/DocoptParser.h"
#include "libCloudundancyTests/Components/Docopt/ZenUnit/docoptvalueRandom.h"

TESTS(DocoptParserTests)
AFACT(Constructor_SetsDocoptFunctionPointer)
AFACT(ParseArgs_ArgvVectorEmpty_Throws)
AFACT(ParseArgs_ArgvVectorNotEmpty_ReturnsMapResultFromCallingDocopt)
AFACT(GetRequiredString_ArgNotInMap_Throws)
AFACT(GetRequiredString_ArgInMap_ReturnsValue)
AFACT(GetRequiredBool_ArgNotInMap_Throws)
AFACT(GetRequiredBool_ArgInMap_ReturnsValue)
AFACT(GetProgramModeSpecificRequiredString_ProgramModeValueDoesNotEqualComparisonProgramModeValue_ReturnsEmptyString)
AFACT(GetProgramModeSpecificRequiredString_ProgramModeValueEqualsComparisonProgramModeValue_ArgNotInMap_Throws)
AFACT(GetProgramModeSpecificRequiredString_ProgramModeValueEqualsComparisonProgramModeValue_ArgInMap_ReturnsValue)
AFACT(GetOptionalBool_ArgNotInMap_ReturnsFalse)
AFACT(GetOptionalBool_ArgInMap_ReturnsTrue)
AFACT(GetOptionalString_ArgNotInMap_ReturnsEmptyString)
AFACT(GetOptionalString_ArgInMapWithStringValue_ReturnsValue)
EVIDENCE

DocoptParser _docoptParser;
METALMOCK_NONVOID5_FREE(map<string COMMA docopt::Value>, docopt, const string&, const vector<string>&, bool, const string&, bool)

map<string, docopt::Value> _docoptArgs;
string _argName;
string _expectedKeyNotFoundWhat;

STARTUP
{
   _docoptParser._call_docopt_docopt = BIND_5ARG_METALMOCK_OBJECT(docoptMock);

   _docoptArgs = ZenUnit::RandomMap<string, docopt::Value>();
   _argName = ZenUnit::Random<string>() + "_argName";
   _expectedKeyNotFoundWhat = "Key not found in map: [" + _argName + "]";
}

TEST(Constructor_SetsDocoptFunctionPointer)
{
   DocoptParser docoptParser;
   STD_FUNCTION_TARGETS(docopt::docopt, docoptParser._call_docopt_docopt);
}

TEST(ParseArgs_ArgvVectorEmpty_Throws)
{
   const string usage = ZenUnit::Random<string>();
   const vector<string> emptyArgv;
   //
   THROWS_EXCEPTION(const auto args = _docoptParser.ParseArgs(usage, emptyArgv), invalid_argument, "argv cannot be empty");
}

TEST(ParseArgs_ArgvVectorNotEmpty_ReturnsMapResultFromCallingDocopt)
{
   const map<string, docopt::Value> docoptReturnValue = ZenUnit::RandomMap<string, docopt::Value>();
   docoptMock.Return(docoptReturnValue);

   const string usage = ZenUnit::Random<string>();
   const vector<string> nonEmptyArgv(ZenUnit::RandomBetween<size_t>(1, 2));
   //
   const map<string, docopt::Value> docoptValues = _docoptParser.ParseArgs(usage, nonEmptyArgv);
   //
   const vector<string> expectedNonEmptyArgvWithoutFirstArgument(
      nonEmptyArgv.data() + 1, nonEmptyArgv.data() + nonEmptyArgv.size());
   METALMOCK(docoptMock.CalledOnceWith(usage, expectedNonEmptyArgvWithoutFirstArgument, true, "", false));
   ARE_EQUAL(docoptReturnValue, docoptValues);
}

TEST(GetRequiredString_ArgNotInMap_Throws)
{
   THROWS_EXCEPTION(_docoptParser.GetRequiredString(_docoptArgs, _argName),
      out_of_range, _expectedKeyNotFoundWhat);
}

TEST(GetRequiredString_ArgInMap_ReturnsValue)
{
   const string stringValue = ZenUnit::Random<string>();
   _docoptArgs[_argName] = docopt::Value(stringValue);
   //
   const string returnedStringValue = _docoptParser.GetRequiredString(_docoptArgs, _argName);
   //
   ARE_EQUAL(stringValue, returnedStringValue);
}

TEST(GetRequiredBool_ArgNotInMap_Throws)
{
   THROWS_EXCEPTION(_docoptParser.GetRequiredBool(_docoptArgs, _argName),
      out_of_range, _expectedKeyNotFoundWhat);
}

TEST(GetRequiredBool_ArgInMap_ReturnsValue)
{
   const bool boolValue = ZenUnit::Random<bool>();
   _docoptArgs[_argName] = docopt::Value(boolValue);
   //
   const bool returnedBoolValue = _docoptParser.GetRequiredBool(_docoptArgs, _argName);
   //
   ARE_EQUAL(boolValue, returnedBoolValue);
}

TEST(GetProgramModeSpecificRequiredString_ProgramModeValueDoesNotEqualComparisonProgramModeValue_ReturnsEmptyString)
{
   const unsigned modeValue = ZenUnit::Random<unsigned>();
   const unsigned fieldIsRequiredIfModeEqualsThisValue = modeValue + 1;
   //
   const string argValue = _docoptParser.GetProgramModeSpecificRequiredString(
      _docoptArgs, modeValue, fieldIsRequiredIfModeEqualsThisValue, _argName);
   //
   ARE_EQUAL(string(), argValue);
}

TEST(GetProgramModeSpecificRequiredString_ProgramModeValueEqualsComparisonProgramModeValue_ArgNotInMap_Throws)
{
   const unsigned modeValue = ZenUnit::Random<unsigned>();
   const unsigned fieldIsRequiredIfModeEqualsThisValue = modeValue;
   //
   THROWS_EXCEPTION(_docoptParser.GetProgramModeSpecificRequiredString(
      _docoptArgs, modeValue, fieldIsRequiredIfModeEqualsThisValue, _argName),
      out_of_range, _expectedKeyNotFoundWhat);
}

TEST(GetProgramModeSpecificRequiredString_ProgramModeValueEqualsComparisonProgramModeValue_ArgInMap_ReturnsValue)
{
   const unsigned modeValue = ZenUnit::Random<unsigned>();
   const unsigned fieldIsRequiredIfModeEqualsThisValue = modeValue;
   const string argValue = ZenUnit::Random<string>();
   _docoptArgs[_argName] = argValue;
   //
   const string returnedArgValue = _docoptParser.GetProgramModeSpecificRequiredString(
      _docoptArgs, modeValue, fieldIsRequiredIfModeEqualsThisValue, _argName);
   //
   ARE_EQUAL(argValue, returnedArgValue);
}

TEST(GetOptionalBool_ArgNotInMap_ReturnsFalse)
{
   const bool argValue = _docoptParser.GetOptionalBool(_docoptArgs, _argName);
   IS_FALSE(argValue);
}

TEST(GetOptionalBool_ArgInMap_ReturnsTrue)
{
   const bool argValueInMap = ZenUnit::Random<bool>();
   _docoptArgs[_argName] = docopt::Value(argValueInMap);
   //
   const bool argValue = _docoptParser.GetOptionalBool(_docoptArgs, _argName);
   //
   ARE_EQUAL(argValueInMap, argValue);
}

TEST(GetOptionalString_ArgNotInMap_ReturnsEmptyString)
{
   const string argValue = _docoptParser.GetOptionalString(_docoptArgs, _argName);
   ARE_EQUAL("", argValue);
}

TEST(GetOptionalString_ArgInMapWithStringValue_ReturnsValue)
{
   const string argValueInMap = ZenUnit::Random<string>();
   _docoptArgs[_argName] = docopt::Value(argValueInMap);
   //
   const string argValue = _docoptParser.GetOptionalString(_docoptArgs, _argName);
   //
   ARE_EQUAL(argValueInMap, argValue);
}

RUN_TESTS(DocoptParserTests)
