#include "pch.h"
#include "libCloudundancy/Components/Args/ProgramModeDeterminer.h"

TESTS(ProgramModeDeterminerTests)
FACTS(DetermineProgramMode_ReturnsProgramModeCorrespondingToProgramModeBool)
AFACT(DetermineProgramMode_AllFourBoolsAreFalse_ThrowsInvalidArgument)
EVIDENCE

ProgramModeDeterminer _programModeDeterminer;

TEST5X5(DetermineProgramMode_ReturnsProgramModeCorrespondingToProgramModeBool,
   bool isBackupFilesToMultipleFoldersMode,
   bool is7ZipBackupMode,
   bool isPrintExampleLinuxIniFileMode,
   bool isPrintExampleWindowsIniFileMode,
   ProgramMode expectedReturnValue,
   true, false, false, false, ProgramMode::BackupFilesAndFolders,
   false, true, false, false, ProgramMode::BackupFilesAndFoldersTo7zFile,
   false, false, true, false, ProgramMode::PrintExampleLinuxIniFile,
   false, false, false, true, ProgramMode::PrintExampleWindowsIniFile)
{
   const ProgramMode programMode = _programModeDeterminer.DetermineProgramMode(
      isBackupFilesToMultipleFoldersMode,
      is7ZipBackupMode,
      isPrintExampleLinuxIniFileMode,
      isPrintExampleWindowsIniFileMode);
   //
   ARE_EQUAL(expectedReturnValue, programMode);
}

TEST(DetermineProgramMode_AllFourBoolsAreFalse_ThrowsInvalidArgument)
{
   THROWS_EXCEPTION(_programModeDeterminer.DetermineProgramMode(false, false, false, false),
      invalid_argument, "ProgramModeDeterminer::DetermineProgramMode(bool, bool, bool, bool): All four ProgramMode bools are unexpectedly false");
}

RUN_TESTS(ProgramModeDeterminerTests)
