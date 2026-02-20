#include "pch.h"
#include "libCloudundancy/Components/Args/ProgramModeDeterminer.h"
#include "libCloudundancyTests/Components/Docopt/MetalMock/DocoptParserMock.h"

TESTS(ProgramModeDeterminerTests)
AFACT(DetermineProgramMode__ExampleLinuxIniFile)
AFACT(DetermineProgramMode__ExampleWindowsIniFile)
AFACT(DetermineProgramMode__CopyFilesToMultipleFolders)
AFACT(DetermineProgramMode__SevenZip)
AFACT(DetermineProgramMode__Invalid)
EVIDENCE

ProgramModeDeterminer _programModeDeterminer;
// Constant Components
DocoptParserMock* _docoptParserMock = nullptr;

STARTUP
{
   // Constant Components
   _programModeDeterminer._docoptParser.reset(_docoptParserMock = new DocoptParserMock);
}

TEST(DetermineProgramMode__ExampleLinuxIniFile)
{
   _docoptParserMock->GetRequiredBoolMock.Return(true);
   const map<string, docopt::value> docoptArgs = ZenUnit::RandomNonEmptyOrderedMap<string, docopt::value>();
   //
   const ProgramMode programMode = _programModeDeterminer.DetermineProgramMode(docoptArgs);
   //
   METALMOCK(_docoptParserMock->GetRequiredBoolMock.CalledOnceWith(docoptArgs, "example-linux-ini-file"));
   ARE_EQUAL(ProgramMode::ExampleLinuxIniFile, programMode);
}

TEST(DetermineProgramMode__ExampleWindowsIniFile)
{
   _docoptParserMock->GetRequiredBoolMock.ReturnValues(
      false,
      true);
   const map<string, docopt::value> docoptArgs = ZenUnit::RandomNonEmptyOrderedMap<string, docopt::value>();
   //
   const ProgramMode programMode = _programModeDeterminer.DetermineProgramMode(docoptArgs);
   //
   METALMOCK(_docoptParserMock->GetRequiredBoolMock.CalledNTimes(2));
   METALMOCKTHEN(_docoptParserMock->GetRequiredBoolMock.CalledWith(docoptArgs, "example-linux-ini-file")).Then(
   METALMOCKTHEN(_docoptParserMock->GetRequiredBoolMock.CalledWith(docoptArgs, "example-windows-ini-file")));
   ARE_EQUAL(ProgramMode::ExampleWindowsIniFile, programMode);
}

TEST(DetermineProgramMode__CopyFilesToMultipleFolders)
{
   _docoptParserMock->GetRequiredBoolMock.ReturnValues(
      false,
      false,
      true);
   const map<string, docopt::value> docoptArgs = ZenUnit::RandomNonEmptyOrderedMap<string, docopt::value>();
   //
   const ProgramMode programMode = _programModeDeterminer.DetermineProgramMode(docoptArgs);
   //
   METALMOCK(_docoptParserMock->GetRequiredBoolMock.CalledNTimes(3));
   METALMOCKTHEN(_docoptParserMock->GetRequiredBoolMock.CalledWith(docoptArgs, "example-linux-ini-file")).Then(
   METALMOCKTHEN(_docoptParserMock->GetRequiredBoolMock.CalledWith(docoptArgs, "example-windows-ini-file"))).Then(
   METALMOCKTHEN(_docoptParserMock->GetRequiredBoolMock.CalledWith(docoptArgs, "copy-files-to-multiple-folders")));
   ARE_EQUAL(ProgramMode::CopyFilesToMultipleFolders, programMode);
}

TEST(DetermineProgramMode__SevenZip)
{
   _docoptParserMock->GetRequiredBoolMock.ReturnValues(
      false,
      false,
      false,
      true);
   const map<string, docopt::value> docoptArgs = ZenUnit::RandomNonEmptyOrderedMap<string, docopt::value>();
   //
   const ProgramMode programMode = _programModeDeterminer.DetermineProgramMode(docoptArgs);
   //
   METALMOCK(_docoptParserMock->GetRequiredBoolMock.CalledNTimes(4));
   METALMOCKTHEN(_docoptParserMock->GetRequiredBoolMock.CalledWith(docoptArgs, "example-linux-ini-file")).Then(
   METALMOCKTHEN(_docoptParserMock->GetRequiredBoolMock.CalledWith(docoptArgs, "example-windows-ini-file"))).Then(
   METALMOCKTHEN(_docoptParserMock->GetRequiredBoolMock.CalledWith(docoptArgs, "copy-files-to-multiple-folders"))).Then(
   METALMOCKTHEN(_docoptParserMock->GetRequiredBoolMock.CalledWith(docoptArgs, "7zip-files-then-copy-the-7zip-file-to-multiple-folders")));
   ARE_EQUAL(ProgramMode::SevenZip, programMode);
}

TEST(DetermineProgramMode__Invalid)
{
   _docoptParserMock->GetRequiredBoolMock.ReturnValues(
      false,
      false,
      false,
      false);
   const map<string, docopt::value> docoptArgs = ZenUnit::RandomNonEmptyOrderedMap<string, docopt::value>();
   //
   const ProgramMode programMode = _programModeDeterminer.DetermineProgramMode(docoptArgs);
   //
   METALMOCK(_docoptParserMock->GetRequiredBoolMock.CalledNTimes(4));
   METALMOCKTHEN(_docoptParserMock->GetRequiredBoolMock.CalledWith(docoptArgs, "example-linux-ini-file")).Then(
   METALMOCKTHEN(_docoptParserMock->GetRequiredBoolMock.CalledWith(docoptArgs, "example-windows-ini-file"))).Then(
   METALMOCKTHEN(_docoptParserMock->GetRequiredBoolMock.CalledWith(docoptArgs, "copy-files-to-multiple-folders"))).Then(
   METALMOCKTHEN(_docoptParserMock->GetRequiredBoolMock.CalledWith(docoptArgs, "7zip-files-then-copy-the-7zip-file-to-multiple-folders")));
   ARE_EQUAL(ProgramMode::Invalid, programMode);
}

RUN_TESTS(ProgramModeDeterminerTests)
