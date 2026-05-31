#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/ExampleWindowsIniFileSubProgram.h"

int ExampleWindowsIniFileSubProgram::Run()
{
   const string exampleWindowsIniFileText =
R"(
Example Windows Cloudundancy .ini file:

[DestinationFolders]
# Cloud-redundancy backups to GoogleDrive and OneDrive
C:\GoogleDrive\CloudundancyBackups
C:\OneDrive\CloudundancyBackups

# Device-redundant backups to USB drives D: and E:
D:\CloudundancyBackups
E:\CloudundancyBackups

[SourceFilesAndFolders]
# In the [SourceFilesAndFolders] section, the line format is
# <SourceFileOrFolderPath> -> <RelativeDestinationFolderPath>

# Files to backup
C:\CriticalFiles\KeePassFile.kdbx -> .
C:\CriticalFiles\PersonalFinancesSpreadsheet.xlsx -> .
C:\VS2026\Common7\IDE\VC\Snippets\1033\Visual C++\C++Snippets.snippet                              -> Snippets
C:\VS2026\Common7\IDE\Extensions\Microsoft\Python\Core\Snippets\1033\Python\PythonSnippets.snippet -> Snippets
C:\VS2026\VC#\Snippets\1033\Visual C#\CSharpSnippets.snippet                                       -> Snippets

# Folders to backup
# Source folder paths ending in a '\' or '/' character are interpretted as folders instead of files
C:\Users\UserName\Documents\WindowsPowerShell\ -> PowerShell

[FileSubpathsToNotCopy]
PowerShell\Modules\
)";
   p_console->WriteLine(exampleWindowsIniFileText);
   return 0;
}
