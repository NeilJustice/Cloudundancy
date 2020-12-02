#include "pch.h"
#include "libCloudundancy/Components/Args/CloudundancyArgsParser.h"
#include "libCloudundancyTests/Components/Args/MetalMock/ProgramModeDeterminerMock.h"
#include "libCloudundancyTests/UtilityComponents/Docopt/MetalMock/DocoptParserMock.h"
#include "libCloudundancyTests/Components/FileSystem/MetalMock/FileSystemMock.h"

TESTS(CloudundancyArgsParserTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(ParseStringArgs_CallsDocoptParserForEachField_ReturnsCloudundancyArgs)
EVIDENCE

CloudundancyArgsParser _cloudundancyArgsParser;
// Constant Components
DocoptParserMock* _docoptParserMock = nullptr;
FileSystemMock* _fileSystemMock = nullptr;
ProgramModeDeterminerMock* _programModeDeterminerMock = nullptr;

STARTUP
{
   // Constant Components
   _cloudundancyArgsParser._docoptParser.reset(_docoptParserMock = new DocoptParserMock);
   _cloudundancyArgsParser._fileSystem.reset(_fileSystemMock = new FileSystemMock);
   _cloudundancyArgsParser._programModeDeterminer.reset(_programModeDeterminerMock = new ProgramModeDeterminerMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   CloudundancyArgsParser cloudundancyArgsParser;
   DELETE_TO_ASSERT_NEWED(cloudundancyArgsParser._docoptParser);
   DELETE_TO_ASSERT_NEWED(cloudundancyArgsParser._fileSystem);
   DELETE_TO_ASSERT_NEWED(_cloudundancyArgsParser._programModeDeterminer);
}

TEST(ParseStringArgs_CallsDocoptParserForEachField_ReturnsCloudundancyArgs)
{
   const map<string, docopt::Value> docoptArgs = ZenUnit::RandomMap<string, docopt::Value>();
   _docoptParserMock->ParseArgsMock.Return(docoptArgs);

   const bool isExampleLinuxIniFileMode = ZenUnit::Random<bool>();
   const bool isExampleWindowsIniFileMode = ZenUnit::Random<bool>();
   const bool isBackupFilesAndFoldersMode = ZenUnit::Random<bool>();
   const bool isBackupFilesAndFoldersTo7zFileMode = ZenUnit::Random<bool>();
   _docoptParserMock->GetRequiredBoolMock.ReturnValues(
      isExampleLinuxIniFileMode, isExampleWindowsIniFileMode, isBackupFilesAndFoldersMode, isBackupFilesAndFoldersTo7zFileMode);

   const ProgramMode programMode = _programModeDeterminerMock->DetermineProgramModeMock.ReturnRandom();

   const string iniFilePath = _docoptParserMock->GetRequiredStringMock.ReturnRandom();

   const string sevenZipIniFilePath = ZenUnit::Random<string>();
   const string backupStagingFolderPath = ZenUnit::Random<string>();
   _docoptParserMock->GetProgramModeSpecificRequiredStringMock.ReturnValues(sevenZipIniFilePath, backupStagingFolderPath);

   _fileSystemMock->ThrowIfFilePathIsNotEmptyAndDoesNotExistMock.Expect();

   const vector<string> stringArgs = ZenUnit::RandomVector<string>();
   //
   const CloudundancyArgs args = _cloudundancyArgsParser.ParseStringArgs(stringArgs);
   //
   METALMOCK(_docoptParserMock->ParseArgsMock.CalledOnceWith(CloudundancyArgs::CommandLineUsage, stringArgs));
   METALMOCK(_docoptParserMock->GetRequiredBoolMock.CalledAsFollows(
   {
      { docoptArgs, "example-linux-ini-file" },
      { docoptArgs, "example-windows-ini-file" },
      { docoptArgs, "backup-files-and-folders" },
      { docoptArgs, "backup-files-and-folders-to-7z-file" }
   }));
   METALMOCK(_programModeDeterminerMock->DetermineProgramModeMock.CalledOnceWith(
      isExampleLinuxIniFileMode, isExampleWindowsIniFileMode, isBackupFilesAndFoldersMode, isBackupFilesAndFoldersTo7zFileMode));
   METALMOCK(_docoptParserMock->GetRequiredStringMock.CalledOnceWith(docoptArgs, "--ini-file"));
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
   CloudundancyArgs expectedArgs;
   expectedArgs.programMode = programMode;
   expectedArgs.iniFilePath = iniFilePath;
   expectedArgs.backupStagingFolderPath = backupStagingFolderPath;
   expectedArgs.sevenZipIniFilePath = sevenZipIniFilePath;
   ARE_EQUAL(expectedArgs, args);
}

RUN_TESTS(CloudundancyArgsParserTests)
