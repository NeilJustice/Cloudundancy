#include "pch.h"
#include "libCloudundancy/ValueTypes/CloudundancyArgs.h"
#include "libCloudundancy/Components/Console/Console.h"
#include "libCloudundancy/Components/CloudundancyFileCopier.h"
#include "libCloudundancy/Components/FileSystem/FileSystem.h"
#include "libCloudundancy/Components/FunctionCallers/Member/VoidOneArgMemberFunctionCaller.h"
#include "libCloudundancy/Components/Process/ProcessRunner.h"
#include "libCloudundancy/Components/SubPrograms/BackupFilesAndFoldersTo7zFileSubProgram.h"
#include "libCloudundancy/Components/Time/Stopwatch.h"
#include "libCloudundancy/Components/Time/Watch.h"

BackupFilesAndFoldersTo7zFileSubProgram::BackupFilesAndFoldersTo7zFileSubProgram()
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

BackupFilesAndFoldersTo7zFileSubProgram::~BackupFilesAndFoldersTo7zFileSubProgram()
{
}

int BackupFilesAndFoldersTo7zFileSubProgram::Run(const CloudundancyArgs& args)
{
   _voidOneArgFunctionCaller->ConstCall(this, &BackupFilesAndFoldersTo7zFileSubProgram::DeleteBackupStagingFolder, args);
   _voidOneArgFunctionCaller->ConstCall(this, &BackupFilesAndFoldersTo7zFileSubProgram::CopyFilesAndFoldersToBackupStagingFolder, args);
   _voidOneArgFunctionCaller->ConstCall(this, &BackupFilesAndFoldersTo7zFileSubProgram::SevenZipBackupStagingFolder, args);
   _voidOneArgFunctionCaller->ConstCall(this, &BackupFilesAndFoldersTo7zFileSubProgram::Copy7zFileToDestinationFolders, args);
   return 0;
}

// Private Functions

void BackupFilesAndFoldersTo7zFileSubProgram::Copy7zFileToDestinationFolders(const CloudundancyArgs& args) const
{
   _console->WriteLine("[Cloudundancy] Copying .7z File To Backup Folders.");
   _stopwatch->Start();

   _cloudundancyFileCopier->CopyFilesAndFoldersToMultipleFolders(args.sevenZipIniFilePath);

   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   _console->WriteLine("[Cloudundancy] Copied .7z File To Backup Folders in " + elapsedSeconds + " seconds\n");
}

void BackupFilesAndFoldersTo7zFileSubProgram::CopyFilesAndFoldersToBackupStagingFolder(const CloudundancyArgs& args) const
{
   _console->WriteLine("[Cloudundancy] Copying Code Folder To " + args.backupStagingFolderPath.string());
   _stopwatch->Start();

   _cloudundancyFileCopier->CopyFilesAndFoldersToMultipleFolders(args.iniFilePath);

   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   _console->WriteLine("[Cloudundancy] Copied Code Folder To " + args.backupStagingFolderPath.string() + " in " + elapsedSeconds + " seconds\n");
}

void BackupFilesAndFoldersTo7zFileSubProgram::DeleteBackupStagingFolder(const CloudundancyArgs& args) const
{
   _console->WriteLine("[Cloudundancy] Deleting " + args.backupStagingFolderPath.string());
   _stopwatch->Start();

   _cloudundancyFileCopier->DeleteFolder(args.backupStagingFolderPath);

   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   _console->WriteLine("[Cloudundancy] Deleted " + args.backupStagingFolderPath.string() + " in " + elapsedSeconds + " seconds\n");
}

void BackupFilesAndFoldersTo7zFileSubProgram::SevenZipBackupStagingFolder(const CloudundancyArgs& args) const
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
