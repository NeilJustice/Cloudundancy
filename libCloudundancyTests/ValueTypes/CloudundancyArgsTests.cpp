#include "pch.h"
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"

TESTS(CloudundancyArgsTests)
AFACT(CommandLineUsage_IsExpectedString)
AFACT(DefaultConstructor_SetsFieldsToDefaults)
EVIDENCE

TEST(CommandLineUsage_IsExpectedString)
{
   ARE_EQUAL(
R"(Cloudundancy v0.9.2 - Creates cloud-redundant and device-redundant file backups
https://github.com/NeilJustice/Cloudundancy

Usage:
   cloudundancy copy-files-to-multiple-folders --ini-file=<CloudundancyIniFilePath> [--delete-destination-folders-first]
   cloudundancy 7zip-files-then-copy-the-7zip-file-to-multiple-folders
      --ini-file-to-copy-files-to-7zip-staging-folder=<CloudundancyIniFilePath>
      --7zip-staging-folder=<FolderPath>
      --ini-file-to-copy-7zip-file-from-staging-folder-to-multiple-folders=<CloudundancyIniFilePath>
   cloudundancy example-linux-ini-file
   cloudundancy example-windows-ini-file
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
