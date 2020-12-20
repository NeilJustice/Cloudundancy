#include "pch.h"
#include "libCloudundancy/Components/SubPrograms/CopyFilesToMultipleFoldersSubProgram.h"
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"
#include "libCloudundancyTests/Components/FileSystem/MetalMock/CloudundancyFileCopierMock.h"

TESTS(CopyFilesToMultipleFoldersSubProgramTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(Run_SetsArgs_CallsCopyFilesAndFoldersToMultipleDestinationFolders_Returns0)
EVIDENCE

CopyFilesToMultipleFoldersSubProgram _copyFilesToMultipleFoldersSubProgram;
ConsoleMock* _consoleMock = nullptr;
CloudundancyFileCopierMock* _cloudundancyFileCopierMock = nullptr;

STARTUP
{
   _copyFilesToMultipleFoldersSubProgram._cloudundancyFileCopier.reset(
      _cloudundancyFileCopierMock = new CloudundancyFileCopierMock);
   _copyFilesToMultipleFoldersSubProgram._console.reset(_consoleMock = new ConsoleMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   CopyFilesToMultipleFoldersSubProgram copyFilesAndFoldersToMultipleFoldersSubProgram;
   DELETE_TO_ASSERT_NEWED(copyFilesAndFoldersToMultipleFoldersSubProgram._cloudundancyFileCopier);
}

TEST(Run_SetsArgs_CallsCopyFilesAndFoldersToMultipleDestinationFolders_Returns0)
{
   _cloudundancyFileCopierMock->CopyFilesAndFoldersToMultipleDestinationFoldersMock.Expect();
   _consoleMock->WriteLineColorMock.Expect();

   const CloudundancyArgs args = ZenUnit::Random<CloudundancyArgs>();
   //
   const int exitCode = _copyFilesToMultipleFoldersSubProgram.Run(args);
   //
   METALMOCK(_cloudundancyFileCopierMock->CopyFilesAndFoldersToMultipleDestinationFoldersMock.CalledOnceWith(
      args.iniFilePath, args.deleteDestinationFoldersFirst));
   METALMOCK(_consoleMock->WriteLineColorMock.CalledOnceWith(
      "\n[Cloudundancy] OverallBackupResult: Successfully copied all [SourceFilesAndFolders] to all [DestinationFolders]",
      Color::Green));
   IS_ZERO(exitCode);
}

RUN_TESTS(CopyFilesToMultipleFoldersSubProgramTests)
