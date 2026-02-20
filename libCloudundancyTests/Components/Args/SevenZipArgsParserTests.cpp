#include "pch.h"
#include "libCloudundancy/Components/Args/SevenZipArgsParser.h"

TESTS(SevenZipArgsParserTests)
AFACT(ParseDocoptArgs_DoesSo)
EVIDENCE

SevenZipArgsParser _sevenZipArgsParser;
// Base Constant Components
DocoptParserMock* p_docoptParserMock = nullptr;

STARTUP
{
   // Base Constant Components
   _sevenZipArgsParser.p_docoptParser.reset(p_docoptParserMock = new DocoptParserMock);
}

TEST(ParseDocoptArgs_DoesSo)
{
   const fs::path iniInputFilePath =
      p_docoptParserMock->GetRequiredFilePathWhichMustExistMock.ReturnRandom();

   const map<string, docopt::value> docoptArgs = ZenUnit::RandomNonEmptyOrderedMap<string, docopt::value>();
   //
   const CloudundancyArgs cloudundancyArgs = _sevenZipArgsParser.ParseDocoptArgs(docoptArgs);
   //
   METALMOCK(p_docoptParserMock->GetRequiredFilePathWhichMustExistMock.CalledOnceWith(
      docoptArgs, "--ini-file-to-copy-files-to-7zip-staging-folder"));

   CloudundancyArgs expectedCloudundancyArgs;
   expectedCloudundancyArgs.iniInputFilePath = iniInputFilePath;
   ARE_EQUAL(expectedCloudundancyArgs, cloudundancyArgs);
}

RUN_TESTS(SevenZipArgsParserTests)
