#include "pch.h"
#include "libCloudundancy/Components/Args/ProgramModeDeterminer.h"

ProgramMode ProgramModeDeterminer::DetermineProgramMode(
   bool isExampleLinuxIniFileMode,
   bool isExampleWindowsIniFileMode,
   bool isBackupFilesAndFoldersMode,
   bool isBackupFilesAndFoldersTo7zFileMode) const
{
   if (isExampleLinuxIniFileMode)
   {
      return ProgramMode::ExampleLinuxIniFile;
   }
   if (isExampleWindowsIniFileMode)
   {
      return ProgramMode::ExampleWindowsIniFile;
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
