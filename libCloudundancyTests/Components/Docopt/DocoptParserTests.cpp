#include "pch.h"
#include "libCloudundancy/Components/Docopt/DocoptParser.h"
#include "libCloudundancyTests/Components/Maps/MetalMock/MapHelperMock.h"

TESTS(DocoptParserTests)
AFACT(DefaultConstructor_SetsFieldsToDefaultValues)
AFACT(DocoptArgsAreForProgramMode_ReturnsTrueIfSo)

AFACT(ParseArgs_ArgvVectorEmpty_ThrowsInvalidArgument)
AFACT(ParseArgs_ArgvVectorNotEmpty_ReturnsMapResultFromCallingDocopt)

AFACT(GetRequiredString_ArgNotInMap_ThrowsOutOfRange)
AFACT(GetRequiredString_ArgInMap_ReturnsValue)

AFACT(GetRequiredBool_ArgNotInMap_ThrowsOutOfRange)
AFACT(GetRequiredBool_ArgInMap_ReturnsValue)

AFACT(GetProgramModeSpecificRequiredString_ProgramModeValueDoesNotEqualComparisonProgramModeValue_ReturnsEmptyString)
AFACT(GetProgramModeSpecificRequiredString_ProgramModeValueEqualsComparisonProgramModeValue_ArgNotInMap_ThrowsOutOfRange)
AFACT(GetProgramModeSpecificRequiredString_ProgramModeValueEqualsComparisonProgramModeValue_ArgInMap_ReturnsValue)

AFACT(GetOptionalBool_ArgNotInMap_ReturnsFalse)
AFACT(GetOptionalBool_ArgInMap_ReturnsTrue)

AFACT(GetOptionalString_ArgNotInMap_ReturnsEmptyString)
AFACT(GetOptionalString_ArgInMap_ReturnsValue)
AFACT(GetOptionalStringWithDefaultValue_ArgNotInMap_ReturnsDefaultValue)
AFACT(GetOptionalStringWithDefaultValue_ArgInMap_ReturnsValue)
EVIDENCE

DocoptParser _docoptParser;
// Function Pointers
//METALMOCK_NONVOID5_STATIC_OR_FREE(map<string COMMA docopt::value>, docopt, const string&, const vector<string>&, bool, const string&, bool)
// Constant Components
using _mapHelperMockType = Utils::MapHelperMock<string, docopt::value>;
_mapHelperMockType* _mapHelperMock = nullptr;
// Testing Fields
map<string, docopt::value> _docoptArgs;
string _argName;
string _expectedKeyNotFoundWhat;

STARTUP
{
   // Function Pointers
   //_docoptParser._call_docopt_docopt = BIND_5ARG_METALMOCK_OBJECT(docoptMock);
   // Constant Components
   _docoptParser._mapHelper.reset(_mapHelperMock = new _mapHelperMockType);
   // Testing Fields
   _docoptArgs = ZenUnit::RandomOrderedMap<string, docopt::value>();
   _argName = ZenUnit::Random<string>() + "_argName";
   _expectedKeyNotFoundWhat = "Error: Key not found in map: [" + _argName + "]";
}

TEST(DefaultConstructor_SetsFieldsToDefaultValues)
{
   const DocoptParser docoptParser;
   // Function Pointers
   //STD_FUNCTION_TARGETS(docopt::docopt, docoptParser._call_docopt_docopt);
}

TEST(DocoptArgsAreForProgramMode_ReturnsTrueIfSo)
{
   const bool docoptArgsAreForProgramMode = _mapHelperMock->ContainsKeyWithValueMock.ReturnRandom();
   const map<string, docopt::value> docoptArgs = ZenUnit::RandomOrderedMap<string, docopt::value>();
   const string programModeString = ZenUnit::Random<string>();
   //
   const bool returnedDocoptArgsAreForProgramMode = _docoptParser.DocoptArgsAreForProgramMode(docoptArgs, programModeString);
   //
   const docopt::value trueDocoptValue(true);
   METALMOCK(_mapHelperMock->ContainsKeyWithValueMock.CalledOnceWith(
      &docoptArgs, programModeString, trueDocoptValue));
   ARE_EQUAL(docoptArgsAreForProgramMode, returnedDocoptArgsAreForProgramMode);
}

TEST(ParseArgs_ArgvVectorEmpty_ThrowsInvalidArgument)
{
   const string usage = ZenUnit::Random<string>();
   const vector<string> emptyArgv;
   //
   THROWS_EXCEPTION(const auto returnValue = _docoptParser.ParseArgs(
      usage, emptyArgv, false),
      invalid_argument, "argv cannot be empty");
}

TEST(ParseArgs_ArgvVectorNotEmpty_ReturnsMapResultFromCallingDocopt)
{
   //const map<string, docopt::value> docoptReturnValue = ZenUnit::RandomOrderedMap<string, docopt::value>();
   //docoptMock.Return(docoptReturnValue);

   //const string usage = ZenUnit::Random<string>();
   //const vector<string> nonEmptyArgv(ZenUnit::RandomBetween<size_t>(1, 2));
   ////
   //const map<string, docopt::value> docoptValues = _docoptParser.ParseArgs(usage, nonEmptyArgv);
   ////
   //const vector<string> expectedNonEmptyArgvWithoutFirstArgument(
   //   nonEmptyArgv.data() + 1, nonEmptyArgv.data() + nonEmptyArgv.size());
   //METALMOCK(docoptMock.CalledOnceWith(usage, expectedNonEmptyArgvWithoutFirstArgument, true, "", false));
   //ARE_EQUAL(docoptReturnValue, docoptValues);
}

