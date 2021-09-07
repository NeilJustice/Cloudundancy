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
   , _watch(std::make_unique<Utils::Watch>())
   // Mutable Components
   , _stopwatch(std::make_unique<Utils::Stopwatch>())
{
}

SevenZipSubProgram::~SevenZipSubProgram()
{
}

int SevenZipSubProgram::Run(const CloudundancyArgs& args)
{
   _voidOneArgMemberFunctionCaller->CallConstMemberFunction(&SevenZipSubProgram::DeleteBackupStagingFolder, this, args);
   _voidOneArgMemberFunctionCaller->CallConstMemberFunction(&SevenZipSubProgram::CopyFileToFilesAndFoldersToBackupStagingFolder, this, args);
   _voidOneArgMemberFunctionCaller->CallConstMemberFunction(&SevenZipSubProgram::SevenZipBackupStagingFolder, this, args);
   _voidOneArgMemberFunctionCaller->CallConstMemberFunction(&SevenZipSubProgram::Copy7ZipFileToDestinationFolders, this, args);
   return 0;
}

// Private Functions

void SevenZipSubProgram::Copy7ZipFileToDestinationFolders(const CloudundancyArgs& args) const
{
   _console->WriteLine("[Cloudundancy] Copying .7z file to [DestinationFolders]...");
   _cloudundancyFileCopier->CopyFileToFilesAndFoldersToMultipleDestinationFolders(args.sevenZipFileCopyingIniFilePath, false);
   _console->WriteLineColor("\n[Cloudundancy] Successfully copied .7z file to [DestinationFolders]", Color::Green);
}

void SevenZipSubProgram::CopyFileToFilesAndFoldersToBackupStagingFolder(const CloudundancyArgs& args) const
{
   _cloudundancyFileCopier->CopyFileToFilesAndFoldersToMultipleDestinationFolders(args.sevenZipModeIniFilePath, false);
}

void SevenZipSubProgram::DeleteBackupStagingFolder(const CloudundancyArgs& args) const
{
   _stopwatch->Start();
   const string deletingMessage = Utils::String::ConcatStrings("[Cloudundancy] Deleting ", args.sevenZipStagingFolderPath.string());
   _console->WriteLine(deletingMessage);

   _cloudundancyFileSystem->DeleteFolderContentsExceptForFile(args.sevenZipStagingFolderPath, "Cloudundancy.log");

   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   const string deletedMessage = Utils::String::ConcatStrings(
      "[Cloudundancy] Deleted ", args.sevenZipStagingFolderPath.string(), " in ", elapsedSeconds, " seconds\n");
   _console->WriteLine(deletedMessage);
}

void SevenZipSubProgram::SevenZipBackupStagingFolder(const CloudundancyArgs& args) const
{
   _stopwatch->Start();
   const string sevenZippingMessage = Utils::String::ConcatStrings("\n[Cloudundancy] 7-zipping ", args.sevenZipStagingFolderPath.string(), "...");
   _console->WriteLineColor(sevenZippingMessage, Color::Teal);
   _fileSystem->SetCurrentPath(args.sevenZipStagingFolderPath);
   const string dateTimeNowForFileNames = _watch->DateTimeNowForFileNames();
   const string sevenZipCommandLineArguments = Utils::String::ConcatStrings("a 7ZipFile/CloudundancyBackup_", dateTimeNowForFileNames, ".7z -r -mx9");
   _processRunner->FailFastRun("7z", sevenZipCommandLineArguments, true);
   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   const string sevenZippedMessage = Utils::String::ConcatStrings(
      "[Cloudundancy] 7-zipped ", args.sevenZipStagingFolderPath.string(), " in ", elapsedSeconds, " seconds\n");
   _console->WriteLineColor(sevenZippedMessage, Color::Green);
}
