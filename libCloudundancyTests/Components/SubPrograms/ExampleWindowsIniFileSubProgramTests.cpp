#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/ExampleWindowsIniFileSubProgram.h"

TESTS(ExampleWindowsIniFileSubProgramTests)
AFACT(Run_PrintsExampleWindowsIniFile_Returns0)
EVIDENCE

ExampleWindowsIniFileSubProgram _exampleWindowsIniFileSubProgram;
// Base Constant Components
Utils::ConsoleMock* _consoleMock = nullptr;

STARTUP
{
   // Base Constant Components
   _exampleWindowsIniFileSubProgram._console.reset(_consoleMock = new Utils::ConsoleMock);
}

TEST(Run_PrintsExampleWindowsIniFile_Returns0)
{
   _consoleMock->WriteLineMock.Expect();
   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   const int exitCode = _exampleWindowsIniFileSubProgram.Run(args);
   //
   const string expectedExampleWindowsIniFileText =
R"(
Example Windows Cloudundancy .ini file:

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

[FileSubpathsToNotCopy]
# In the [FileSubpathsToNotCopy] section, case-sensitive file path substrings can be listed one per line

# PowerShell Modules folder to not copy, as PowerShell modules can be easily reinstalled
PowerShell\Modules\
)";
   METALMOCK(_consoleMock->WriteLineMock.CalledOnceWith(expectedExampleWindowsIniFileText));
   IS_ZERO(exitCode);
}

RUN_TESTS(ExampleWindowsIniFileSubProgramTests)
