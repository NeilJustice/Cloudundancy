# Cloudundancy

[![Standard](https://img.shields.io/badge/c%2B%2B-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B17) [![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

Cloudundancy is a C++ command line program which quickly copies a configurable list of files and folders to a configurable list of destination folders to achieve cloud-redundant and device-redundant backups of business-critical files.

For example, in a Cloudundancy.ini file, destination folders could be configured to be a Google Drive folder, a Microsoft OneDrive folder, and two USB drives to achieve the peace of mind that comes with having cloud-redundant and device-redundant backups of business-critical files.

On Windows, Google Drive and Microsoft OneDrive folders automatically upload their contents to their respective clouds. On Linux, command line invocations of Google Drive and Microsoft OneDrive command line utilities would have to be added after a command line which runs Cloudundancy.

|Cloudundancy Build Type|Build Status|
|----------|------------|
|Travis CI Linux (Clang 7.0.0 and GCC 7.5.0)|<a href="https://travis-ci.org/NeilJustice/Cloudundancy"><img src="https://travis-ci.org/NeilJustice/Cloudundancy.svg?branch=main"/></a>|
|AppVeyor Windows (Visual Studio 2019 x64)|<a href="https://ci.appveyor.com/project/NeilJustice/Cloudundancy"><img src="https://ci.appveyor.com/api/projects/status/ygwr3rb9spwhy4u0?svg=true"/></a>|
|Code Coverage For The GCC 7.5.0 Release Build|[![codecov](https://codecov.io/gh/NeilJustice/Cloudundancy/branch/main/graph/badge.svg?token=ruXbRPB1CQ)](https://codecov.io/gh/NeilJustice/Cloudundancy)|

Cloudundancy is rigorously unit tested with <a href="https://github.com/NeilJustice/ZenUnitAndMetalMock">ZenUnit and MetalMock</a>.

* [Command Line Usage](#command-line-usage)
* [Program Modes](#program-modes)
   * [backup-files-to-multiple-folders](#backup-files-to-multiple-folders)
   * [7zip-files-then-copy-the-7zip-file-to-multiple-folders](#7zip-files-then-copy-the-7zip-file-to-multiple-folders)
   * [example-linux-ini-file](#print-example-linux-ini-file)
   * [example-windows-ini-file](#print-example-windows-ini-file)
* [Linux Jenkins Jobs Which Build, clang-tidy, AddressSanitize, and UndefinedBehaviorSanitize Cloudundancy](#linux-jenkins-jobs-which-build-clang-tidy-addresssanitize-undefinedbehaviorsanitize-cloudundancy)
* [Windows Jenkins Jobs Which Build Cloudundancy](#windows-jenkins-jobs-which-build-cloudundancy)
* [4 Commands To Build Cloudundancy From Source On Linux With Clang](#4-commands-to-build-cloudundancy-from-source-on-linux-with-clang)
* [4 Commands To Build Cloudundancy From Source On Windows With Visual Studio 2019](#4-commands-to-build-cloudundancy-from-source-on-windows-with-visual-studio-2019)
* [Cloudundancy Future Features Roadmap](#cloudundancy-future-features-roadmap)

## Command Line Usage

```
Cloudundancy v0.9.0 - Maker of cloud-redundant and device-redundant file backups
https://github.com/NeilJustice/Cloudundancy

Usage:
   Cloudundancy backup-files-to-multiple-folders --ini-file=<CloudundancyIniFilePath> [--delete-destination-folders-first]
   Cloudundancy 7zip-files-then-copy-the-7zip-file-to-multiple-folders
      --ini-file-to-copy-files-to-7zip-staging-folder=<CloudundancyIniFilePath>
      --7zip-staging-folder=<FolderPath>
      --ini-file-to-copy-7zip-file-from-staging-folder-to-multiple-folders=<CloudundancyIniFilePath>
   Cloudundancy print-example-linux-ini-file
   Cloudundancy print-example-windows-ini-file
```

Cloudundancy command line arguments are parsed using the excellent single-header library [docopt.cpp](https://github.com/docopt/docopt.cpp):



## Program Modes

### backup-files-to-multiple-folders

Cloudundancy program mode `backup-files-to-multiple-folders` copies files and folders listed in a Cloudundancy.ini file to multiple destination folders.

12/03/2020: Work in progress.

### 7zip-files-then-copy-the-7zip-file-to-multiple-folders

12/03/2020: Work in progress.

### print-example-linux-ini-file

12/03/2020: Work in progress.

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

### Linux Jenkins Jobs Which Build, clang-tidy, AddressSanitize, and UndefinedBehaviorSanitize Cloudundancy

A Jenkins Blue Ocean build pipeline builds the following Cloudundancy Jenkins jobs on Fedora 33 with Clang and GCC:

12/09/2020: Work in progress.

### Windows Jenkins Jobs Which Build Cloudundancy

A Jenkins Blue Ocean build pipeline builds the following Cloudundancy Jenkins jobs on Windows 10 with Visual Studio 2019:

![Cloudundancy Windows Jenkins Jobs](Screenshots/CloudundancyWindowsJenkinsJobs.png)

## 4 Commands To Build Cloudundancy From Source On Linux With Clang

```
git clone https://github.com/NeilJustice/Cloudundancy
cd Cloudundancy && mkdir Release && cd Release
CXX=clang++ cmake .. -DCMAKE_BUILD_TYPE=Release
sudo cmake --build . --target install # Installs binary Cloudundany to /usr/local/bin/Cloudundancy
```

## 4 Commands To Build Cloudundancy From Source On Windows With Visual Studio 2019

```
git clone https://github.com/NeilJustice/Cloudundancy
cd Cloudundancy
cmake . -G"Visual Studio 16 2019" -A x64 -DCMAKE_INSTALL_PREFIX=C:\bin
cmake --build . --config Release --target install # Installs Cloudundancy.exe to C:\bin\Cloudundancy.exe
```

![Cloudundancy.exe on Windows](Screenshots/CloudundancyDotExe.png)

## Cloudundancy Future Features Roadmap

|Future Cloudundancy Feature|Estimated Delivery Quarter|
|---------------------------|--------------------------------------|
|`7zip-files-then-copy-the-7zip-file-to-multiple-folders` working on Linux|Q4 2020|
|SonarCloud static analysis badge|Q1 2021|
|Coverity static analysis badge|Q1 2021|
|Parallel copying to multiple destination folders|Q2 2021|
