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
// print-example-linux-ini-file
// print-example-windows-ini-file
// backup-files-to-multiple-folders --ini-file=C:\Code\dotfiles\WindowsCloudundancy.ini
// backup-files-and-folders-to-7z-file --ini-file=C:\Code\dotfiles\WindowsCloudundancy_CodeFolderBackups.ini --7z-ini-file=C:\Code\dotfiles\WindowsCloudundancy_CodeFolderBackups_7zFileCopyStep.ini --backup-staging-folder=C:\CodeFolderBackupStaging

// Testing Cloudundancy command lines:
// backup-files-to-multiple-folders --ini-file=C:\Test\Cloudundancy.ini
// backup-files-and-folders-to-7z-file --ini-file=C:\Test\Cloudundancy7z1.ini --7z-ini-file=C:\Test\Cloudundancy7z2.ini --backup-staging-folder=C:\Test\BackupStagingFolder

int main(int argc, char* argv[])
{
   CloudundancyProgram cloudundancyProgram;
   const int exitCode = cloudundancyProgram.Main(argc, argv);
   return exitCode;
}
