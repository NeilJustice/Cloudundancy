#include "pch.h"
#include "libCloudundancy/Components/CloudundancyArgsParser.h"

TESTS(CloudundancyArgsParserTests)
AFACT(DefaultConstructor_NewsComponents)
AFACT(ParseStringArgs_CallsDocoptParserForEachField_ReturnsCloudundancyArgs)
AFACT(GetProgramMode_IsBackupFilesAndFoldersModeIsTrue_ReturnsProgramModeBackupFilesAndFolders);
AFACT(GetProgramMode_Is7zBackupModeIsTrue_ReturnsProgramModeBackupFilesAndFolders)
AFACT(GetProgramMode_BothBoolsAreFalse_ThrowsInvalidArgument)
EVIDENCE

CloudundancyArgsParser _cloudundancyArgsParser;
// Constant Components
DocoptParserMock* _docoptParserMock = nullptr;
FileSystemMock* _fileSystemMock = nullptr;
// Function Callers
METALMOCK_NONVOID2_STATIC(ProgramMode, CloudundancyArgsParser, GetProgramMode, bool, bool)

STARTUP
{
   // Constant Components
   _cloudundancyArgsParser._docoptParser.reset(_docoptParserMock = new DocoptParserMock);
   _cloudundancyArgsParser._fileSystem.reset(_fileSystemMock = new FileSystemMock);
   // Function Callers
   _cloudundancyArgsParser._call_GetProgramMode = BIND_2ARG_METALMOCK_OBJECT(GetProgramModeMock);
}

TEST(DefaultConstructor_NewsComponents)
{
   CloudundancyArgsParser cloudundancyArgsParser;
   STD_FUNCTION_TARGETS(CloudundancyArgsParser::GetProgramMode, cloudundancyArgsParser._call_GetProgramMode);
   DELETE_TO_ASSERT_NEWED(cloudundancyArgsParser._docoptParser);
   DELETE_TO_ASSERT_NEWED(cloudundancyArgsParser._fileSystem);
}

TEST(ParseStringArgs_CallsDocoptParserForEachField_ReturnsCloudundancyArgs)
{
   const map<string, docopt::Value> docoptArgs = ZenUnit::RandomMap<string, docopt::Value>();
   _docoptParserMock->ParseArgsMock.Return(docoptArgs);

   const bool isBackupFilesAndFoldersMode = ZenUnit::Random<bool>();
   const bool is7ZipBackupMode = ZenUnit::Random<bool>();
   _docoptParserMock->GetRequiredBoolMock.ReturnValues(isBackupFilesAndFoldersMode, is7ZipBackupMode);

   const ProgramMode programMode = ZenUnit::RandomEnum<ProgramMode>(ProgramMode::MaxValue);
   GetProgramModeMock.Return(programMode);

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
      { docoptArgs, "backup-files-and-folders" },
      { docoptArgs, "backup-files-and-folders-to-7z-file" }
   }));
   METALMOCK(GetProgramModeMock.CalledOnceWith(isBackupFilesAndFoldersMode, is7ZipBackupMode));
   METALMOCK(_docoptParserMock->GetRequiredStringMock.CalledOnceWith(docoptArgs, "--ini-file"));
   METALMOCK(_docoptParserMock->GetProgramModeSpecificRequiredStringMock.CalledAsFollows(
   {
      { docoptArgs, static_cast<int>(programMode), static_cast<int>(ProgramMode::BackupFilesAndFoldersWith7Zip), "--7z-ini-file" },
      { docoptArgs, static_cast<int>(programMode), static_cast<int>(ProgramMode::BackupFilesAndFoldersWith7Zip), "--backup-staging-folder" }
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

TEST(GetProgramMode_IsBackupFilesAndFoldersModeIsTrue_ReturnsProgramModeBackupFilesAndFolders)
{
   const ProgramMode programMode = CloudundancyArgsParser::GetProgramMode(true, false);
   ARE_EQUAL(ProgramMode::BackupFilesAndFolders, programMode);
}

TEST(GetProgramMode_Is7zBackupModeIsTrue_ReturnsProgramModeBackupFilesAndFolders)
{
   const ProgramMode programMode = CloudundancyArgsParser::GetProgramMode(false, true);
   ARE_EQUAL(ProgramMode::BackupFilesAndFoldersWith7Zip, programMode);
}

TEST(GetProgramMode_BothBoolsAreFalse_ThrowsInvalidArgument)
{
   THROWS_EXCEPTION(CloudundancyArgsParser::GetProgramMode(false, false),
      invalid_argument, "CloudundancyArgsParser::GetProgramMode(): isBackupFilesAndFoldersMode and is7ZipBackupMode are unexpectedly both false");
}

RUN_TESTS(CloudundancyArgsParserTests)
