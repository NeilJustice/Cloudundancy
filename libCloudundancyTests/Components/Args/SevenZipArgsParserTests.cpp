#include "pch.h"
#include "libCloudundancy/Components/Args/SevenZipArgsParser.h"

TESTS(SevenZipArgsParserTests)
AFACT(ParseDocoptArgs_DoesSo)
EVIDENCE

SevenZipArgsParser _sevenZipArgsParser;

TEST(ParseDocoptArgs_DoesSo)
{
   const map<string, docopt::value> docoptArgs = ZenUnit::RandomNonEmptyOrderedMap<string, docopt::value>();
   //
   const CloudundancyArgs cloudundancyArgs = _sevenZipArgsParser.ParseDocoptArgs(docoptArgs);
   //

}

RUN_TESTS(SevenZipArgsParserTests)
