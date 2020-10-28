#include "libCloudundancy/Components/Compiler/MSVCIgnoredWallWarnings.h"
#include <functional>
#ifdef __linux__
#include <memory> // unique_ptr
#endif
#include "libCloudundancy/Components/CloudundancyProgram.h"

// backup-files-and-folders --ini-file=C:\Code\dotfiles\HomeWindowsCloudundancy.ini
// backup-files-and-folders-to-7z-file --ini-file=C:\Code\dotfiles\HomeWindowsCloudundancy_CodeFolderBackups.ini --7z-ini-file=C:\Code\dotfiles\HomeWindowsCloudundancy_CodeFolderBackups_7zFileCopyStep.ini --backup-staging-folder=C:\CodeFolderBackupStaging

// backup-files-and-folders --ini-file=C:\Code\dotfiles\WorkWindowsCloudundancy.ini
// backup-files-and-folders-to-7z-file --ini-file=C:\Code\dotfiles\WorkWindowsCloudundancyCodeBackup.ini --7z-ini-file=C:\Code\dotfiles\WorkWindowsCloudundancyCodeBackup7zFile.ini --backup-staging-folder=C:\CodeFolderBackupStaging

int main(int argc, char* argv[])
{
   CloudundancyProgram cloudundancyProgram;
   const int exitCode = cloudundancyProgram.Main(argc, argv);
   return exitCode;
}
