#include "pch.h"
#include "libCloudundancy/Components/Args/CloudundancyArgsParser.h"
#include "libCloudundancyTests/Components/Args/MetalMock/ProgramModeDeterminerMock.h"
#include "libCloudundancyTests/Components/Args/MetalMock/ProgramModeSpecificArgsParserFactoryMock.h"
#include "libCloudundancyTests/Components/Args/MetalMock/ProgramModeSpecificArgsParserMock.h"

TESTS(CloudundancyArgsParserTests)
AFACT(ParseStringArgs_DoesSo)
EVIDENCE

CloudundancyArgsParser _cloudundancyArgsParser;
// Constant Components
Utils::ConsoleMock* _consoleMock = nullptr;
DocoptParserMock* _docoptParserMock = nullptr;
Utils::FileSystemMock* _fileSystemMock = nullptr;
Utils::ProcessRunnerMock* _processRunnerMock = nullptr;
ProgramModeDeterminerMock* _programModeDeterminerMock = nullptr;
ProgramModeSpecificArgsParserFactoryMock* _programModeSpecificArgsParserFactoryMock = nullptr;

STARTUP
{
   // Constant Components
   _cloudundancyArgsParser._console.reset(_consoleMock = new Utils::ConsoleMock);
   _cloudundancyArgsParser._docoptParser.reset(_docoptParserMock = new DocoptParserMock);
   _cloudundancyArgsParser._fileSystem.reset(_fileSystemMock = new Utils::FileSystemMock);
   _cloudundancyArgsParser._processRunner.reset(_processRunnerMock = new Utils::ProcessRunnerMock);
   _cloudundancyArgsParser._programModeDeterminer.reset(_programModeDeterminerMock = new ProgramModeDeterminerMock);
   _cloudundancyArgsParser._programModeSpecificArgsParserFactory.reset(_programModeSpecificArgsParserFactoryMock = new ProgramModeSpecificArgsParserFactoryMock);
}

TEST(ParseStringArgs_DoesSo)
{
   const map<string, docopt::value> docoptArgs = ZenUnit::RandomOrderedMap<string, docopt::value>();
   _docoptParserMock->ParseArgsMock.Return(docoptArgs);

   const ProgramMode programMode = _programModeDeterminerMock->DetermineProgramModeMock.ReturnRandom();

   const shared_ptr<const ProgramModeSpecificArgsParserMock> programModeSpecificArgsParserMock =
      make_shared<ProgramModeSpecificArgsParserMock>();
   _programModeSpecificArgsParserFactoryMock->NewProgramModeSpecificArgsParserMock.Return(programModeSpecificArgsParserMock);

   const CloudundancyArgs cloudundancyArgs = programModeSpecificArgsParserMock->ParseDocoptArgsMock.ReturnRandom();

   const vector<string> stringArgs = ZenUnit::RandomVector<string>();
   //
   const CloudundancyArgs returnedCloudundancyArgs = _cloudundancyArgsParser.ParseStringArgs(stringArgs);
   //
   METALMOCKTHEN(_docoptParserMock->ParseArgsMock.CalledOnceWith(
      CloudundancyArgs::CommandLineUsage, stringArgs, false)).Then(

   METALMOCKTHEN(_programModeDeterminerMock->DetermineProgramModeMock.CalledOnceWith(
      docoptArgs))).Then(

   METALMOCKTHEN(_programModeSpecificArgsParserFactoryMock->NewProgramModeSpecificArgsParserMock.CalledOnceWith(
      programMode))).Then(

   METALMOCKTHEN(programModeSpecificArgsParserMock->ParseDocoptArgsMock.CalledOnceWith(
      docoptArgs)));

   ARE_EQUAL(cloudundancyArgs, returnedCloudundancyArgs);
}

RUN_TESTS(CloudundancyArgsParserTests)
