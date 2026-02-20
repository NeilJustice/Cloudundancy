#pragma once

class ProgramModeDeterminer
{
public:
   virtual ~ProgramModeDeterminer() = default;

   virtual ProgramMode DetermineProgramMode(
      bool isCopyFileToFilesToMultipleFoldersMode,
      bool is7ZipMode,
      bool isExampleLinuxIniFileMode,
      bool isExampleWindowsIniFileMode) const;
};
