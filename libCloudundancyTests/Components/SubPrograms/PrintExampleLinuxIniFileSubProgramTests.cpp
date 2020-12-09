#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/PrintExampleLinuxIniFileSubProgram.h"

TESTS(PrintExampleLinuxIniFileSubProgramTests)
AFACT(Run_PrintsExampleLinuxIniFile_Returns0)
EVIDENCE

PrintExampleLinuxIniFileSubProgram _printExampleLinuxIniFileSubProgram;
ConsoleMock* _consoleMock = nullptr;

STARTUP
{
   _printExampleLinuxIniFileSubProgram._console.reset(_consoleMock = new ConsoleMock);
}

TEST(Run_PrintsExampleLinuxIniFile_Returns0)
{
   _consoleMock->WriteLineMock.Expect();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   const int exitCode = _printExampleLinuxIniFileSubProgram.Run(args);
   //
   const string expectedExampleLinuxIniFileText =
R"(
Example Linux Cloudundancy .ini file:

[DestinationFolders]
# Cloud-redundant backups to Google's cloud and GitHub's cloud
~/GoogleDrive/CloudundancyBackups
~/GitHubRepos/CloudundancyBackups

# Device-redundant backups to ~/USBDriveA and ~/USBDriveB
~/USBDriveA
~/USBDriveB

[SourceFilesAndFolders]
# In the [SourceFilesAndFolders] section, the format of lines is "<SourceFileOrFolderPath> -> <RelativeDestinationFolderPath>"

# Critical files to backup
~/GoogleDrive/KeePassFile.kdbx -> .
~/GoogleDrive/PersonalFinancesSpreadsheet.xlsx -> .

# Critical directories to backup
Placeholder/Jenkins/jobs/ -> Jenkins/jobs

[FileSubpathsToNotCopy]
# In the [FileSubpathsToNotCopy] section, case-insensitive file path substrings
# can be listed so as to not back up files matching the listed case-insensitive file path substrings

# Jenkins jobs folder file paths to not backup so as to only backup Jenkins job config.xml files
/builds/
/cobertura/
/lastStable
/lastSuccessful/
/atomic
nextBuildNumber
)";
   METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(expectedExampleLinuxIniFileText));
   IS_ZERO(exitCode);
}

RUN_TESTS(PrintExampleLinuxIniFileSubProgramTests)