TEST(GetRequiredString_ArgNotInMap_ThrowsOutOfRange)
{
   THROWS_EXCEPTION(const string returnValue = _docoptParser.GetRequiredString(_docoptArgs, _argName),
      out_of_range, _expectedKeyNotFoundWhat);
}

TEST(GetRequiredString_ArgInMap_ReturnsValue)
{
   const string stringValue = ZenUnit::Random<string>();
   _docoptArgs[_argName] = docopt::value(stringValue);
   //
   const string returnedStringValue = _docoptParser.GetRequiredString(_docoptArgs, _argName);
   //
   ARE_EQUAL(stringValue, returnedStringValue);
}

TEST(GetRequiredBool_ArgNotInMap_ThrowsOutOfRange)
{
   THROWS_EXCEPTION(_docoptParser.GetRequiredBool(_docoptArgs, _argName),
      out_of_range, _expectedKeyNotFoundWhat);
}

TEST(GetRequiredBool_ArgInMap_ReturnsValue)
{
   const bool boolValue = ZenUnit::Random<bool>();
   _docoptArgs[_argName] = docopt::value(boolValue);
   //
   const bool returnedBoolValue = _docoptParser.GetRequiredBool(_docoptArgs, _argName);
   //
   ARE_EQUAL(boolValue, returnedBoolValue);
}

TEST(GetProgramModeSpecificRequiredString_ProgramModeValueDoesNotEqualComparisonProgramModeValue_ReturnsEmptyString)
{
   const unsigned programModeValue = ZenUnit::Random<unsigned>();
   const unsigned fieldIsRequiredIfModeEqualsThisValue = programModeValue + 1;
   //
   const string argValue = _docoptParser.GetProgramModeSpecificRequiredString(
      _docoptArgs, programModeValue, fieldIsRequiredIfModeEqualsThisValue, _argName);
   //
   ARE_EQUAL(string(), argValue);
}

TEST(GetProgramModeSpecificRequiredString_ProgramModeValueEqualsComparisonProgramModeValue_ArgNotInMap_ThrowsOutOfRange)
{
   const unsigned programModeValue = ZenUnit::Random<unsigned>();
   const unsigned fieldIsRequiredIfProgramModeEqualsThisValue = programModeValue;
   //
   THROWS_EXCEPTION(const string returnValue = _docoptParser.GetProgramModeSpecificRequiredString(
      _docoptArgs, programModeValue, fieldIsRequiredIfProgramModeEqualsThisValue, _argName),
      out_of_range, _expectedKeyNotFoundWhat);
}

TEST(GetProgramModeSpecificRequiredString_ProgramModeValueEqualsComparisonProgramModeValue_ArgInMap_ReturnsValue)
{
   const unsigned programModeValue = ZenUnit::Random<unsigned>();
   const unsigned fieldIsRequiredIfProgramModeEqualsThisValue = programModeValue;
   const string argValue = ZenUnit::Random<string>();
   _docoptArgs[_argName] = argValue;
   //
   const string returnedArgValue = _docoptParser.GetProgramModeSpecificRequiredString(
      _docoptArgs, programModeValue, fieldIsRequiredIfProgramModeEqualsThisValue, _argName);
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
   _docoptArgs[_argName] = docopt::value(argValueInMap);
   //
   const bool argValue = _docoptParser.GetOptionalBool(_docoptArgs, _argName);
   //
   ARE_EQUAL(argValueInMap, argValue);
}

TEST(GetOptionalString_ArgNotInMap_ReturnsEmptyString)
{
   const string argValue = _docoptParser.GetOptionalString(_docoptArgs, _argName);
   IS_EMPTY_STRING(argValue);
}

TEST(GetOptionalString_ArgInMap_ReturnsValue)
{
   const string argValueInMap = ZenUnit::Random<string>();
   _docoptArgs[_argName] = docopt::value(argValueInMap);
   //
   const string argValue = _docoptParser.GetOptionalString(_docoptArgs, _argName);
   //
   ARE_EQUAL(argValueInMap, argValue);
}

TEST(GetOptionalStringWithDefaultValue_ArgNotInMap_ReturnsDefaultValue)
{
   const string defaultValue = ZenUnit::Random<string>();
   //
   const string argValue = _docoptParser.GetOptionalStringWithDefaultValue(_docoptArgs, _argName, defaultValue);
   //
   ARE_EQUAL(defaultValue, argValue);
}

TEST(GetOptionalStringWithDefaultValue_ArgInMap_ReturnsValue)
{
   const string defaultValue = ZenUnit::Random<string>();
   const string argValueInMap = ZenUnit::Random<string>();
   _docoptArgs[_argName] = docopt::value(argValueInMap);
   //
   const string argValue = _docoptParser.GetOptionalStringWithDefaultValue(_docoptArgs, _argName, defaultValue);
   //
   ARE_EQUAL(argValueInMap, argValue);
}

RUN_TESTS(DocoptParserTests)
