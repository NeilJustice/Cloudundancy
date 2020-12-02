#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyFileCopier.h"
#include "libCloudundancy/Components/SubPrograms/BackupFilesAndFoldersTo7zFileSubProgram.h"

BackupFilesAndFoldersTo7zFileSubProgram::BackupFilesAndFoldersTo7zFileSubProgram()
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

BackupFilesAndFoldersTo7zFileSubProgram::~BackupFilesAndFoldersTo7zFileSubProgram()
{
}

int BackupFilesAndFoldersTo7zFileSubProgram::Run(const CloudundancyArgs& args)
{
   _voidOneArgFunctionCaller->CallConstMemberFunction(
      &BackupFilesAndFoldersTo7zFileSubProgram::DeleteBackupStagingFolder, this, args);
   _voidOneArgFunctionCaller->CallConstMemberFunction(
      &BackupFilesAndFoldersTo7zFileSubProgram::CopyFilesAndFoldersToBackupStagingFolder, this, args);
   _voidOneArgFunctionCaller->CallConstMemberFunction(
      &BackupFilesAndFoldersTo7zFileSubProgram::SevenZipBackupStagingFolder, this, args);
   _voidOneArgFunctionCaller->CallConstMemberFunction(
      &BackupFilesAndFoldersTo7zFileSubProgram::Copy7zFileToDestinationFolders, this, args);
   return 0;
}

// Private Functions

void BackupFilesAndFoldersTo7zFileSubProgram::Copy7zFileToDestinationFolders(const CloudundancyArgs& args) const
{
   _console->WriteLine("[Cloudundancy] Copying .7z file to [DestinationFolders]...");
   _stopwatch->Start();

   _cloudundancyFileCopier->CopyFilesAndFoldersToMultipleDestinationFolders(args.sevenZipIniFilePath);

   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   const string copiedMessage = String::Concat(
      "[Cloudundancy] Copied .7z file to [DestinationFolders] in ", elapsedSeconds, " seconds\n");
   _console->WriteLine(copiedMessage);
}

void BackupFilesAndFoldersTo7zFileSubProgram::CopyFilesAndFoldersToBackupStagingFolder(const CloudundancyArgs& args) const
{
   const string copyingMessage = String::Concat(
      "[Cloudundancy] Copying [SourceFilesAndFolders] To " + args.backupStagingFolderPath.string());
   _console->WriteLine(copyingMessage);
   _stopwatch->Start();

   _cloudundancyFileCopier->CopyFilesAndFoldersToMultipleDestinationFolders(args.iniFilePath);

   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   const string copiedMessage = String::Concat(
      "[Cloudundancy] Copied [SourceFilesAndFolders] To ", args.backupStagingFolderPath.string(), " in ", elapsedSeconds, " seconds\n");
   _console->WriteLine(copiedMessage);
}

void BackupFilesAndFoldersTo7zFileSubProgram::DeleteBackupStagingFolder(const CloudundancyArgs& args) const
{
   const string deletingMessage = String::Concat("[Cloudundancy] Deleting ", args.backupStagingFolderPath.string());
   _console->WriteLine(deletingMessage);
   _stopwatch->Start();

   _fileSystem->DeleteFolder(args.backupStagingFolderPath);

   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   const string deletedMessage = String::Concat(
      "[Cloudundancy] Deleted ", args.backupStagingFolderPath.string(), " in ", elapsedSeconds, " seconds\n");
   _console->WriteLine(deletedMessage);
}

void BackupFilesAndFoldersTo7zFileSubProgram::SevenZipBackupStagingFolder(const CloudundancyArgs& args) const
{
   const string sevenZippingMessage = String::Concat("[Cloudundancy] 7-zipping ", args.backupStagingFolderPath.string(), "...");
   _console->WriteLine(sevenZippingMessage);
   _stopwatch->Start();

   _fileSystem->SetCurrentPath(args.backupStagingFolderPath);
   const string dateTimeNowForFileNames = _watch->DateTimeNowForFileNames();
   const string sevenZipCommandLineArguments = "a -r -mx9 7zFile\\SourceFilesAndFolders_" + dateTimeNowForFileNames + ".7z";
   _processRunner->FailFastRun("7z", sevenZipCommandLineArguments, true);

   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   const string sevenZippedMessage = String::Concat(
      "[Cloudundancy] 7-zipped ", args.backupStagingFolderPath.string(), " in ", elapsedSeconds, " seconds\n");
   _console->WriteLine(sevenZippedMessage);
}
