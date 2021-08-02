#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/CopyFilesToMultipleFoldersSubProgram.h"
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"
#include "libCloudundancyTests/Components/FileSystem/MetalMock/CloudundancyFileCopierMock.h"

TESTS(CopyFileFastsToMultipleFoldersSubProgramTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(Run_SetsArgs_CallsCopyFileFastsAndFoldersToMultipleDestinationFolders_Returns0)
EVIDENCE

CopyFileFastsToMultipleFoldersSubProgram _copyFilesToMultipleFoldersSubProgram;
// Base Constant Components
Utils::ConsoleMock* _consoleMock = nullptr;
// Constant Components
CloudundancyFileCopierMock* _cloudundancyFileCopierMock = nullptr;

STARTUP
{
   // Base Constant Components
   _copyFilesToMultipleFoldersSubProgram._console.reset(_consoleMock = new Utils::ConsoleMock);
   // Constant Components
   _copyFilesToMultipleFoldersSubProgram._cloudundancyFileCopier.reset(_cloudundancyFileCopierMock = new CloudundancyFileCopierMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   CopyFileFastsToMultipleFoldersSubProgram copyFilesAndFoldersToMultipleFoldersSubProgram;
   DELETE_TO_ASSERT_NEWED(copyFilesAndFoldersToMultipleFoldersSubProgram._cloudundancyFileCopier);
}

TEST(Run_SetsArgs_CallsCopyFileFastsAndFoldersToMultipleDestinationFolders_Returns0)
{
   _cloudundancyFileCopierMock->CopyFileFastsAndFoldersToMultipleDestinationFoldersMock.Expect();
   _consoleMock->WriteLineColorMock.Expect();

   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   const int exitCode = _copyFilesToMultipleFoldersSubProgram.Run(args);
   //
   METALMOCK(_cloudundancyFileCopierMock->CopyFileFastsAndFoldersToMultipleDestinationFoldersMock.CalledOnceWith(
      args.iniFilePath, args.deleteDestinationFoldersFirst));
   METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith(
      "\n[Cloudundancy] OverallBackupResult: Successfully copied all [SourceFilesAndFolders] to all [DestinationFolders]",
      Color::Green));
   IS_ZERO(exitCode);
}

RUN_TESTS(CopyFileFastsToMultipleFoldersSubProgramTests)
