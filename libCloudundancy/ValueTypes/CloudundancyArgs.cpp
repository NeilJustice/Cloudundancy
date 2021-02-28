#include "pch.h"
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"

const string CloudundancyArgs::CommandLineUsage =
R"(Cloudundancy v0.9.2 - Creates cloud-redundant and device-redundant file backups
https://github.com/NeilJustice/Cloudundancy

Usage:
   cloudundancy example-linux-ini-file
   cloudundancy example-windows-ini-file
   cloudundancy copy-files-to-multiple-folders --ini-file=<CloudundancyIniFilePath> [--delete-destination-folders-first]
   cloudundancy 7zip-files-then-copy-the-7zip-file-to-multiple-folders
      --ini-file-to-copy-files-to-7zip-staging-folder=<CloudundancyIniFilePath>
      --7zip-staging-folder=<FolderPath>
      --ini-file-to-copy-7zip-file-from-staging-folder-to-multiple-folders=<CloudundancyIniFilePath>
)";
