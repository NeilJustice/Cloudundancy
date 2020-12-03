#include "pch.h"
#include "libCloudundancy/Components/Args/CloudundancyArgsParser.h"
#include "libCloudundancyTests/Components/Args/MetalMock/ProgramModeDeterminerMock.h"

TESTS(CloudundancyArgsParserTests)
AFACT(DefaultConstructor_NewsComponents)
FACTS(ParseStringArgs_CallsDocoptParserForEachField_ReturnsCloudundancyArgs)
EVIDENCE

CloudundancyArgsParser _cloudundancyArgsParser;
// Constant Components
ConsoleMock* _consoleMock = nullptr;
DocoptParserMock* _docoptParserMock = nullptr;
FileSystemMock* _fileSystemMock = nullptr;
ProcessRunnerMock* _processRunnerMock = nullptr;
ProgramModeDeterminerMock* _programModeDeterminerMock = nullptr;

STARTUP
{
   // Constant Components
   _cloudundancyArgsParser._console.reset(_consoleMock = new ConsoleMock);
   _cloudundancyArgsParser._docoptParser.reset(_docoptParserMock = new DocoptParserMock);
   _cloudundancyArgsParser._fileSystem.reset(_fileSystemMock = new FileSystemMock);
   _cloudundancyArgsParser._processRunner.reset(_processRunnerMock = new ProcessRunnerMock);
   _cloudundancyArgsParser._programModeDeterminer.reset(_programModeDeterminerMock = new ProgramModeDeterminerMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   CloudundancyArgsParser cloudundancyArgsParser;
   // Constant Components
   DELETE_TO_ASSERT_NEWED(cloudundancyArgsParser._console);
   DELETE_TO_ASSERT_NEWED(cloudundancyArgsParser._docoptParser);
   DELETE_TO_ASSERT_NEWED(cloudundancyArgsParser._fileSystem);
   DELETE_TO_ASSERT_NEWED(cloudundancyArgsParser._processRunner);
   DELETE_TO_ASSERT_NEWED(cloudundancyArgsParser._programModeDeterminer);
}

TEST2X2(ParseStringArgs_CallsDocoptParserForEachField_ReturnsCloudundancyArgs,
   bool isBackupFilesAndFoldersTo7zFileMode, bool expectRun7zToConfirm7zIsInThePath,
   false, false,
   true, true)
{
   const map<string, docopt::Value> docoptArgs = ZenUnit::RandomMap<string, docopt::Value>();
   _docoptParserMock->ParseArgsMock.Return(docoptArgs);

   const bool isPrintExampleLinuxIniFileMode = ZenUnit::Random<bool>();
   const bool isPrintExampleWindowsIniFileMode = ZenUnit::Random<bool>();
   const bool isBackupFilesToMultipleFoldersMode = ZenUnit::Random<bool>();
   _docoptParserMock->GetRequiredBoolMock.ReturnValues(
      isPrintExampleLinuxIniFileMode,
      isPrintExampleWindowsIniFileMode,
      isBackupFilesToMultipleFoldersMode,
      isBackupFilesAndFoldersTo7zFileMode);

   const ProgramMode programMode = _programModeDeterminerMock->DetermineProgramModeMock.ReturnRandom();

   const string iniFilePath = _docoptParserMock->GetRequiredStringMock.ReturnRandom();

   const bool deleteDestinationFoldersFirst = _docoptParserMock->GetOptionalBoolMock.ReturnRandom();

   const string sevenZipIniFilePath = ZenUnit::Random<string>();
   const string backupStagingFolderPath = ZenUnit::Random<string>();
   _docoptParserMock->GetProgramModeSpecificRequiredStringMock.ReturnValues(sevenZipIniFilePath, backupStagingFolderPath);

   _fileSystemMock->ThrowIfFilePathIsNotEmptyAndDoesNotExistMock.Expect();

   if (expectRun7zToConfirm7zIsInThePath)
   {
      _consoleMock->WriteLineMock.Expect();
      _processRunnerMock->FailFastRunMock.ReturnRandom();
   }

   const vector<string> stringArgs = ZenUnit::RandomVector<string>();
   //
   const CloudundancyArgs args = _cloudundancyArgsParser.ParseStringArgs(stringArgs);
   //
   METALMOCK(_docoptParserMock->ParseArgsMock.CalledOnceWith(CloudundancyArgs::CommandLineUsage, stringArgs));
   METALMOCK(_docoptParserMock->GetRequiredBoolMock.CalledAsFollows(
   {
      { docoptArgs, "print-example-linux-ini-file" },
      { docoptArgs, "print-example-windows-ini-file" },
      { docoptArgs, "backup-files-to-multiple-folders" },
      { docoptArgs, "backup-files-and-folders-to-7z-file" }
   }));
   METALMOCK(_programModeDeterminerMock->DetermineProgramModeMock.CalledOnceWith(
      isPrintExampleLinuxIniFileMode,
      isPrintExampleWindowsIniFileMode,
      isBackupFilesToMultipleFoldersMode,
      isBackupFilesAndFoldersTo7zFileMode));
   METALMOCK(_docoptParserMock->GetRequiredStringMock.CalledOnceWith(docoptArgs, "--ini-file"));
   METALMOCK(_docoptParserMock->GetOptionalBoolMock.CalledOnceWith(docoptArgs, "--delete-destination-folders-first"));
   METALMOCK(_docoptParserMock->GetProgramModeSpecificRequiredStringMock.CalledAsFollows(
   {
      { docoptArgs, static_cast<int>(programMode), static_cast<int>(ProgramMode::BackupFilesAndFoldersTo7zFile), "--7z-ini-file" },
      { docoptArgs, static_cast<int>(programMode), static_cast<int>(ProgramMode::BackupFilesAndFoldersTo7zFile), "--backup-staging-folder" }
   }));
   METALMOCK(_fileSystemMock->ThrowIfFilePathIsNotEmptyAndDoesNotExistMock.CalledAsFollows(
   {
      { iniFilePath },
      { sevenZipIniFilePath }
   }));
   if (expectRun7zToConfirm7zIsInThePath)
   {
      METALMOCK(_consoleMock->WriteLineMock.CalledAsFollows(
      {
         { "[Cloudundancy] Running 7z to confirm 7z is present on the PATH" },
         { "[Cloudundancy] 7z ran and exited with code 0 and is therefore confirmed to be present on the PATH\n" }
      }));
      METALMOCK(_processRunnerMock->FailFastRunMock.CalledOnceWith("7z", "", false));
   }
   CloudundancyArgs expectedArgs;
   expectedArgs.programMode = programMode;
   expectedArgs.iniFilePath = iniFilePath;
   expectedArgs.deleteDestinationFoldersFirst = deleteDestinationFoldersFirst;
   expectedArgs.backupStagingFolderPath = backupStagingFolderPath;
   expectedArgs.sevenZipIniFilePath = sevenZipIniFilePath;
   ARE_EQUAL(expectedArgs, args);
}

RUN_TESTS(CloudundancyArgsParserTests)
