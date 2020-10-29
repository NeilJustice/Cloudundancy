#include "libCloudundancy/CompilerWarnings/IfWindowsIgnoreTheseWarningsGlobally.h"
#include <functional>
#ifdef __linux__
#include <memory> // unique_ptr
#endif
#include "libCloudundancy/Components/CloudundancyProgram.h"

// backup-files-and-folders --ini-file=C:\Code\dotfiles\HomeWindowsCloudundancy.ini
// backup-files-and-folders-to-7z-file --ini-file=C:\Code\dotfiles\HomeWindowsCloudundancy_CodeFolderBackups.ini --7z-ini-file=C:\Code\dotfiles\HomeWindowsCloudundancy_CodeFolderBackups_7zFileCopyStep.ini --backup-staging-folder=C:\CodeFolderBackupStaging

// Acceptance Testing
// backup-files-and-folders --ini-file=C:\Code\Cloudundancy\AcceptanceTesting\IniFiles\CompletelyBlankIniFile.ini
// backup-files-and-folders --ini-file=C:\Code\Cloudundancy\AcceptanceTesting\IniFiles\AllThreeHeadingsPresentButBlankIniFile.ini
// C:\Code\Cloudundancy\AcceptanceTesting\IniFiles\DestinationFolderExistsButNoWriteAccess.ini
// C:\Code\Cloudundancy\AcceptanceTesting\IniFiles\NonExistentDestinationFolder.ini
// C:\Code\Cloudundancy\AcceptanceTesting\IniFiles\NonExistentSourceFile.ini
// C:\Code\Cloudundancy\AcceptanceTesting\IniFiles\NonExistentSourceFolder.ini
// C:\Code\Cloudundancy\AcceptanceTesting\IniFiles\SourceFileExistsButNoReadAccess.ini
// C:\Code\Cloudundancy\AcceptanceTesting\IniFiles\SourceFolderExistsButNoReadAccess.ini

int main(int argc, char* argv[])
{
   CloudundancyProgram cloudundancyProgram;
   const int exitCode = cloudundancyProgram.Main(argc, argv);
   return exitCode;
}
