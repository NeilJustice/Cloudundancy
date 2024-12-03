#include "libCloudundancy/Compiler/IfWindowsIgnoreTheseWarningsGlobally.h"

#include <filesystem>
#include <functional>
namespace fs = std::filesystem;

#if defined __linux__ || defined __APPLE__
#include <memory>
#include <unistd.h>
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
#include "libCloudundancy/UtilityComponents/Asserters/Asserter.h"
#include "libCloudundancy/UtilityComponents/Console/Console.h"
#include "libCloudundancy/UtilityComponents/Environment/EnvironmentService.h"
#include "libCloudundancy/UtilityComponents/Exception/TryCatchCaller.h"
#include "libCloudundancy/UtilityComponents/Time/Stopwatch.h"
#include "libCloudundancy/UtilityComponents/Time/Watch.h"

// Production Cloudundancy command lines:
// copy-files-to-multiple-folders --ini-file=C:\Code\dotfiles\WindowsCloudundancy.ini --delete-destination-folders-first
// 7zip-files-then-copy-the-7zip-file-to-multiple-folders --ini-file-to-copy-files-to-7zip-staging-folder=C:\Code\dotfiles\WindowsCloudundancy_CopyCodeFolderTo7ZipStagingFolder.ini --7zip-staging-folder=D:\CodeBackup --ini-file-to-copy-7zip-file-from-staging-folder-to-multiple-folders=C:\Code\dotfiles\WindowsCloudundancy_Copy7ZipFileFromStagingFolderToMultipleFolders.ini

// Testing Cloudundancy command lines:
// copy-files-to-multiple-folders --ini-file=D:\CloudundancyTesting\Cloudundancy.ini --delete-destination-folders-first
// 7zip-files-then-copy-the-7zip-file-to-multiple-folders --ini-file-to-copy-files-to-7zip-staging-folder=D:\Cloudundancy7ZipTesting\CodeFolderTo7ZipStagingFolderCopyingStep.ini --7zip-staging-folder=D:\Cloudundancy7ZipTesting\7ZipStagingFolder --ini-file-to-copy-7zip-file-from-staging-folder-to-multiple-folders=D:\Cloudundancy7ZipTesting\7ZipFileToGoogleDriveAndOneDriveCopyingStep.ini
// example-linux-ini-file
// example-windows-ini-file

int main(int argc, char* argv[])
{
   CloudundancyProgram cloudundancyProgram;
   const int exitCode = cloudundancyProgram.Main(argc, argv);
   return exitCode;
}
