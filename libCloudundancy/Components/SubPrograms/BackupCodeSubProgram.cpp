#include "pch.h"
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"
#include "libCloudundancy/Components/Console/Console.h"
#include "libCloudundancy/Components/CloudundancyFileCopier.h"
#include "libCloudundancy/Components/FileSystem/FileSystem.h"
#include "libCloudundancy/Components/FunctionCallers/Member/VoidOneArgMemberFunctionCaller.h"
#include "libCloudundancy/Components/Process/ProcessRunner.h"
#include "libCloudundancy/Components/SubPrograms/BackupCodeSubProgram.h"
#include "libCloudundancy/Components/Time/Stopwatch.h"
#include "libCloudundancy/Components/Time/Watch.h"

BackupCodeSubProgram::BackupCodeSubProgram()
   // Function Callers
   : _voidOneArgFunctionCaller(make_unique<VoidOneArgFunctionCallerType>())
   // Constant Components
   , _console(std::make_unique<Console>())
   , _cloudundancyFileCopier(std::make_unique<CloudundancyFileCopier>())
   , _fileSystem(make_unique<FileSystem>())
   , _processRunner(std::make_unique<ProcessRunner>())
   , _watch(std::make_unique<Watch>())
   // Mutable Components
   , _stopwatch(std::make_unique<Stopwatch>())
{
}

BackupCodeSubProgram::~BackupCodeSubProgram()
{
}

void BackupCodeSubProgram::Run(const CloudundancyArgs& args)
{
   _voidOneArgFunctionCaller->ConstCall(this, &BackupCodeSubProgram::DeleteBackupStagingFolder, args);
   _voidOneArgFunctionCaller->ConstCall(this, &BackupCodeSubProgram::CopyFilesAndFoldersToBackupStagingFolder, args);
   _voidOneArgFunctionCaller->ConstCall(this, &BackupCodeSubProgram::SevenZipBackupStagingFolder, args);
   _voidOneArgFunctionCaller->ConstCall(this, &BackupCodeSubProgram::Copy7zFileToDestinationFolders, args);
}

// Private Functions

void BackupCodeSubProgram::Copy7zFileToDestinationFolders(const CloudundancyArgs& args) const
{
   _console->WriteLine("[Cloudundancy] Copying .7z File To Backup Folders.");
   _stopwatch->Start();

   _cloudundancyFileCopier->CopyFilesAndFoldersToMultipleFolders(args.sevenZipIniFilePath);

   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   _console->WriteLine("[Cloudundancy] Copied .7z File To Backup Folders in " + elapsedSeconds + " seconds\n");
}

void BackupCodeSubProgram::CopyFilesAndFoldersToBackupStagingFolder(const CloudundancyArgs& args) const
{
   _console->WriteLine("[Cloudundancy] Copying Code Folder To " + args.backupStagingFolderPath.string());
   _stopwatch->Start();

   _cloudundancyFileCopier->CopyFilesAndFoldersToMultipleFolders(args.iniFilePath);

   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   _console->WriteLine("[Cloudundancy] Copied Code Folder To " + args.backupStagingFolderPath.string() + " in " + elapsedSeconds + " seconds\n");
}

void BackupCodeSubProgram::DeleteBackupStagingFolder(const CloudundancyArgs& args) const
{
   _console->WriteLine("[Cloudundancy] Deleting " + args.backupStagingFolderPath.string());
   _stopwatch->Start();

   _cloudundancyFileCopier->DeleteFolder(args.backupStagingFolderPath);

   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   _console->WriteLine("[Cloudundancy] Deleted " + args.backupStagingFolderPath.string() + " in " + elapsedSeconds + " seconds\n");
}

void BackupCodeSubProgram::SevenZipBackupStagingFolder(const CloudundancyArgs& args) const
{
   const string sevenZippingMessage = String::Concat("[Cloudundancy] 7-zipping ", args.backupStagingFolderPath.string());
   _console->WriteLine(sevenZippingMessage);
   _stopwatch->Start();

   _fileSystem->SetCurrentPath(args.backupStagingFolderPath);
   const string dateTimeNowHoursMinutes = _watch->DateTimeNowHoursMinutesForFileNames();
   const string sevenZipCommandLineArguments = "a -r -mx9 7zFile\\SourceFilesAndFolders_" + dateTimeNowHoursMinutes + ".7z";
   _processRunner->FailFastRun("7z.exe", sevenZipCommandLineArguments);

   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   const string sevenZippedMessage = String::Concat(
      "[Cloudundancy] 7-zipped ", args.backupStagingFolderPath.string(), " in ", elapsedSeconds, " seconds\n");
   _console->WriteLine(sevenZippedMessage);
}
