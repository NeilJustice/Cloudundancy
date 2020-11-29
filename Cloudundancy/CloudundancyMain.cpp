#include "libCloudundancy/CompilerWarnings/IfWindowsIgnoreTheseWarningsGlobally.h"
#include <functional>
#ifdef __linux__
#include <memory> // unique_ptr
#endif
#include "libCloudundancy/Components/CloudundancyProgram.h"

// Example Cloudundancy command lines:
// example-linux-ini-file
// example-windows-ini-file
// backup-files-and-folders --ini-file=C:\Code\dotfiles\WindowsCloudundancy.ini
// backup-files-and-folders-to-7z-file --ini-file=C:\Code\dotfiles\WindowsCloudundancy_CodeFolderBackups.ini --7z-ini-file=C:\Code\dotfiles\WindowsCloudundancy_CodeFolderBackups_7zFileCopyStep.ini --backup-staging-folder=C:\CodeFolderBackupStaging

// Acceptance Testing
// backup-files-and-folders --ini-file=C:\Code\Cloudundancy\AcceptanceTesting\IniFiles\BlankIniFile.ini
// backup-files-and-folders --ini-file=C:\Code\Cloudundancy\AcceptanceTesting\IniFiles\AllThreeHeadingsPresentButBlank.ini
// backup-files-and-folders --ini-file=C:\Code\Cloudundancy\AcceptanceTesting\IniFiles\DestinationFolderExistsButNoWriteAccess.ini
// backup-files-and-folders --ini-file=C:\Code\Cloudundancy\AcceptanceTesting\IniFiles\NonExistentDestinationFolder.ini
// backup-files-and-folders --ini-file=C:\Code\Cloudundancy\AcceptanceTesting\IniFiles\NonExistentSourceFile.ini
// backup-files-and-folders --ini-file=C:\Code\Cloudundancy\AcceptanceTesting\IniFiles\NonExistentSourceFolder.ini
// backup-files-and-folders --ini-file=C:\Code\Cloudundancy\AcceptanceTesting\IniFiles\SourceFileExistsButNoReadAccess.ini
// backup-files-and-folders --ini-file=C:\Code\Cloudundancy\AcceptanceTesting\IniFiles\SourceFolderExistsButNoReadAccess.ini

int main(int argc, char* argv[])
{
   CloudundancyProgram cloudundancyProgram;
   const int exitCode = cloudundancyProgram.Main(argc, argv);
   return exitCode;
}
