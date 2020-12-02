#include "libCloudundancy/CompilerWarnings/IfWindowsIgnoreTheseWarningsGlobally.h"

#if defined __linux__
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#include <memory>
#include <unistd.h>
#elif defined _WIN32 || defined __APPLE__
#pragma warning(push)
#pragma warning(disable: 4365) // signed/unsigned mismatch
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <filesystem>
namespace fs = std::filesystem;
#pragma warning(pop)
#endif

#include <functional>
#ifdef __linux__
#include <memory> // unique_ptr
#endif
#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOMINMAX
#include "Windows.h"
using namespace std;

#include "libCloudundancy/Enums/Color.h"
#include "libCloudundancy/UtilityComponents/Console/Console.h"
#include "libCloudundancy/UtilityComponents/Environment/Environmentalist.h"
#include "libCloudundancy/UtilityComponents/Exception/TryCatchCaller.h"
#include "libCloudundancy/UtilityComponents/Time/Stopwatch.h"
#include "libCloudundancy/UtilityComponents/Time/Watch.h"
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
