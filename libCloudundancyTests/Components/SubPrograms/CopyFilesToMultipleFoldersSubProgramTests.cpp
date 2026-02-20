#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/CopyFilesToMultipleFoldersSubProgram.h"
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"
#include "libCloudundancyTests/Components/FileSystem/MetalMock/CloudundancyFileCopierMock.h"

TESTS(CopyFileToFilesToMultipleFoldersSubProgramTests)
AFACT(Run_DoesSo)
EVIDENCE

CopyFileToFilesToMultipleFoldersSubProgram _copyFilesToMultipleFoldersSubProgram;
// Base Constant Components
Utils::ConsoleMock* p_consoleMock = nullptr;
// Constant Components
CloudundancyFileCopierMock* _cloudundancyFileCopierMock = nullptr;
// Mutable Fields
CloudundancyArgs p_args;

STARTUP
{
   // Base Constant Components
   _copyFilesToMultipleFoldersSubProgram.p_console.reset(p_consoleMock = new Utils::ConsoleMock);
   // Constant Components
   _copyFilesToMultipleFoldersSubProgram._cloudundancyFileCopier.reset(_cloudundancyFileCopierMock = new CloudundancyFileCopierMock);
   // Mutable Fields
   _copyFilesToMultipleFoldersSubProgram.p_args = p_args = ZenUnit::Random<CloudundancyArgs>();
}

TEST(Run_DoesSo)
{
   _cloudundancyFileCopierMock->CopyFilteredFilesAndFoldersToDestinationFoldersMock.Expect();
   p_consoleMock->WriteLineColorMock.Expect();
   //
   const int exitCode = _copyFilesToMultipleFoldersSubProgram.Run();
   //
   METALMOCKTHEN(_cloudundancyFileCopierMock->CopyFilteredFilesAndFoldersToDestinationFoldersMock.CalledOnceWith(
      p_args.iniInputFilePath, p_args.deleteDestinationFoldersFirst)).Then(
   METALMOCKTHEN(p_consoleMock->WriteLineColorMock.CalledOnceWith(
      "\n[Cloudundancy] OverallBackupResult: Successfully copied all [SourceFilesAndFolders] to all [DestinationFolders]",
      Utils::Color::Green)));
   IS_ZERO(exitCode);
}

RUN_TESTS(CopyFileToFilesToMultipleFoldersSubProgramTests)
