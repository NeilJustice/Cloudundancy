#include "pch.h"
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"

TESTS(CloudundancyArgsTests)
AFACT(CommandLineUsage_IsExpectedString)
AFACT(DefaultConstructor_SetsFieldsToDefaults)
EVIDENCE

TEST(CommandLineUsage_IsExpectedString)
{
   ARE_EQUAL(
R"(Cloudundancy v0.9.0 - Makes cloud-redundant and device-redundant file backups
https://github.com/NeilJustice/Cloudundancy

Usage:
   Cloudundancy example-linux-ini-file
   Cloudundancy example-windows-ini-file
   Cloudundancy backup-files-and-folders --ini-file=<CloudundancyIniFilePath>
   Cloudundancy backup-files-and-folders-to-7z-file
      --ini-file=<CloudundancyIniFilePath>
      --7z-ini-file=<CloudundancyIniFilePath>
      --backup-staging-folder=<FolderPath>
)", CloudundancyArgs::CommandLineUsage);
}

TEST(DefaultConstructor_SetsFieldsToDefaults)
{
   const CloudundancyArgs cloudundancyArgs;
   CloudundancyArgs expectedCloudundancyArgs;
   expectedCloudundancyArgs.programMode = ProgramMode::Unset;
   expectedCloudundancyArgs.iniFilePath = "";
   expectedCloudundancyArgs.sevenZipIniFilePath = "";
   expectedCloudundancyArgs.backupStagingFolderPath = "";
   ARE_EQUAL(expectedCloudundancyArgs, cloudundancyArgs);
}

RUN_TESTS(CloudundancyArgsTests)
