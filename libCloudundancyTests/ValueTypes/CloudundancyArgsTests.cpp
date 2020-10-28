#include "pch.h"
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"

TESTS(CloudundancyArgsTests)
AFACT(CommandLineUsage_IsExpectedString)
AFACT(DefaultConstructor_SetsFieldsToDefaults)
EVIDENCE

TEST(CommandLineUsage_IsExpectedString)
{
   ARE_EQUAL(
R"(Cloudundancy v0.6.0
https://github.com/NeilJustice/Cloudundancy

Cloudundancy quickly copies files and folders to multiple configurable destination folders
to achieve cloud-redundancy and device-redundancy backups of key files.
For example, destination folders could be configured to be
a Google Drive folder, a Microsoft OneDrive folder, a USB drive, and a network share
to achieve cloud-redundant and device-redundant backups of key files.

Usage:
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
   ARE_EQUAL(ProgramMode::Unset, cloudundancyArgs.programMode);
   ARE_EQUAL("", cloudundancyArgs.iniFilePath);
   ARE_EQUAL("", cloudundancyArgs.sevenZipIniFilePath);
   ARE_EQUAL("", cloudundancyArgs.backupStagingFolderPath);
}

RUN_TESTS(CloudundancyArgsTests)
