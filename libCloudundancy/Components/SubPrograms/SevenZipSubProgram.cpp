#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyFileCopier.h"
#include "libCloudundancy/Components/SubPrograms/SevenZipSubProgram.h"

SevenZipSubProgram::SevenZipSubProgram()
   // Function Callers
   : _voidOneArgFunctionCaller(make_unique<VoidOneArgFunctionCallerType>())
   // Constant Components
   , _cloudundancyFileCopier(std::make_unique<CloudundancyFileCopier>())
   , _fileSystem(make_unique<FileSystem>())
   , _processRunner(std::make_unique<ProcessRunner>())
   , _watch(std::make_unique<Watch>())
   // Mutable Components
   , _stopwatch(std::make_unique<Stopwatch>())
{
}

SevenZipSubProgram::~SevenZipSubProgram()
{
}

int SevenZipSubProgram::Run(const CloudundancyArgs& args)
{
   _voidOneArgFunctionCaller->CallConstMemberFunction(
      &SevenZipSubProgram::DeleteBackupStagingFolder, this, args);
   _voidOneArgFunctionCaller->CallConstMemberFunction(
      &SevenZipSubProgram::CopyFilesAndFoldersToBackupStagingFolder, this, args);
   _voidOneArgFunctionCaller->CallConstMemberFunction(
      &SevenZipSubProgram::SevenZipBackupStagingFolder, this, args);
   _voidOneArgFunctionCaller->CallConstMemberFunction(
      &SevenZipSubProgram::Copy7ZipFileToDestinationFolders, this, args);
   return 0;
}

// Private Functions

void SevenZipSubProgram::Copy7ZipFileToDestinationFolders(const CloudundancyArgs& args) const
{
   _console->WriteLine("[Cloudundancy] Copying .7z file to [DestinationFolders]...");
   _stopwatch->Start();

   _cloudundancyFileCopier->CopyFilesAndFoldersToMultipleDestinationFolders(args.sevenZipFileCopyingIniFilePath, false);

   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   const string copiedMessage = String::Concat(
      "[Cloudundancy] Copied .7z file to [DestinationFolders] in ", elapsedSeconds, " seconds\n");
   _console->WriteLine(copiedMessage);
}

void SevenZipSubProgram::CopyFilesAndFoldersToBackupStagingFolder(const CloudundancyArgs& args) const
{
   const string copyingMessage = String::Concat(
      "[Cloudundancy] Copying [SourceFilesAndFolders] To " + args.sevenZipStagingFolderPath.string());
   _console->WriteLine(copyingMessage);
   _stopwatch->Start();

   _cloudundancyFileCopier->CopyFilesAndFoldersToMultipleDestinationFolders(args.sevenZipModeIniFilePath, false);

   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   const string copiedMessage = String::Concat(
      "[Cloudundancy] Copied [SourceFilesAndFolders] To ", args.sevenZipStagingFolderPath.string(), " in ", elapsedSeconds, " seconds\n");
   _console->WriteLine(copiedMessage);
}

void SevenZipSubProgram::DeleteBackupStagingFolder(const CloudundancyArgs& args) const
{
   const string deletingMessage = String::Concat("[Cloudundancy] Deleting ", args.sevenZipStagingFolderPath.string());
   _console->WriteLine(deletingMessage);
   _stopwatch->Start();

   _fileSystem->DeleteFolder(args.sevenZipStagingFolderPath);

   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   const string deletedMessage = String::Concat(
      "[Cloudundancy] Deleted ", args.sevenZipStagingFolderPath.string(), " in ", elapsedSeconds, " seconds\n");
   _console->WriteLine(deletedMessage);
}

void SevenZipSubProgram::SevenZipBackupStagingFolder(const CloudundancyArgs& args) const
{
   const string sevenZippingMessage = String::Concat("[Cloudundancy] 7-zipping ", args.sevenZipStagingFolderPath.string(), "...");
   _console->WriteLine(sevenZippingMessage);
   _stopwatch->Start();

   _fileSystem->SetCurrentPath(args.sevenZipStagingFolderPath);
   const string dateTimeNowForFileNames = _watch->DateTimeNowForFileNames();
   const string sevenZipCommandLineArguments = String::Concat(
      "a -r -mx9 7ZipFile\\CloudundancyBackup_", dateTimeNowForFileNames, ".7z");
   _processRunner->FailFastRun("7z", sevenZipCommandLineArguments, true);

   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   const string sevenZippedMessage = String::Concat(
      "[Cloudundancy] 7-zipped ", args.sevenZipStagingFolderPath.string(), " in ", elapsedSeconds, " seconds\n");
   _console->WriteLine(sevenZippedMessage);
}
