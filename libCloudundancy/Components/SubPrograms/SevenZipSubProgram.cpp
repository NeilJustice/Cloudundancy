#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyFileCopier.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyFileSystem.h"
#include "libCloudundancy/Components/SubPrograms/SevenZipSubProgram.h"

SevenZipSubProgram::SevenZipSubProgram()
   // Function Callers
   : _voidZeroArgMemberFunctionCaller(make_unique<_voidZeroArgMemberFunctionCallerType>())
   // Constant Components
   , _cloudundancyFileCopier(std::make_unique<CloudundancyFileCopier>())
   , _cloudundancyFileSystem(make_unique<CloudundancyFileSystem>())
   , _fileSystem(make_unique<Utils::FileSystem>())
   , _processRunner(std::make_unique<Utils::ProcessRunner>())
   , _watch(std::make_unique<Utils::Watch>())
   // Mutable Components
   , _stopwatch(std::make_unique<Utils::Stopwatch>())
{
}

SevenZipSubProgram::~SevenZipSubProgram()
{
}

int SevenZipSubProgram::Run()
{
   _voidZeroArgMemberFunctionCaller->CallConstMemberFunction(
      this, &SevenZipSubProgram::DeleteBackupStagingFolder);

   _voidZeroArgMemberFunctionCaller->CallConstMemberFunction(
      this, &SevenZipSubProgram::CopyFileToFilesAndFoldersToBackupStagingFolder);

   _voidZeroArgMemberFunctionCaller->CallConstMemberFunction(
      this, &SevenZipSubProgram::SevenZipBackupStagingFolder);

   _voidZeroArgMemberFunctionCaller->CallConstMemberFunction(
      this, &SevenZipSubProgram::Copy7ZipFileToDestinationFolders);
   return 0;
}

// Private Functions

void SevenZipSubProgram::Copy7ZipFileToDestinationFolders() const
{
   p_console->WriteLine("[Cloudundancy] Copying .7z file to [DestinationFolders]...");
   _cloudundancyFileCopier->CopyFilteredFilesAndFoldersToDestinationFolders(p_args.sevenZipFileCopyingIniInputFilePath, false);
   p_console->WriteLineColor("\n[Cloudundancy] Successfully copied .7z file to [DestinationFolders]", Utils::Color::Green);
}

void SevenZipSubProgram::CopyFileToFilesAndFoldersToBackupStagingFolder() const
{
   _cloudundancyFileCopier->CopyFilteredFilesAndFoldersToDestinationFolders(p_args.sevenZipModeIniInputFilePath, false);
}

void SevenZipSubProgram::DeleteBackupStagingFolder() const
{
   _stopwatch->Start();
   const string deletingMessage = Utils::String::ConcatStrings("[Cloudundancy] Deleting ", p_args.sevenZipStagingFolderPath.string());
   p_console->WriteLine(deletingMessage);

   _cloudundancyFileSystem->DeleteFolderContentsExceptForFile(p_args.sevenZipStagingFolderPath, "Cloudundancy.log");

   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   const string deletedMessage = Utils::String::ConcatStrings(
      "[Cloudundancy] Deleted ", p_args.sevenZipStagingFolderPath.string(), " in ", elapsedSeconds, " seconds\n");
   p_console->WriteLine(deletedMessage);
}

void SevenZipSubProgram::SevenZipBackupStagingFolder() const
{
   _stopwatch->Start();
   const string sevenZippingMessage = Utils::String::ConcatStrings("\n[Cloudundancy] 7-zipping ", p_args.sevenZipStagingFolderPath.string(), "...");
   p_console->WriteLineColor(sevenZippingMessage, Utils::Color::Teal);
   _fileSystem->SetCurrentPath(p_args.sevenZipStagingFolderPath);
   const string dateTimeNowForFileNames = _watch->DateTimeNowForFileNames();
   const string sevenZipCommandLineArguments = Utils::String::ConcatStrings("a 7ZipFile/CloudundancyBackup_", dateTimeNowForFileNames, ".7z -r -mx9");
   _processRunner->FailFastRun("7z", sevenZipCommandLineArguments, true);
   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   const string sevenZippedMessage = Utils::String::ConcatStrings(
      "[Cloudundancy] 7-zipped ", p_args.sevenZipStagingFolderPath.string(), " in ", elapsedSeconds, " seconds\n");
   p_console->WriteLineColor(sevenZippedMessage, Utils::Color::Green);
}
