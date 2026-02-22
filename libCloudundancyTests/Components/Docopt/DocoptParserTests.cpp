#include "pch.h"
#include "libCloudundancy/Components/Docopt/DocoptParser.h"
#include "libCloudundancyTests/Components/FileSystem/MetalMock/FileSystemPatherMock.h"

TESTS(DocoptParserTests)
AFACT(DefaultConstructor_SetsFieldsToDefaultValues)

AFACT(DocoptArgsAreForProgramMode_ArgInMapAsFalse_ReturnsFalse)
AFACT(DocoptArgsAreForProgramMode_ArgInMapAsTrue_ReturnsTrue)

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

AFACT(GetRequiredSizeT_DoesSo)

AFACT(GetRequiredFilePathWhichMustExist_DoesSo)
AFACT(GetRequiredFolderPathWhichNeedNotExist_DoesSo)
// Private Functions
AFACT(StaticGetRequiredSizeT_ArgNotInMap_ThrowsInvalidArgumentException)
AFACT(StaticGetRequiredSizeT_ArgInMapAsNoneValue_ThrowsInvalidArgumentException)
AFACT(StaticGetRequiredSizeT_ArgInMapAsSizeTValue_ReturnsValue)

AFACT(StaticGetRequiredString_ArgNotInMap_ThrowsInvalidArgumentException)
AFACT(StaticGetRequiredString_ArgInMapAsNoneValue_ThrowsInvalidArgumentException)
AFACT(StaticGetRequiredString_ArgInMapAsStringValue_ReturnsValue)
EVIDENCE

DocoptParser _docoptParser;
// Function Pointers
using DocoptMapType = map<string, docopt::value>;
METALMOCK_NONVOID2_STATIC_OR_FREE(size_t, _call_DocoptParser_StaticGetRequiredSizeT, const DocoptMapType&, const string&)
METALMOCK_NONVOID2_STATIC_OR_FREE(string, _call_DocoptParser_StaticGetRequiredString, const DocoptMapType&, const string&)
// Constant Components
Utils::FileSystemPatherMock* _fileSystemPatherMock = nullptr;
// Testing Fields
map<string, docopt::value> _docoptArgs;
string _argName;
string _expectedKeyNotFoundInMapExceptionMessage;

STARTUP
{
   // Function Pointers
   _docoptParser._call_StaticGetRequiredSizeT = BIND_2ARG_METALMOCK_OBJECT(_call_DocoptParser_StaticGetRequiredSizeTMock);
   _docoptParser._call_StaticGetRequiredString = BIND_2ARG_METALMOCK_OBJECT(_call_DocoptParser_StaticGetRequiredStringMock);
   // Constant Components
   _docoptParser._fileSystemPather.reset(_fileSystemPatherMock = new Utils::FileSystemPatherMock);
   // Testing Fields
   _docoptArgs = ZenUnit::RandomOrderedMap<string, docopt::value>();
   _argName = ZenUnit::Random<string>() + "_argName";
   _expectedKeyNotFoundInMapExceptionMessage = Utils::String::ConcatStrings("Error: Key not found in map: [", _argName, "]");
}

TEST(DefaultConstructor_SetsFieldsToDefaultValues)
{
   const DocoptParser docoptParser;
   // Function Pointers
   //STD_FUNCTION_TARGETS(docopt::docopt, docoptParser._call_docopt_docopt);
}

TEST(DocoptArgsAreForProgramMode_ArgInMapAsFalse_ReturnsFalse)
{
   _docoptArgs[_argName] = docopt::value(false);
   //
   const bool returnedDocoptArgsAreForProgramMode = _docoptParser.DocoptArgsAreForProgramMode(_docoptArgs, _argName);
   //
   IS_FALSE(returnedDocoptArgsAreForProgramMode);
}

TEST(DocoptArgsAreForProgramMode_ArgInMapAsTrue_ReturnsTrue)
{
   _docoptArgs[_argName] = docopt::value(true);
   //
   const bool returnedDocoptArgsAreForProgramMode = _docoptParser.DocoptArgsAreForProgramMode(_docoptArgs, _argName);
   //
   IS_TRUE(returnedDocoptArgsAreForProgramMode);
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
   const string usage = R"(
usage:
   program_name --arg1=<Value> --arg2=<Value>)";
   const vector<string> argv =
   {
      "program_name",
      "--arg1=value1",
      "--arg2=value2"
   };
   //
   const map<string, docopt::value> docoptValues = _docoptParser.ParseArgs(usage, argv, true);
   //
   const map<string, docopt::value> expectedDocoptValues
   {
      { "--arg1", docopt::value(string("value1")) },
      { "--arg2", docopt::value(string("value2")) }
   };
   MAPS_ARE_EQUAL(expectedDocoptValues, docoptValues);
}

TEST(GetRequiredString_ArgNotInMap_ThrowsOutOfRange)
{
   THROWS_EXCEPTION(const string returnValue = _docoptParser.GetRequiredString(_docoptArgs, _argName),
      invalid_argument, _expectedKeyNotFoundInMapExceptionMessage);
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
      invalid_argument, _expectedKeyNotFoundInMapExceptionMessage);
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
      invalid_argument, _expectedKeyNotFoundInMapExceptionMessage);
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

