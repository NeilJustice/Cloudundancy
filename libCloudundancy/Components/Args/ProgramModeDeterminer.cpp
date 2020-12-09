#include "pch.h"
#include "libCloudundancy/Components/Args/ProgramModeDeterminer.h"

ProgramMode ProgramModeDeterminer::DetermineProgramMode(
   bool isCopyFilesToMultipleFoldersMode,
   bool is7ZipMode,
   bool isPrintExampleLinuxIniFileMode,
   bool isPrintExampleWindowsIniFileMode) const
{
   if (isCopyFilesToMultipleFoldersMode)
   {
      return ProgramMode::CopyFilesAndFoldersToMultipleFolders;
   }
   if (is7ZipMode)
   {
      return ProgramMode::SevenZip;
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
