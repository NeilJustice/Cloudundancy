#include "pch.h"
#include "libCloudundancy/Components/Args/ProgramModeSpecificArgsParser.h"

TESTS(ProgramModeSpecificArgsParserTests)
AFACT(DefaultConstructor_NewsDocoptParser)
AFACT(ParseDocoptArgs_ThrowsLogicError)
EVIDENCE

ProgramModeSpecificArgsParser _programModeSpecificArgsParser;

TEST(DefaultConstructor_NewsDocoptParser)
{
   ProgramModeSpecificArgsParser programModeSpecificArgsParser;
   // Constant Components
   DELETE_TO_ASSERT_NEWED(programModeSpecificArgsParser.p_docoptParser);
}

TEST(ParseDocoptArgs_ThrowsLogicError)
{
   const map<string, docopt::value> docoptArgs = ZenUnit::RandomNonEmptyOrderedMap<string, docopt::value>();
   THROWS_EXCEPTION(_programModeSpecificArgsParser.ParseDocoptArgs(docoptArgs),
      logic_error, "Unimplemented call to ProgramModeSpecificArgsParser::ParseDocoptArgs");
}

RUN_TESTS(ProgramModeSpecificArgsParserTests)
