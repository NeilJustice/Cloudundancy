#include "pch.h"
#include "libCloudundancy/Components/Args/ProgramModeDeterminer.h"

TESTS(ProgramModeDeterminerTests)
FACTS(DetermineProgramMode_ReturnsProgramModeCorrespondingToProgramModeBool)
AFACT(DetermineProgramMode_AllFourBoolsAreFalse_ThrowsInvalidArgument)
EVIDENCE

ProgramModeDeterminer _programModeDeterminer;

TEST5X5(DetermineProgramMode_ReturnsProgramModeCorrespondingToProgramModeBool,
   bool isCopyFileToFilesToMultipleFoldersMode,
   bool is7ZipMode,
   bool isExampleLinuxIniFileMode,
   bool isExampleWindowsIniFileMode,
   ProgramMode expectedReturnValue,
   true, false, false, false, ProgramMode::CopyFileToFilesAndFoldersToMultipleFolders,
   false, true, false, false, ProgramMode::SevenZip,
   false, false, true, false, ProgramMode::ExampleLinuxIniFile,
   false, false, false, true, ProgramMode::ExampleWindowsIniFile)
{
   const ProgramMode programMode = _programModeDeterminer.DetermineProgramMode(
      isCopyFileToFilesToMultipleFoldersMode,
      is7ZipMode,
      isExampleLinuxIniFileMode,
      isExampleWindowsIniFileMode);
   ARE_EQUAL(expectedReturnValue, programMode);
}

TEST(DetermineProgramMode_AllFourBoolsAreFalse_ThrowsInvalidArgument)
{
   THROWS_EXCEPTION(_programModeDeterminer.DetermineProgramMode(false, false, false, false),
      invalid_argument, "ProgramModeDeterminer::DetermineProgramMode(bool, bool, bool, bool): All four ProgramMode bools are unexpectedly false");
}

RUN_TESTS(ProgramModeDeterminerTests)
