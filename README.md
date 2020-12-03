# Cloudundancy

[![Standard](https://img.shields.io/badge/c%2B%2B-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B17) [![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

Cloudundancy quickly copies a configurable list of files and folders to multiple destination folders to achieve cloud-redundant and device-redundant backups. For example, in a Cloudundancy.ini file, destination folder could be configured to be a Google Drive folder, a Microsoft OneDrive folder, and two USB drives to achieve the peace of mind that comes with having cloud-redundant and device-redundant backups of business-critical files.

|Build Type|Build Status|
|----------|------------|
|Travis CI Linux (Clang 7.0.0 and GCC 7.5.0)|<a href="https://travis-ci.org/NeilJustice/Cloudundancy"><img src="https://travis-ci.org/NeilJustice/Cloudundancy.svg?branch=main"/></a>|
|AppVeyor Windows (Visual Studio 2019 x64)|<a href="https://ci.appveyor.com/project/NeilJustice/Cloudundancy"><img src="https://ci.appveyor.com/api/projects/status/ygwr3rb9spwhy4u0?svg=true"/></a>|
|Code Coverage For The GCC 7.5.0 Release Build|[![codecov](https://codecov.io/gh/NeilJustice/Cloudundancy/branch/main/graph/badge.svg?token=ruXbRPB1CQ)](https://codecov.io/gh/NeilJustice/Cloudundancy)|

Cloudundancy is rigorously unit tested with <a href="https://github.com/NeilJustice/ZenUnitAndMetalMock">ZenUnit and MetalMock</a>.

* [Cloudundancy Command Line Usage](#cloudundancy-command-line-usage)
* [Cloudundancy Program Modes](#cloudundancy-program-modes)
   * [example-linux-ini-file](#print-example-linux-ini-file)
   * [example-windows-ini-file](#print-example-windows-ini-file)
   * [backup-files-to-multiple-folders](#backup-files-to-multiple-folders)
   * [7zip-files-then-copy-the-7zip-file-to-multiple-folders](#7zip-files-then-copy-the-7zip-file-to-multiple-folders)
* [Linux Jenkins Jobs Which Compile, clang-tidy, AddressSanitize, UndefinedBehaviorSanitize, and ThreadSanitize Cloudundancy](#linux-jenkins-jobs-which-compile-clang-tidy-addresssanitize-undefinedbehaviorsanitize-and-threadsanitize-cloudundancy)
* [Windows Jenkins Jobs Which Compile Cloudundancy](#windows-jenkins-jobs-which-compile-cloudundancy)
* [How To Build Cloudundancy From Source On Linux With Clang](#how-to-build-cloudundancy-from-source-on-linux-with-clang)
* [How To Build Cloudundancy From Source On Windows With Visual Studio 2019](#how-to-build-cloudundancy-from-source-on-windows-with-visual-studio-2019)
* [Cloudundancy Future Features Roadmap](#cloudundancy-future-features-roadmap)

## Cloudundancy Command Line Usage

```
Cloudundancy v0.9.0 - Maker of cloud-redundant and device-redundant file backups
https://github.com/NeilJustice/Cloudundancy - MIT License

Usage:
   Cloudundancy print-example-linux-ini-file
   Cloudundancy print-example-windows-ini-file
   Cloudundancy backup-files-to-multiple-folders --ini-file=<CloudundancyIniFilePath> [--delete-destination-folders-first]
   Cloudundancy 7zip-files-then-copy-the-7zip-file-to-multiple-folders
      --ini-file=<CloudundancyIniFilePath>
      --7z-ini-file=<CloudundancyIniFilePath>
      --backup-staging-folder=<FolderPath>
```

Cloudundancy command line arguments are parsed using the excellent single-header library [docopt.cpp](https://github.com/docopt/docopt.cpp):

![CloudundancyArgsParser](Screenshots/CloudundancyArgsParser.png)

## Cloudundancy Program Modes

### print-example-linux-ini-file

12/02/2020: Work in progress.

### print-example-windows-ini-file

Cloudundancy program mode `print-example-windows-ini-file` prints an example Windows Cloudundancy .ini file for showing how to achieve data security peace of mind by way of quintuple backups of critical files and folders to three clouds (Google Drive, OneDrive, GitHub) and two USB drives (D: and E:).

![Example Windows Cloudundancy .ini File](Screenshots/ExampleWindowsCloudundancyIniFile.png)

`print-example-windows-ini-file` in text format:

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

### backup-files-to-multiple-folders

Cloudundancy program mode `backup-files-to-multiple-folders` copies files and folders listed in a Cloudundancy.ini file to multiple destination folders.



### 7zip-files-then-copy-the-7zip-file-to-multiple-folders

12/02/2020: Work in progress.

### Linux Jenkins Jobs Which Build, clang-tidy, AddressSanitize, UndefinedBehaviorSanitize, and ThreadSanitize Cloudundancy

A Jenkins Blue Ocean build pipeline builds the following Cloudundancy Jenkins jobs on Fedora 33 to build Cloudundancy with Clang and GCC:

12/02/2020: Work in progress.

### Windows Jenkins Jobs Which Build Cloudundancy

A Jenkins Blue Ocean build pipeline builds the following Cloudundancy Jenkins jobs on Windows 10 to build Cloudundancy with Visual Studio 2019:

![Cloudundancy Windows Jenkins Jobs](Screenshots/CloudundancyWindowsJenkinsJobs.png)

## How To Build Cloudundancy From Source On Linux With Clang

```
git clone https://github.com/NeilJustice/Cloudundancy
cd Cloudundancy && mkdir Release && cd Release
CXX=clang++ cmake .. -DCMAKE_BUILD_TYPE=Release
sudo cmake --build . --target install
```

## How To Build Cloudundancy From Source On Windows With Visual Studio 2019

```
git clone https://github.com/NeilJustice/Cloudundancy
cd Cloudundancy
cmake . -G"Visual Studio 16 2019" -A x64 -DCMAKE_INSTALL_PREFIX=C:\bin
cmake --build . --config Release --target install
```

## Cloudundancy Future Features Roadmap

|Future Cloudundancy Feature|Estimated Delivery Quarter|
|-----------------------------------------------------------------|
|`7zip-files-then-copy-the-7zip-file-to-multiple-folders` working on Linux|Q4 2020|
|SonarCloud static analysis badge|Q1 2021|
|Coverity static analysis badge|Q1 2021|
|Parallel copying to multiple destination folders|Q2 2021|
