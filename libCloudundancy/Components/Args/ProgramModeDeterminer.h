#pragma once

class ProgramModeDeterminer
{
public:
   virtual ProgramMode DetermineProgramMode(
      bool isPrintExampleLinuxIniFileMode,
      bool isPrintExampleWindowsIniFileMode,
      bool isBackupFilesToMultipleFoldersMode,
      bool isBackupFilesAndFoldersTo7zFileMode) const;
   virtual ~ProgramModeDeterminer() = default;
};
