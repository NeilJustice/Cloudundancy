#pragma once

class ProgramModeDeterminer
{
public:
   virtual ProgramMode DetermineProgramMode(
      bool isCopyFilesToMultipleFoldersMode,
      bool is7ZipMode,
      bool isPrintExampleLinuxIniFileMode,
      bool isPrintExampleWindowsIniFileMode) const;
   virtual ~ProgramModeDeterminer() = default;
};
