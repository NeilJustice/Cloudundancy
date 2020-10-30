#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/ExampleLinuxIniFileSubProgram.h"

TESTS(ExampleLinuxIniFileSubProgramTests)
AFACT(Run_PrintsExampleLinuxIniFile_Returns0)
EVIDENCE

ExampleLinuxIniFileSubProgram _exampleLinuxIniFileSubProgram;
ConsoleMock* _consoleMock = nullptr;

STARTUP
{
   _exampleLinuxIniFileSubProgram._console.reset(_consoleMock = new ConsoleMock);
}

TEST(Run_PrintsExampleLinuxIniFile_Returns0)
{
   _consoleMock->WriteLineMock.Expect();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   const int exitCode = _exampleLinuxIniFileSubProgram.Run(args);
   //
   const string expectedExampleLinuxIniFileText =
R"(
[DestinationFolders]
[SourceFilesAndFolders]
[FileSubpathsToNotCopy]
)";
   METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(expectedExampleLinuxIniFileText));
   IS_ZERO(exitCode);
}

RUN_TESTS(ExampleLinuxIniFileSubProgramTests)
