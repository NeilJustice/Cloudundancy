#include "pch.h"
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"

TESTS(CloudundancyArgsTests)
AFACT(CommandLineUsage_IsExpectedString)
AFACT(DefaultConstructor_SetsFieldsToDefaults)
EVIDENCE

TEST(CommandLineUsage_IsExpectedString)
{
   ARE_EQUAL(
R"(Cloudundancy v1.0.0
Copies configurable file and folder paths to configurable file and folder paths.
For example, on Windows, destination folder paths can be set to C:\GoogleDrive and C:\OneDrive
to achieve cloud-redundant backups by way of automatic cloud uploading.

Usage:
   cloudundancy example-linux-ini-file
   cloudundancy example-windows-ini-file
   cloudundancy copy-files-to-multiple-folders --ini-file=<FilePath> [--delete-destination-folders-first]
   cloudundancy 7zip-files-then-copy-the-7zip-file-to-multiple-folders
      --ini-file-to-copy-files-to-7zip-staging-folder=<FilePath>
      --7zip-staging-folder=<FolderPath>
      --ini-file-to-copy-7zip-file-from-staging-folder-to-multiple-folders=<FilePath>
)", CloudundancyArgs::CommandLineUsage);
}

TEST(DefaultConstructor_SetsFieldsToDefaults)
{
   const CloudundancyArgs cloudundancyArgs;
   CloudundancyArgs expectedCloudundancyArgs;
   expectedCloudundancyArgs.programMode = ProgramMode::Unset;
   expectedCloudundancyArgs.iniFilePath = "";
   expectedCloudundancyArgs.deleteDestinationFoldersFirst = false;
   expectedCloudundancyArgs.sevenZipModeIniFilePath = "";
   expectedCloudundancyArgs.sevenZipStagingFolderPath = "";
   expectedCloudundancyArgs.sevenZipFileCopyingIniFilePath = "";
   ARE_EQUAL(expectedCloudundancyArgs, cloudundancyArgs);
}

RUN_TESTS(CloudundancyArgsTests)
