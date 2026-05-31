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
   //
   const int exitCode = _exampleLinuxIniFileSubProgram.Run();
   //
   const string expectedExampleLinuxIniFileText =
R"(
[DestinationFolders]
/code/dotfiles/LinuxCloudundancy
/home/user/USBDrive1/LinuxCloudundancy
/home/user/USBDrive2/LinuxCloudundancy

[SourceFilesAndFolders]
/etc/fstab -> Linux
/home/user/.config/Code/User/keybindings.json -> VSCode
/home/user/.config/Code/User/settings.json    -> VSCode
/home/user/.config/Code/User/snippets/        -> VSCode/Snippets
)";
   METALMOCK(p_consoleMock->WriteLineMock.CalledOnceWith(expectedExampleLinuxIniFileText));
   IS_ZERO(exitCode);
}

RUN_TESTS(ExampleLinuxIniFileSubProgramTests)
