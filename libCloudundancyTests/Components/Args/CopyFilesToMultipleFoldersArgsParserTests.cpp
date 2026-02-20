#include "pch.h"
#include "libCloudundancy/Components/Args/CopyFilesToMultipleFoldersArgsParser.h"
#include "libCloudundancyTests/Components/Docopt/MetalMock/DocoptParserMock.h"

TESTS(CopyFilesToMultipleFoldersArgsParserTests)
AFACT(ParseDocoptArgs_DoesSo)
EVIDENCE

CopyFilesToMultipleFoldersArgsParser _copyFilesToMultipleFoldersArgsParser;
// Base Constant Components
DocoptParserMock* p_docoptParserMock = nullptr;

STARTUP
{
   _copyFilesToMultipleFoldersArgsParser.p_docoptParser.reset(p_docoptParserMock = new DocoptParserMock);
}

TEST(ParseDocoptArgs_DoesSo)
{
   const fs::path iniInputFilePath = p_docoptParserMock->GetRequiredFilePathWhichMustExistMock.ReturnRandom();
   const bool deleteDestinationFoldersFirst = p_docoptParserMock->GetOptionalBoolMock.ReturnRandom();
   const map<string, docopt::value> docoptArgs = ZenUnit::RandomNonEmptyOrderedMap<string, docopt::value>();
   //
   const CloudundancyArgs cloudundancyArgs = _copyFilesToMultipleFoldersArgsParser.ParseDocoptArgs(docoptArgs);
   //
   METALMOCKTHEN(p_docoptParserMock->GetRequiredFilePathWhichMustExistMock.CalledOnceWith(
      docoptArgs, "--ini-file")).Then(

   METALMOCKTHEN(p_docoptParserMock->GetOptionalBoolMock.CalledOnceWith(
      docoptArgs, "--delete-destination-folders-first")));
   CloudundancyArgs expectedCloudundancyArgs;
   expectedCloudundancyArgs.programMode = ProgramMode::CopyFilesToMultipleFolders;
   expectedCloudundancyArgs.iniInputFilePath = iniInputFilePath;
   expectedCloudundancyArgs.deleteDestinationFoldersFirst = deleteDestinationFoldersFirst;
   ARE_EQUAL(expectedCloudundancyArgs, cloudundancyArgs);
}

RUN_TESTS(CopyFilesToMultipleFoldersArgsParserTests)
