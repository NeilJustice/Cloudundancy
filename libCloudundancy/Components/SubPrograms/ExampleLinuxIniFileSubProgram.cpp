#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/ExampleLinuxIniFileSubProgram.h"

int ExampleLinuxIniFileSubProgram::Run()
{
   const string exampleLinuxIniFileText =
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
   p_console->WriteLine(exampleLinuxIniFileText);
   return 0;
}
