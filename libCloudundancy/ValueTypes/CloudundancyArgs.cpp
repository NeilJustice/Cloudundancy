#include "pch.h"
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"

const string CloudundancyArgs::CommandLineUsage =
R"(Cloudundancy v0.6.0
https://github.com/NeilJustice/Cloudundancy

Cloudundancy quickly copies source files and folders to multiple destination folders.
When the destination folders are configured to be a Google Drive folder, a Microsoft OneDrive folder,
a USB drive, and a network share, cloud-redundant and device-redundant backups of key files are achieved.

Usage:
   Cloudundancy backup-files-and-folders --ini-file=<CloudundancyIniFilePath>
   Cloudundancy backup-files-and-folders-to-7z-file
      --ini-file=<CloudundancyIniFilePath>
      --7z-ini-file=<CloudundancyIniFilePath>
      --backup-staging-folder=<FolderPath>
)";
