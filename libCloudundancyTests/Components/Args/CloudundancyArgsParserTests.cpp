#include "pch.h"
#include "libCloudundancy/Components/Args/CloudundancyArgsParser.h"
#include "libCloudundancyTests/Components/Args/MetalMock/ProgramModeDeterminerMock.h"

TESTS(CloudundancyArgsParserTests)
AFACT(DefaultConstructor_NewsComponents)
FACTS(ParseStringArgs_CallsDocoptParserForEachField_ReturnsCloudundancyArgs)
EVIDENCE

CloudundancyArgsParser _cloudundancyArgsParser;
// Constant Components
Time::ConsoleMock* _consoleMock = nullptr;
Time::DocoptParserMock* _docoptParserMock = nullptr;
Utils::FileSystemMock* _fileSystemMock = nullptr;
Utils::ProcessRunnerMock* _processRunnerMock = nullptr;
ProgramModeDeterminerMock* _programModeDeterminerMock = nullptr;

STARTUP
{
   // Constant Components
   _cloudundancyArgsParser._console.reset(_consoleMock = new Time::ConsoleMock);
   _cloudundancyArgsParser._docoptParser.reset(_docoptParserMock = new Time::DocoptParserMock);
   _cloudundancyArgsParser._fileSystem.reset(_fileSystemMock = new Utils::FileSystemMock);
   _cloudundancyArgsParser._processRunner.reset(_processRunnerMock = new Utils::ProcessRunnerMock);
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
   bool is7ZipMode, bool expectRun7zToConfirm7zIsInThePath,
   false, false,
   true, true)
{
   const map<string, docopt::Value> docoptArgs = ZenUnit::RandomOrderedMap<string, docopt::Value>();
   _docoptParserMock->ParseArgsMock.Return(docoptArgs);

   const bool isCopyFileToFilesToMultipleFoldersMode = ZenUnit::Random<bool>();
   const bool isExampleLinuxIniFileMode = ZenUnit::Random<bool>();
   const bool isExampleWindowsIniFileMode = ZenUnit::Random<bool>();
   _docoptParserMock->GetRequiredBoolMock.ReturnValues(
      isCopyFileToFilesToMultipleFoldersMode,
      is7ZipMode,
      isExampleLinuxIniFileMode,
      isExampleWindowsIniFileMode);

   const ProgramMode programMode = _programModeDeterminerMock->DetermineProgramModeMock.ReturnRandom();

   const string iniFilePath = _docoptParserMock->GetRequiredStringMock.ReturnRandom();

   const bool deleteDestinationFoldersFirst = _docoptParserMock->GetOptionalBoolMock.ReturnRandom();

   const string sevenZipModeIniFilePath = ZenUnit::Random<string>();
   const string sevenZipStagingFolderPath = ZenUnit::Random<string>();
   const string sevenZipFileCopyingIniFilePath = ZenUnit::Random<string>();
   _docoptParserMock->GetProgramModeSpecificRequiredStringMock.ReturnValues(
      sevenZipModeIniFilePath, sevenZipStagingFolderPath, sevenZipFileCopyingIniFilePath);

   _fileSystemMock->ThrowIfFilePathIsNotEmptyPathAndFileDoesNotExistMock.Expect();

   if (expectRun7zToConfirm7zIsInThePath)
   {
      _consoleMock->WriteLineMock.Expect();
      _processRunnerMock->FailFastRunMock.ReturnRandom();
   }

   const vector<string> stringArgs = ZenUnit::RandomVector<string>();
   //
   const CloudundancyArgs args = _cloudundancyArgsParser.ParseStringArgs(stringArgs);
   //
   METALMOCK(_docoptParserMock->GetRequiredBoolMock.CalledNTimes(4));
   METALMOCK(_docoptParserMock->GetProgramModeSpecificRequiredStringMock.CalledNTimes(3));
   METALMOCK(_fileSystemMock->ThrowIfFilePathIsNotEmptyPathAndFileDoesNotExistMock.CalledNTimes(3));

   METALMOCKTHEN(_docoptParserMock->ParseArgsMock.CalledOnceWith(CloudundancyArgs::CommandLineUsage, stringArgs)).Then(

   METALMOCKTHEN(_docoptParserMock->GetRequiredBoolMock.CalledWith(
      docoptArgs, "copy-files-to-multiple-folders"))).Then(

   METALMOCKTHEN(_docoptParserMock->GetRequiredBoolMock.CalledWith(
      docoptArgs, "7zip-files-then-copy-the-7zip-file-to-multiple-folders"))).Then(

   METALMOCKTHEN(_docoptParserMock->GetRequiredBoolMock.CalledWith(
      docoptArgs, "example-linux-ini-file"))).Then(

   METALMOCKTHEN(_docoptParserMock->GetRequiredBoolMock.CalledWith(
      docoptArgs, "example-windows-ini-file"))).Then(

   METALMOCKTHEN(_programModeDeterminerMock->DetermineProgramModeMock.CalledOnceWith(
      isCopyFileToFilesToMultipleFoldersMode,
      is7ZipMode,
      isExampleLinuxIniFileMode,
      isExampleWindowsIniFileMode))).Then(

   METALMOCKTHEN(_docoptParserMock->GetRequiredStringMock.CalledOnceWith(docoptArgs, "--ini-file"))).Then(

   METALMOCKTHEN(_docoptParserMock->GetOptionalBoolMock.CalledOnceWith(docoptArgs, "--delete-destination-folders-first"))).Then(

   METALMOCKTHEN(_docoptParserMock->GetProgramModeSpecificRequiredStringMock.CalledWith(
      docoptArgs, static_cast<int>(programMode), static_cast<int>(ProgramMode::SevenZip), "--ini-file-to-copy-files-to-7zip-staging-folder"))).Then(

   METALMOCKTHEN(_docoptParserMock->GetProgramModeSpecificRequiredStringMock.CalledWith(
      docoptArgs, static_cast<int>(programMode), static_cast<int>(ProgramMode::SevenZip), "--7zip-staging-folder"))).Then(

   METALMOCKTHEN(_docoptParserMock->GetProgramModeSpecificRequiredStringMock.CalledWith(
      docoptArgs, static_cast<int>(programMode), static_cast<int>(ProgramMode::SevenZip), "--ini-file-to-copy-7zip-file-from-staging-folder-to-multiple-folders"))).Then(

   METALMOCKTHEN(_fileSystemMock->ThrowIfFilePathIsNotEmptyPathAndFileDoesNotExistMock.CalledWith(iniFilePath))).Then(
   METALMOCKTHEN(_fileSystemMock->ThrowIfFilePathIsNotEmptyPathAndFileDoesNotExistMock.CalledWith(sevenZipModeIniFilePath))).Then(
   METALMOCKTHEN(_fileSystemMock->ThrowIfFilePathIsNotEmptyPathAndFileDoesNotExistMock.CalledWith(sevenZipFileCopyingIniFilePath)));

   if (expectRun7zToConfirm7zIsInThePath)
   {
      METALMOCKTHEN(_consoleMock->WriteLineMock.CalledWith(
         "[Cloudundancy] Running program 7z to confirm 7z is present on the PATH")).Then(
      METALMOCKTHEN(_processRunnerMock->FailFastRunMock.CalledOnceWith("7z", "", false))).Then(
      METALMOCKTHEN(_consoleMock->WriteLineMock.CalledWith(
         "[Cloudundancy] 7z ran and exited with code 0 and is therefore confirmed to be present on the PATH\n")));
   }
   CloudundancyArgs expectedArgs{};
   expectedArgs.programMode = programMode;
   expectedArgs.iniFilePath = iniFilePath;
   expectedArgs.deleteDestinationFoldersFirst = deleteDestinationFoldersFirst;
   expectedArgs.sevenZipModeIniFilePath = sevenZipModeIniFilePath;
   expectedArgs.sevenZipStagingFolderPath = sevenZipStagingFolderPath;
   expectedArgs.sevenZipFileCopyingIniFilePath = sevenZipFileCopyingIniFilePath;
   ARE_EQUAL(expectedArgs, args);
}

RUN_TESTS(CloudundancyArgsParserTests)
