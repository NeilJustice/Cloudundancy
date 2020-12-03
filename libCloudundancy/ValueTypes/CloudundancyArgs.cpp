#include "pch.h"
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"

const string CloudundancyArgs::CommandLineUsage =
R"(Cloudundancy v0.9.0 - Makes cloud-redundant and device-redundant file backups
https://github.com/NeilJustice/Cloudundancy

Usage:
   Cloudundancy print-example-linux-ini-file
   Cloudundancy print-example-windows-ini-file
   Cloudundancy backup-files-to-multiple-folders --ini-file=<CloudundancyIniFilePath> [--delete-destination-folders-first]
   Cloudundancy backup-files-and-folders-to-7z-file
      --ini-file=<CloudundancyIniFilePath>
      --7z-ini-file=<CloudundancyIniFilePath>
      --backup-staging-folder=<FolderPath>
)";
