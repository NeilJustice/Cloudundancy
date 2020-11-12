#include "pch.h"
#include "libCloudundancy/Components/Console/Console.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyFileCopier.h"
#include "libCloudundancy/Components/FileSystem/FileSystem.h"
#include "libCloudundancy/Components/FunctionCallers/Member/VoidOneArgMemberFunctionCaller.h"
#include "libCloudundancy/Components/Process/ProcessRunner.h"
#include "libCloudundancy/Components/SubPrograms/BackupFilesAndFoldersWith7ZipSubProgram.h"
#include "libCloudundancy/Components/Time/Stopwatch.h"
#include "libCloudundancy/Components/Time/Watch.h"

BackupFilesAndFoldersWith7ZipSubProgram::BackupFilesAndFoldersWith7ZipSubProgram()
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

BackupFilesAndFoldersWith7ZipSubProgram::~BackupFilesAndFoldersWith7ZipSubProgram()
{
}

int BackupFilesAndFoldersWith7ZipSubProgram::Run(const CloudundancyArgs& args)
{
   _voidOneArgFunctionCaller->ConstCall(this, &BackupFilesAndFoldersWith7ZipSubProgram::DeleteBackupStagingFolder, args);
   _voidOneArgFunctionCaller->ConstCall(this, &BackupFilesAndFoldersWith7ZipSubProgram::CopyFilesAndFoldersToBackupStagingFolder, args);
   _voidOneArgFunctionCaller->ConstCall(this, &BackupFilesAndFoldersWith7ZipSubProgram::SevenZipCodeBackupFolder, args);
   _voidOneArgFunctionCaller->ConstCall(this, &BackupFilesAndFoldersWith7ZipSubProgram::Copy7zFileToDestinationFolders, args);
   return 0;
}

// Private Functions

void BackupFilesAndFoldersWith7ZipSubProgram::Copy7zFileToDestinationFolders(const CloudundancyArgs& args) const
{
   _console->WriteLine("[Cloudundancy] Copying .7z file to backup folders.");
   _stopwatch->Start();

   _cloudundancyFileCopier->CopyFilesAndFoldersToMultipleFolders(args.sevenZipIniFilePath);

   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   _console->WriteLine("[Cloudundancy] Copied .7z file to backup folders in " + elapsedSeconds + " seconds\n");
}

void BackupFilesAndFoldersWith7ZipSubProgram::CopyFilesAndFoldersToBackupStagingFolder(const CloudundancyArgs& args) const
{
   _console->WriteLine("[Cloudundancy] Copying Code Folder To " + args.backupStagingFolderPath.string());
   _stopwatch->Start();

   _cloudundancyFileCopier->CopyFilesAndFoldersToMultipleFolders(args.iniFilePath);

   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   _console->WriteLine("[Cloudundancy] Copied Code Folder To " + args.backupStagingFolderPath.string() + " in " + elapsedSeconds + " seconds\n");
}

void BackupFilesAndFoldersWith7ZipSubProgram::DeleteBackupStagingFolder(const CloudundancyArgs& args) const
{
   _console->WriteLine("[Cloudundancy] Deleting " + args.backupStagingFolderPath.string());
   _stopwatch->Start();

   _cloudundancyFileCopier->DeleteFolder(args.backupStagingFolderPath);

   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   _console->WriteLine("[Cloudundancy] Deleted " + args.backupStagingFolderPath.string() + " in " + elapsedSeconds + " seconds\n");
}

void BackupFilesAndFoldersWith7ZipSubProgram::SevenZipCodeBackupFolder(const CloudundancyArgs& args) const
{
   _console->WriteLine("[Cloudundancy] 7-zipping 7zFile\\SourceFilesAndFolders.");
   _stopwatch->Start();

   _fileSystem->SetCurrentPath(args.backupStagingFolderPath);
   const string dateTimeNowForFileNames = _watch->DateTimeNowForFileNames();
   const string sevenZipCommandLineArguments = "a -r -mx9 7zFile\\SourceFilesAndFolders_" + dateTimeNowForFileNames + ".7z";
   _processRunner->FailFastRun("7z.exe", sevenZipCommandLineArguments);

   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   _console->WriteLine("[Cloudundancy] 7-zipped 7zFile\\SourceFilesAndFolders in " + elapsedSeconds + " seconds\n");
}

