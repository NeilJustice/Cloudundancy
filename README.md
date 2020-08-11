# Cloudundancy

[![Standard](https://img.shields.io/badge/c%2B%2B-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B17) [![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

|Build Type|Build Status|
|----------|------------|
|Travis CI Linux (Clang 7.0.0 and GCC 7.4.0)|<a href="https://travis-ci.org/NeilJustice/Cloudundancy"><img src="https://travis-ci.org/NeilJustice/Cloudundancy.svg?branch=master"/></a>|
|AppVeyor Windows (Visual Studio 2019 x64)|<a href="https://ci.appveyor.com/project/NeilJustice/Cloudundancy"><img src="https://ci.appveyor.com/api/projects/status/ygwr3rb9spwhy4u0?svg=true"/></a>|

[![codecov](https://codecov.io/gh/NeilJustice/Cloudundancy/branch/master/graph/badge.svg?token=ruXbRPB1CQ)](https://codecov.io/gh/NeilJustice/Cloudundancy) Cloudundancy is rigorously unit tested with <a href="https://github.com/NeilJustice/ZenUnitAndMetalMock">ZenUnit and MetalMock</a>.

* [Command Line Usage](#command-line-usage)

## Command Line Usage

```
Cloudundancy v0.6.0
https://github.com/NeilJustice/Cloudundancy

Cloudundancy quickly copies files and folders to multiple destination folders.
Destination folders can be configured to be a Google Drive folder, a Microsoft OneDrive folder, 
a USB drive, and a network share to achieve cloud-redundant and device-redundant backups of key files.

Usage:
   Cloudundancy backup-files-and-folders --ini-file=<CloudundancyIniFilePath>
   Cloudundancy backup-files-and-folders-to-7z-file
      --ini-file=<CloudundancyIniFilePath>
      --7z-ini-file=<CloudundancyIniFilePath>
      --backup-staging-folder=<FolderPath>
```
