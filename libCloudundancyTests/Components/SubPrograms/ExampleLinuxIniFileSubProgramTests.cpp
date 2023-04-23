#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/ExampleLinuxIniFileSubProgram.h"

TESTS(ExampleLinuxIniFileSubProgramTests)
AFACT(Run_PrintsExampleLinuxIniFile_Returns0)
EVIDENCE

ExampleLinuxIniFileSubProgram _exampleLinuxIniFileSubProgram;
// Base Constant Components
Utils::ConsoleMock* p_consoleMock = nullptr;

STARTUP
{
   // Base Constant Components
   _exampleLinuxIniFileSubProgram.p_console.reset(p_consoleMock = new Utils::ConsoleMock);
}

TEST(Run_PrintsExampleLinuxIniFile_Returns0)
{
   p_consoleMock->WriteLineMock.Expect();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   const int exitCode = _exampleLinuxIniFileSubProgram.Run(args);
   //
   const string expectedExampleLinuxIniFileText =
R"(
[DestinationFolders]
/code/dotfiles/LinuxCloudundancy
/home/neil/BlackUSB/LinuxCloudundancy
/home/neil/SilverUSB/LinuxCloudundancy

[SourceFilesAndFolders]
# dotfiles
/code/dotfiles/linux/ -> dotfiles

# Linux
/etc/fstab -> Linux

# VS Code
/home/neil/.config/Code/User/keybindings.json -> VSCode
/home/neil/.config/Code/User/settings.json    -> VSCode
/home/neil/.config/Code/User/snippets/        -> VSCode/Snippets

[FileSubpathsToNotCopy]
/.git/
)";
   METALMOCK(p_consoleMock->WriteLineMock.CalledOnceWith(expectedExampleLinuxIniFileText));
   IS_ZERO(exitCode);
}

RUN_TESTS(ExampleLinuxIniFileSubProgramTests)
