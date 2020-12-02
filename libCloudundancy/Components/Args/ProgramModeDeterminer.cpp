#include "pch.h"
#include "libCloudundancy/Components/Args/ProgramModeDeterminer.h"

ProgramMode ProgramModeDeterminer::DetermineProgramMode(
   bool isPrintExampleLinuxIniFileMode,
   bool isPrintExampleWindowsIniFileMode,
   bool isBackupFilesAndFoldersMode,
   bool isBackupFilesAndFoldersTo7zFileMode) const
{
   if (isPrintExampleLinuxIniFileMode)
   {
      return ProgramMode::PrintExampleLinuxIniFile;
   }
   if (isPrintExampleWindowsIniFileMode)
   {
      return ProgramMode::PrintExampleWindowsIniFile;
   }
   if (isBackupFilesAndFoldersMode)
   {
      return ProgramMode::BackupFilesAndFolders;
   }
   if (isBackupFilesAndFoldersTo7zFileMode)
   {
      return ProgramMode::BackupFilesAndFoldersTo7zFile;
   }
   throw invalid_argument("ProgramModeDeterminer::DetermineProgramMode(bool, bool, bool, bool): All four ProgramMode bools are unexpectedly false");
}
