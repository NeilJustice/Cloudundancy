#pragma once

class ProgramModeDeterminer
{
public:
   virtual ProgramMode DetermineProgramMode(
      bool isBackupFilesToMultipleFoldersMode,
      bool is7ZipBackupMode,
      bool isPrintExampleLinuxIniFileMode,
      bool isPrintExampleWindowsIniFileMode) const;
   virtual ~ProgramModeDeterminer() = default;
};
