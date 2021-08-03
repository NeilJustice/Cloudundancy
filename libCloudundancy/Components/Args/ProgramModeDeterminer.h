#pragma once

class ProgramModeDeterminer
{
public:
   virtual ProgramMode DetermineProgramMode(
      bool isCopyFileToFilesToMultipleFoldersMode,
      bool is7ZipMode,
      bool isExampleLinuxIniFileMode,
      bool isExampleWindowsIniFileMode) const;
   virtual ~ProgramModeDeterminer() = default;
};
