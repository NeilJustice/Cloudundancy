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

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOMINMAX
#include "Windows.h"
#endif
using namespace std;

#include "libCloudundancy/Components/CloudundancyProgram.h"
#include "libCloudundancy/Enums/Color.h"
#include "libCloudundancy/UtilityComponents/Console/Console.h"
#include "libCloudundancy/UtilityComponents/Environment/Environmentalist.h"
#include "libCloudundancy/UtilityComponents/Exception/TryCatchCaller.h"
#include "libCloudundancy/UtilityComponents/Time/Stopwatch.h"
#include "libCloudundancy/UtilityComponents/Time/Watch.h"

// Production Cloudundancy command lines:
// copy-files-to-multiple-folders --ini-file=C:\Code\dotfiles\WindowsCloudundancy.ini
// 7zip-files-then-copy-the-7zip-file-to-multiple-folders --ini-file-to-copy-files-to-7zip-staging-folder=C:\Code\dotfiles\WindowsCloudundancy_CopyCodeFolderTo7ZipStagingFolder.ini --7zip-staging-folder=C:\CodeFolderBackupStaging --ini-file-to-copy-7zip-file-from-staging-folder-to-multiple-folders=C:\Code\dotfiles\WindowsCloudundancy_Copy7ZipFileFromStagingFolderToMultipleFolders.ini

// Testing Cloudundancy command lines:
// example-linux-ini-file
// example-windows-ini-file
// copy-files-to-multiple-folders --ini-file=C:\Test\Cloudundancy.ini --delete-destination-folders-first
// 7zip-files-then-copy-the-7zip-file-to-multiple-folders --ini-file-to-copy-files-to-7zip-staging-folder=C:\Test\FileCopyingToStagingFolder.ini --7zip-staging-folder=C:\Test\BackupStagingFolder --ini-file-to-copy-7zip-file-from-staging-folder-to-multiple-folders=C:\Test\7zipCopying.ini

int main(int argc, char* argv[])
{
   CloudundancyProgram cloudundancyProgram;
   const int exitCode = cloudundancyProgram.Main(argc, argv);
   return exitCode;
}
