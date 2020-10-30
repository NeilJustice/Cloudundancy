# Cloudundancy

[![Standard](https://img.shields.io/badge/c%2B%2B-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B17) [![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

|Build Type|Build Status|
|----------|------------|
|Travis CI Linux (Clang 7.0.0 and GCC 7.4.0)|<a href="https://travis-ci.org/NeilJustice/Cloudundancy"><img src="https://travis-ci.org/NeilJustice/Cloudundancy.svg?branch=master"/></a>|
|AppVeyor Windows (Visual Studio 2019 x64)|<a href="https://ci.appveyor.com/project/NeilJustice/Cloudundancy"><img src="https://ci.appveyor.com/api/projects/status/ygwr3rb9spwhy4u0?svg=true"/></a>|
|Code Coverage For The GCC 7.4.0 Release Build|[![codecov](https://codecov.io/gh/NeilJustice/Cloudundancy/branch/master/graph/badge.svg?token=ruXbRPB1CQ)](https://codecov.io/gh/NeilJustice/Cloudundancy)|

Cloudundancy is rigorously unit tested with <a href="https://github.com/NeilJustice/ZenUnitAndMetalMock">ZenUnit and MetalMock</a>.

* [Command Line Usage](#command-line-usage)
* [Cloudundancy Program Modes](#cloudundancy-program-modes)
   * [backup-files-and-folders](#backup-files-and-folders)
   * [backup-files-and-folders-to-7z-file](#backup-files-and-folders-to-7z-file)
* [Linux Jenkins Jobs Which Compile, clang-tidy, AddressSanitize, UndefinedBehaviorSanitize, and ThreadSanitize Cloudundancy](#linux-jenkins-jobs-which-compile-clang-tidy-addresssanitize-undefinedbehaviorsanitize-and-threadsanitize-cloudundancy)
* [Windows Jenkins Jobs Which Compile Cloudundancy](#windows-jenkins-jobs-which-compile-cloudundancy)
* [4 Commands To Build And Install Cloudundancy On Linux](#4-commands-to-build-and-install-cloudundancy-on-linux)
* [4 Commands To Build And Install Cloudundancy On Windows](#4-commands-to-build-and-install-cloudundancy-on-windows)

## Command Line Usage

```
Cloudundancy v0.7.0
https://github.com/NeilJustice/Cloudundancy

Cloudundancy quickly copies files and folders to multiple configurable destination folders
to achieve cloud-redundant and device-redundant backups of key files.
For example, destination folders could be configured to be
a Google Drive folder, a Microsoft OneDrive folder, two USB sticks, and a network share
to achieve cloud-redundant and device-redundant backups of key files.

Usage:
   Cloudundancy backup-files-and-folders --ini-file=<CloudundancyIniFilePath>
   Cloudundancy backup-files-and-folders-to-7z-file
      --ini-file=<CloudundancyIniFilePath>
      --7z-ini-file=<CloudundancyIniFilePath>
      --backup-staging-folder=<FolderPath>
```

## Cloudundancy Program Modes

### backup-files-and-folders

### backup-files-and-folders-to-7z-file

### Linux Jenkins Jobs Which Compile, clang-tidy, AddressSanitize, UndefinedBehaviorSanitize, and ThreadSanitize Cloudundancy

A Jenkins Blue Ocean build pipeline builds the following Cloudundancy Jenkins jobs on Fedora 33:

### Windows Jenkins Jobs Which Compile Cloudundancy

A Jenkins Blue Ocean build pipeline builds the following Cloudundancy Jenkins jobs on Windows 10:

## 4 Commands To Build And Install Cloudundancy On Linux

```
git clone https://github.com/NeilJustice/Cloudundancy
cd Cloudundancy && mkdir Release && cd Release
CXX=clang++ cmake .. -DCMAKE_BUILD_TYPE=Release
sudo cmake --build . --target install
```

## 4 Commands To Build And Install Cloudundancy On Windows

```
git clone https://github.com/NeilJustice/Cloudundancy
cd Cloudundancy
cmake . -G"Visual Studio 16 2019" -A x64 -DCMAKE_INSTALL_PREFIX=C:\bin
cmake --build . --config Release --target install
```
