#include "pch.h"
#include "libCloudundancy/Components/Args/ProgramModeDeterminer.h"

ProgramMode ProgramModeDeterminer::DetermineProgramMode(
   bool isCopyFileFastsToMultipleFoldersMode,
   bool is7ZipMode,
   bool isExampleLinuxIniFileMode,
   bool isExampleWindowsIniFileMode) const
{
   if (isCopyFileFastsToMultipleFoldersMode)
   {
      return ProgramMode::CopyFileFastsAndFoldersToMultipleFolders;
   }
   if (is7ZipMode)
   {
      return ProgramMode::SevenZip;
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
