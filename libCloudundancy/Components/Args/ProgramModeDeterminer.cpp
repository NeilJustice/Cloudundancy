#include "pch.h"
#include "libCloudundancy/Components/Args/ProgramModeDeterminer.h"

ProgramMode ProgramModeDeterminer::DetermineProgramMode(
   bool isBackupFilesToMultipleFoldersMode,
   bool is7ZipBackupMode,
   bool isPrintExampleLinuxIniFileMode,
   bool isPrintExampleWindowsIniFileMode) const
{
   if (isBackupFilesToMultipleFoldersMode)
   {
      return ProgramMode::BackupFilesAndFolders;
   }
   if (is7ZipBackupMode)
   {
      return ProgramMode::BackupFilesAndFoldersTo7ZipFile;
   }
   if (isPrintExampleLinuxIniFileMode)
   {
      return ProgramMode::PrintExampleLinuxIniFile;
   }
   if (isPrintExampleWindowsIniFileMode)
   {
      return ProgramMode::PrintExampleWindowsIniFile;
   }
   throw invalid_argument("ProgramModeDeterminer::DetermineProgramMode(bool, bool, bool, bool): All four ProgramMode bools are unexpectedly false");
}
