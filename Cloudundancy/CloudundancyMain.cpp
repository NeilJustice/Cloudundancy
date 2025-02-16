#include "libCloudundancy/Compiler/IfWindowsIgnoreTheseWarningsGlobally.h"

#include <filesystem>
#include <functional>
namespace fs = std::filesystem;

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOMINMAX
#include "Windows.h"
#endif
using namespace std;

#include "libCloudundancy/Components/CloudundancyProgram.h"

// Testing Args
// ============
// copy-files-to-multiple-folders --ini-file=C:\Code\Cloudundancy\TestingIniFiles\WindowsCloudundancy.ini
// 7zip-files-then-copy-the-7zip-file-to-multiple-folders --ini-file-to-copy-files-to-7zip-staging-folder=D:\Cloudundancy7ZipTesting\CodeFolderTo7ZipStagingFolderCopyingStep.ini --7zip-staging-folder=D:\Cloudundancy7ZipTesting\7ZipStagingFolder --ini-file-to-copy-7zip-file-from-staging-folder-to-multiple-folders=D:\Cloudundancy7ZipTesting\7ZipFileToGoogleDriveAndOneDriveCopyingStep.ini
// example-linux-ini-file
// example-windows-ini-file

// Production Args
// ===============
// copy-files-to-multiple-folders --ini-file=C:\Code\PowerShellFiles\WindowsCloudundancy.ini
// copy-files-to-multiple-folders --ini-file=C:\Code\PowerShellFiles\WindowsCloudundancy.ini --delete-destination-folders-first
// 7zip-files-then-copy-the-7zip-file-to-multiple-folders --ini-file-to-copy-files-to-7zip-staging-folder=C:\Code\PowerShellFiles\WindowsCloudundancy_CopyCodeFolderTo7ZipStagingFolder.ini --7zip-staging-folder=D:\CodeBackup --ini-file-to-copy-7zip-file-from-staging-folder-to-multiple-folders=C:\Code\PowerShellFiles\WindowsCloudundancy_Copy7ZipFileFromStagingFolderToMultipleFolders.ini

int main(int argc, char* argv[])
{
   CloudundancyProgram cloudundancyProgram;
   int exitCode = cloudundancyProgram.Main(argc, argv);
   return exitCode;
}
