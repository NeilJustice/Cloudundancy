#include "pch.h"
#include "libCloudundancy/Components/Args/ExampleLinuxIniFileArgsParser.h"

TESTS(ExampleLinuxIniFileArgsParserTests)
AFACT(ParseDocoptArgs_DoesSo)
EVIDENCE

ExampleLinuxIniFileArgsParser _exampleLinuxIniFileArgsParser;

TEST(ParseDocoptArgs_DoesSo)
{
   const map<string, docopt::value> docoptArgs = ZenUnit::RandomNonEmptyOrderedMap<string, docopt::value>();
   //
   const CloudundancyArgs cloudundancyArgs = _exampleLinuxIniFileArgsParser.ParseDocoptArgs(docoptArgs);
   //
   CloudundancyArgs expectedCloudundancyArgs;
   expectedCloudundancyArgs.programMode = ProgramMode::ExampleLinuxIniFile;
   ARE_EQUAL(expectedCloudundancyArgs, cloudundancyArgs);
}

RUN_TESTS(ExampleLinuxIniFileArgsParserTests)
