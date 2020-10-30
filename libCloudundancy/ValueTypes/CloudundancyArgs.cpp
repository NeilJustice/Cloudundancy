#include "pch.h"
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"

const string CloudundancyArgs::CommandLineUsage =
R"(Cloudundancy v0.8.0
https://github.com/NeilJustice/Cloudundancy

Cloudundancy quickly copies files and folders to multiple configurable destination folders
to achieve cloud-redundant and device-redundant backups of key files.
For example, destination folders could be configured to be
a Google Drive folder, a Microsoft OneDrive folder, two USB drives, and a network share
to achieve cloud-redundant and device-redundant backups of key files.

Usage:
   Cloudundancy example-linux-ini-file
   Cloudundancy example-windows-ini-file
   Cloudundancy backup-files-and-folders --ini-file=<CloudundancyIniFilePath>
   Cloudundancy backup-files-and-folders-to-7z-file
      --ini-file=<CloudundancyIniFilePath>
      --7z-ini-file=<CloudundancyIniFilePath>
      --backup-staging-folder=<FolderPath>
)";
