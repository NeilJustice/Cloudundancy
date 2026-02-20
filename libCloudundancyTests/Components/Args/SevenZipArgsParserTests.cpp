#include "pch.h"
#include "libCloudundancy/Components/Args/SevenZipArgsParser.h"

TESTS(SevenZipArgsParserTests)
AFACT(ParseDocoptArgs_DoesSo)
EVIDENCE

SevenZipArgsParser _sevenZipArgsParser;
// Base Constant Components
DocoptParserMock* p_docoptParserMock = nullptr;
// Constant Components
Utils::ConsoleMock* _consoleMock = nullptr;
Utils::ProcessRunnerMock* _processRunnerMock = nullptr;

STARTUP
{
   // Base Constant Components
   _sevenZipArgsParser.p_docoptParser.reset(p_docoptParserMock = new DocoptParserMock);
   // Constant Components
   _sevenZipArgsParser._console.reset(_consoleMock = new Utils::ConsoleMock);
   _sevenZipArgsParser._processRunner.reset(_processRunnerMock = new Utils::ProcessRunnerMock);
}

TEST(ParseDocoptArgs_DoesSo)
{
   const fs::path sevenZipModeIniInputFilePath = ZenUnit::Random<fs::path>();
   const fs::path sevenZipFileCopyingIniInputFilePath = ZenUnit::Random<fs::path>();
   p_docoptParserMock->GetRequiredFilePathWhichMustExistMock.ReturnValues(
      sevenZipModeIniInputFilePath,
      sevenZipFileCopyingIniInputFilePath);

   const fs::path sevenZipStagingFolderPath =
      p_docoptParserMock->GetRequiredFolderPathWhichNeedNotExistMock.ReturnRandom();

   _consoleMock->WriteLineMock.Expect();
   _processRunnerMock->FailFastRunMock.ReturnRandom();

   const map<string, docopt::value> docoptArgs = ZenUnit::RandomNonEmptyOrderedMap<string, docopt::value>();
   //
   const CloudundancyArgs cloudundancyArgs = _sevenZipArgsParser.ParseDocoptArgs(docoptArgs);
   //
   METALMOCK(p_docoptParserMock->GetRequiredFilePathWhichMustExistMock.CalledNTimes(2));
   METALMOCK(_consoleMock->WriteLineMock.CalledNTimes(2));

   METALMOCKTHEN(p_docoptParserMock->GetRequiredFilePathWhichMustExistMock.CalledWith(
      docoptArgs, "--ini-file-to-copy-files-to-7zip-staging-folder")).Then(

   METALMOCKTHEN(p_docoptParserMock->GetRequiredFolderPathWhichNeedNotExistMock.CalledOnceWith(
      docoptArgs, "--7zip-staging-folder"))).Then(

   METALMOCKTHEN(p_docoptParserMock->GetRequiredFilePathWhichMustExistMock.CalledWith(
      docoptArgs, "--ini-file-to-copy-7zip-file-from-staging-folder-to-multiple-folders"))).Then(

   METALMOCKTHEN(_consoleMock->WriteLineMock.CalledWith(
      "[Cloudundancy] Running program 7z to confirm 7z is present on the PATH"))).Then(
   METALMOCKTHEN(_processRunnerMock->FailFastRunMock.CalledOnceWith(
      "7z", "", false))).Then(
   METALMOCKTHEN(_consoleMock->WriteLineMock.CalledWith(
      "[Cloudundancy] 7z ran and exited with code 0 and is therefore confirmed to be present on the PATH\n")));

   CloudundancyArgs expectedCloudundancyArgs;
   expectedCloudundancyArgs.programMode = ProgramMode::SevenZip;
   expectedCloudundancyArgs.sevenZipModeIniInputFilePath = sevenZipModeIniInputFilePath;
   expectedCloudundancyArgs.sevenZipStagingFolderPath = sevenZipStagingFolderPath;
   expectedCloudundancyArgs.sevenZipFileCopyingIniInputFilePath = sevenZipFileCopyingIniInputFilePath;
   ARE_EQUAL(expectedCloudundancyArgs, cloudundancyArgs);
}

RUN_TESTS(SevenZipArgsParserTests)