TEST(GetRequiredSizeT_DoesSo)
{
   const size_t sizeTValue = _call_DocoptParser_StaticGetRequiredSizeTMock.ReturnRandom();
   //
   const size_t returnedSizeTValue = _docoptParser.GetRequiredSizeT(_docoptArgs, _argName);
   //
   METALMOCK(_call_DocoptParser_StaticGetRequiredSizeTMock.CalledOnceWith(_docoptArgs, _argName));
   ARE_EQUAL(sizeTValue, returnedSizeTValue);
}

TEST(GetRequiredFilePathWhichMustExist_DoesSo)
{
   const string potentiallyRelativeFilePathStringArgument = _call_DocoptParser_StaticGetRequiredStringMock.ReturnRandom();
   const fs::path absoluteFilePathArgument = _fileSystemPatherMock->GetAbsoluteFileOrFolderPathMock.ReturnRandom();
   _fileSystemPatherMock->ThrowIfFileDoesNotExistMock.Expect();
   //
   const fs::path returnedFullFilePathArgument = _docoptParser.GetRequiredFilePathWhichMustExist(_docoptArgs, _argName);
   //
   const fs::path expectedPotentiallyRelativeFilePathArgument(potentiallyRelativeFilePathStringArgument);
   METALMOCKTHEN(_call_DocoptParser_StaticGetRequiredStringMock.CalledOnceWith(
      _docoptArgs, _argName)).Then(

   METALMOCKTHEN(_fileSystemPatherMock->GetAbsoluteFileOrFolderPathMock.CalledOnceWith(
      expectedPotentiallyRelativeFilePathArgument))).Then(

   METALMOCKTHEN(_fileSystemPatherMock->ThrowIfFileDoesNotExistMock.CalledOnceWith(
      absoluteFilePathArgument)));
   ARE_EQUAL(absoluteFilePathArgument, returnedFullFilePathArgument);
}

TEST(GetRequiredFolderPathWhichNeedNotExist_DoesSo)
{
   const string potentiallyRelativeFolderPathStringArgument = _call_DocoptParser_StaticGetRequiredStringMock.ReturnRandom();
   const fs::path absoluteFolderPathArgument = _fileSystemPatherMock->GetAbsoluteFileOrFolderPathMock.ReturnRandom();
   //
   const fs::path returnedAbsoluteFolderPathArgument = _docoptParser.GetRequiredFolderPathWhichNeedNotExist(_docoptArgs, _argName);
   //
   const fs::path expectedPotentiallyRelativeFolderPathArgument(potentiallyRelativeFolderPathStringArgument);
   METALMOCKTHEN(_call_DocoptParser_StaticGetRequiredStringMock.CalledOnceWith(
      _docoptArgs, _argName)).Then(

   METALMOCKTHEN(_fileSystemPatherMock->GetAbsoluteFileOrFolderPathMock.CalledOnceWith(
      expectedPotentiallyRelativeFolderPathArgument)));
   ARE_EQUAL(absoluteFolderPathArgument, returnedAbsoluteFolderPathArgument);
}

// Private Functions

TEST(StaticGetRequiredSizeT_ArgNotInMap_ThrowsInvalidArgumentException)
{
   THROWS_EXCEPTION(_docoptParser.StaticGetRequiredSizeT(_docoptArgs, _argName),
      invalid_argument, _expectedKeyNotFoundInMapExceptionMessage);
}

TEST(StaticGetRequiredSizeT_ArgInMapAsNoneValue_ThrowsInvalidArgumentException)
{
   _docoptArgs[_argName] = docopt::value();
   //
   const string expectedExceptionMessage = Utils::String::ConcatStrings(
      "Key[", _argName, "] found in map but with non-size_t value");
   THROWS_EXCEPTION(_docoptParser.StaticGetRequiredSizeT(_docoptArgs, _argName),
      invalid_argument, expectedExceptionMessage);
}

TEST(StaticGetRequiredSizeT_ArgInMapAsSizeTValue_ReturnsValue)
{
   const size_t sizeTArgumentValue = ZenUnit::Random<size_t>();
   _docoptArgs[_argName] = docopt::value(sizeTArgumentValue);
   //
   const size_t returnedSizeTArgumentValue = _docoptParser.StaticGetRequiredSizeT(_docoptArgs, _argName);
   //
   ARE_EQUAL(sizeTArgumentValue, returnedSizeTArgumentValue);
}

TEST(StaticGetRequiredString_ArgNotInMap_ThrowsInvalidArgumentException)
{
   THROWS_EXCEPTION(_docoptParser.StaticGetRequiredString(_docoptArgs, _argName),
      invalid_argument, _expectedKeyNotFoundInMapExceptionMessage);
}

TEST(StaticGetRequiredString_ArgInMapAsNoneValue_ThrowsInvalidArgumentException)
{
   _docoptArgs[_argName] = docopt::value();
   //
   const string expectedExceptionMessage = Utils::String::ConcatStrings(
      "Key[", _argName, "] found in map but with non-string value");
   THROWS_EXCEPTION(_docoptParser.StaticGetRequiredString(_docoptArgs, _argName),
      invalid_argument, expectedExceptionMessage);
}

TEST(StaticGetRequiredString_ArgInMapAsStringValue_ReturnsValue)
{
   const string stringArgumentValue = ZenUnit::Random<string>();
   _docoptArgs[_argName] = docopt::value(stringArgumentValue);
   //
   const string returnedStringArgumentValue = _docoptParser.StaticGetRequiredString(_docoptArgs, _argName);
   //
   ARE_EQUAL(stringArgumentValue, returnedStringArgumentValue);
}

RUN_TESTS(DocoptParserTests)
