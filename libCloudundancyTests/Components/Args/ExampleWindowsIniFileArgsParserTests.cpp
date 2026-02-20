#include "pch.h"
#include "libCloudundancy/Components/Args/ExampleWindowsIniFileArgsParser.h"

TESTS(ExampleWindowsIniFileArgsParserTests)
AFACT(ParseDocoptArgs_DoesSo)
EVIDENCE

ExampleWindowsIniFileArgsParser _exampleWindowsIniFileArgsParser;

TEST(ParseDocoptArgs_DoesSo)
{
   const map<string, docopt::value> docoptArgs = ZenUnit::RandomNonEmptyOrderedMap<string, docopt::value>();
   //
   const CloudundancyArgs cloudundancyArgs = _exampleWindowsIniFileArgsParser.ParseDocoptArgs(docoptArgs);
   //
   CloudundancyArgs expectedCloudundancyArgs;
   expectedCloudundancyArgs.programMode = ProgramMode::ExampleWindowsIniFile;
   ARE_EQUAL(expectedCloudundancyArgs, cloudundancyArgs);
}

RUN_TESTS(ExampleWindowsIniFileArgsParserTests)
