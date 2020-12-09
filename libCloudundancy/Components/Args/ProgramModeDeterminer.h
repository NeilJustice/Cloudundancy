#pragma once

class ProgramModeDeterminer
{
public:
   virtual ProgramMode DetermineProgramMode(
      bool isCopyFilesToMultipleFoldersMode,
      bool is7ZipMode,
      bool isExampleLinuxIniFileMode,
      bool isExampleWindowsIniFileMode) const;
   virtual ~ProgramModeDeterminer() = default;
};
