#include "pch.h"
#include "libCloudundancy/Components/Args/ProgramModeDeterminer.h"

TESTS(ProgramModeDeterminerTests)
FACTS(DetermineProgramMode_ReturnsProgramModeCorrespondingToProgramModeBool)
AFACT(DetermineProgramMode_AllFourBoolsAreFalse_ThrowsInvalidArgument)
EVIDENCE

ProgramModeDeterminer _programModeDeterminer;

TEST5X5(DetermineProgramMode_ReturnsProgramModeCorrespondingToProgramModeBool,
   bool isExampleLinuxIniFileMode,
   bool isExampleWindowsIniFileMode,
   bool isBackupFilesAndFoldersMode,
   bool is7ZipBackupMode,
   ProgramMode expectedReturnValue,
   true, false, false, false, ProgramMode::ExampleLinuxIniFile,
   false, true, false, false, ProgramMode::ExampleWindowsIniFile,
   false, false, true, false, ProgramMode::BackupFilesAndFolders,
   false, false, false, true, ProgramMode::BackupFilesAndFoldersTo7zFile)
{
   const ProgramMode programMode = _programModeDeterminer.DetermineProgramMode(
      isExampleLinuxIniFileMode, isExampleWindowsIniFileMode, isBackupFilesAndFoldersMode, is7ZipBackupMode);
   //
   ARE_EQUAL(expectedReturnValue, programMode);
}

TEST(DetermineProgramMode_AllFourBoolsAreFalse_ThrowsInvalidArgument)
{
   THROWS_EXCEPTION(_programModeDeterminer.DetermineProgramMode(false, false, false, false),
      invalid_argument, "ProgramModeDeterminer::DetermineProgramMode(bool, bool, bool, bool): All four ProgramMode bools are unexpectedly false");
}

RUN_TESTS(ProgramModeDeterminerTests)
