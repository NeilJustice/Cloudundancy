#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyFileCopier.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyFileSystem.h"
#include "libCloudundancy/Components/SubPrograms/SevenZipSubProgram.h"

SevenZipSubProgram::SevenZipSubProgram()
   // Function Callers
   : _voidOneArgMemberFunctionCaller(make_unique<VoidOneArgMemberFunctionCallerType>())
   // Constant Components
   , _cloudundancyFileCopier(std::make_unique<CloudundancyFileCopier>())
   , _cloudundancyFileSystem(make_unique<CloudundancyFileSystem>())
   , _fileSystem(make_unique<Utils::FileSystem>())
   , _processRunner(std::make_unique<Utils::ProcessRunner>())
   , _watch(std::make_unique<Time::Watch>())
   // Mutable Components
   , _stopwatch(std::make_unique<Time::Stopwatch>())
{
}

SevenZipSubProgram::~SevenZipSubProgram()
{
}

int SevenZipSubProgram::Run(const CloudundancyArgs& args)
{
   _voidOneArgMemberFunctionCaller->CallConstMemberFunction(this, &SevenZipSubProgram::DeleteBackupStagingFolder, args);
   _voidOneArgMemberFunctionCaller->CallConstMemberFunction(this, &SevenZipSubProgram::CopyFileToFilesAndFoldersToBackupStagingFolder, args);
   _voidOneArgMemberFunctionCaller->CallConstMemberFunction(this, &SevenZipSubProgram::SevenZipBackupStagingFolder, args);
   _voidOneArgMemberFunctionCaller->CallConstMemberFunction(this, &SevenZipSubProgram::Copy7ZipFileToDestinationFolders, args);
   return 0;
}

// Private Functions

void SevenZipSubProgram::Copy7ZipFileToDestinationFolders(const CloudundancyArgs& args) const
{
   p_console->WriteLine("[Cloudundancy] Copying .7z file to [DestinationFolders]...");
   _cloudundancyFileCopier->CopyFilteredFilesAndFoldersToDestinationFolders(args.sevenZipFileCopyingIniFilePath, false);
   p_console->WriteLineColor("\n[Cloudundancy] Successfully copied .7z file to [DestinationFolders]", Color::Green);
}

void SevenZipSubProgram::CopyFileToFilesAndFoldersToBackupStagingFolder(const CloudundancyArgs& args) const
{
   _cloudundancyFileCopier->CopyFilteredFilesAndFoldersToDestinationFolders(args.sevenZipModeIniFilePath, false);
}

void SevenZipSubProgram::DeleteBackupStagingFolder(const CloudundancyArgs& args) const
{
   _stopwatch->Start();
   const string deletingMessage = Utils::String::ConcatStrings("[Cloudundancy] Deleting ", args.sevenZipStagingFolderPath.string());
   p_console->WriteLine(deletingMessage);

   _cloudundancyFileSystem->DeleteFolderContentsExceptForFile(args.sevenZipStagingFolderPath, "Cloudundancy.log");

   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   const string deletedMessage = Utils::String::ConcatStrings(
      "[Cloudundancy] Deleted ", args.sevenZipStagingFolderPath.string(), " in ", elapsedSeconds, " seconds\n");
   p_console->WriteLine(deletedMessage);
}

void SevenZipSubProgram::SevenZipBackupStagingFolder(const CloudundancyArgs& args) const
{
   _stopwatch->Start();
   const string sevenZippingMessage = Utils::String::ConcatStrings("\n[Cloudundancy] 7-zipping ", args.sevenZipStagingFolderPath.string(), "...");
   p_console->WriteLineColor(sevenZippingMessage, Color::Teal);
   _fileSystem->SetCurrentPath(args.sevenZipStagingFolderPath);
   const string dateTimeNowForFileNames = _watch->DateTimeNowForFileNames();
   const string sevenZipCommandLineArguments = Utils::String::ConcatStrings("a 7ZipFile/CloudundancyBackup_", dateTimeNowForFileNames, ".7z -r -mx9");
   _processRunner->FailFastRun("7z", sevenZipCommandLineArguments, true);
   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   const string sevenZippedMessage = Utils::String::ConcatStrings(
      "[Cloudundancy] 7-zipped ", args.sevenZipStagingFolderPath.string(), " in ", elapsedSeconds, " seconds\n");
   p_console->WriteLineColor(sevenZippedMessage, Color::Green);
}
