#include "pch.h"
#include "libCloudundancy/Components/Args/ProgramModeDeterminer.h"

ProgramMode ProgramModeDeterminer::DetermineProgramMode(
   bool isBackupFilesAndFoldersMode,
   bool isBackupFilesAndFoldersTo7zFileMode,
   bool isExampleLinuxIniFileMode,
   bool isExampleWindowsIniFileMode) const
{
   if (isBackupFilesAndFoldersMode)
   {
      return ProgramMode::BackupFilesAndFolders;
   }
   if (isBackupFilesAndFoldersTo7zFileMode)
   {
      return ProgramMode::BackupFilesAndFoldersTo7zFile;
   }
   if (isExampleLinuxIniFileMode)
   {
      return ProgramMode::ExampleLinuxIniFile;
   }
   if (isExampleWindowsIniFileMode)
   {
      return ProgramMode::ExampleWindowsIniFile;
   }
   throw invalid_argument("ProgramModeDeterminer::DetermineProgramMode(bool, bool, bool, bool): All four ProgramMode bools are unexpectedly false");
}
