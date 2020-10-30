#pragma once

class ProgramModeDeterminer
{
public:
   virtual ProgramMode DetermineProgramMode(
      bool isBackupFilesAndFoldersMode,
      bool isBackupFilesAndFoldersTo7zFileMode,
      bool isExampleLinuxIniFileMode,
      bool isExampleWindowsIniFileMode) const;
   virtual ~ProgramModeDeterminer() = default;
};
