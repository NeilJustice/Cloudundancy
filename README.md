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
   * [example-linux-ini-file](#example-linux-ini-file)
   * [example-windows-ini-file](#example-windows-ini-file)
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
a Google Drive folder, a Microsoft OneDrive folder, two USB drives, and a network share
to achieve cloud-redundant and device-redundant backups of key files.

Usage:
   Cloudundancy backup-files-and-folders --ini-file=<CloudundancyIniFilePath>
   Cloudundancy backup-files-and-folders-to-7z-file
      --ini-file=<CloudundancyIniFilePath>
      --7z-ini-file=<CloudundancyIniFilePath>
      --backup-staging-folder=<FolderPath>
   Cloudundancy example-linux-ini-file
   Cloudundancy example-windows-ini-file
```

## Cloudundancy Program Modes

### backup-files-and-folders

10/30/2020 work in progress.

### backup-files-and-folders-to-7z-file

10/30/2020 work in progress.

### example-linux-ini-file

10/30/2020 work in progress.

### example-windows-ini-file

Cloudundancy program mode `example-windows-ini-file` prints an example Cloudundancy .ini file for backing up two key files and two key folders to `C:\GoogleDrive\CloudundancyBackups`, `C:\OneDrive\CloudundancyBackups`, first USB drive `D:\CloudundancyBackups`, second USB drive `E:\CloudundancyBackups`, and Git repo folder `C:\Repos\CloudundancyBackups`, thereby achieving peace of mind data security by way of quintuple backups to two clouds, two USB drives, and GitHub.

![Example Windows Cloudundancy .ini File](Screenshots/ExampleWindowsCloudundancyIniFile.png)

Here is the example Windows Cloudundancy .ini file printed by program mode `example-windows-ini-file`:

```
[DestinationFolders]
# Cloud-redundant backups to Google's cloud, Microsoft's cloud, and GitHub's cloud
C:\GoogleDrive\CloudundancyBackups
C:\OneDrive\CloudundancyBackups
C:\GitHubRepos\CloudundancyBackups

# Device-redundant backups to USB drive D: and USB drive E:
D:\CloudundancyBackups
E:\CloudundancyBackups

[SourceFilesAndFolders]
# In the [SourceFilesAndFolders] section, the format of lines is "<SourceFileOrFolderPath> -> <RelativeDestinationFolderPath>"

# Critical files to backup
C:\CriticalFiles\KeePassFile.kdbx -> .
C:\CriticalFiles\PersonalFinancesSpreadsheet.xlsx -> .
C:\VS2019\Common7\IDE\VC\Snippets\1033\Visual C++\C++Snippets.snippet                              -> Snippets
C:\VS2019\Common7\IDE\Extensions\Microsoft\Python\Core\Snippets\1033\Python\PythonSnippets.snippet -> Snippets
C:\VS2019\VC#\Snippets\1033\Visual C#\CSharpSnippets.snippet                                       -> Snippets

# Critical folders to backup
# Source folder paths ending in a '\' or '/' character are interpretted as folders and not files to be backed up
C:\Users\UserName\Documents\WindowsPowerShell\ -> PowerShell
C:\Jenkins\jobs\ -> Jenkins\jobs

[FileSubpathsToNotCopy]
# In the [FileSubpathsToNotCopy] section, case-insensitive file path substrings
# can be listed so as to not back up files matching the listed case-insensitive file path substrings

# PowerShell Modules folder to not backup as PowerShell modules can be easily reinstalled
PowerShell\Modules\

# Jenkins jobs folder file paths to not backup so as to only backup Jenkins job config.xml files
\builds\
\cobertura\
\lastStable
\lastSuccessful\
\atomic
nextBuildNumber
scm-polling.log
```

### Linux Jenkins Jobs Which Compile, clang-tidy, AddressSanitize, UndefinedBehaviorSanitize, and ThreadSanitize Cloudundancy

A Jenkins Blue Ocean build pipeline builds the following Cloudundancy Jenkins jobs on Fedora 33:

10/30/2020 work in progress.

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
