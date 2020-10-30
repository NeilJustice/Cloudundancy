#pragma once

class ProgramModeDeterminer
{
public:
   virtual ProgramMode DetermineProgramMode(
      bool isExampleLinuxIniFileMode,
      bool isExampleWindowsIniFileMode,
      bool isBackupFilesAndFoldersMode,
      bool isBackupFilesAndFoldersTo7zFileMode) const;
   virtual ~ProgramModeDeterminer() = default;
};
