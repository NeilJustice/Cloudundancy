#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/ExampleLinuxIniFileSubProgram.h"

int ExampleLinuxIniFileSubProgram::Run(const CloudundancyArgs&)
{
   const string exampleLinuxIniFileText =
R"(
[DestinationFolders]
[SourceFilesAndFolders]
[FileSubpathsToNotCopy]
)";
   _console->WriteLine(exampleLinuxIniFileText);
   return 0;
}
