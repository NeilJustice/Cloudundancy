#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/ExampleLinuxIniFileSubProgram.h"

int ExampleLinuxIniFileSubProgram::Run(const CloudundancyArgs&)
{
   const string exampleLinuxIniFileText =
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
/builds/
/cobertura/
/lastStable
/lastSuccessful/
nextBuildNumber
scm-polling.log
)";
   _console->WriteLine(exampleLinuxIniFileText);
   return 0;
}
