#include "pch.h"
#include "libCloudundancy/Components/IniFile/CloudundancyIniFileReader.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyFileCopier.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyLogFileAppender.h"

CloudundancyFileCopier::CloudundancyFileCopier() noexcept
   // Function Pointers
   : _call_exit(exit)
   , _call_String_ReplaceFirst(String::ReplaceFirst)
   // Function Callers
   , _memberCaller_CopyFileFunctions(make_unique<_caller_CopyFileFunctionsType>())
   , _memberCaller_CopyNestedFileToFolder(make_unique<_memberCaller_CopyNestedFileToFolderType>())
   , _memberCaller_TryCopyFile(make_unique<_memberCaller_TryCopyFileType>())
   , _memberForEacher_CopyEachFileOrFolderToFolder(make_unique<_memberForEacher_CopyEachFileOrFolderToFolderType>())
   , _memberForEacher_CopyFileOrFolderToFolder(make_unique<_memberForEacher_CopyFileOrFolderToFolderType>())
   , _memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailed(make_unique<_memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedType>())
   // Constant Components
   , _cloudundancyIniFileReader(make_unique<CloudundancyIniFileReader>())
   , _cloudundancyLogFileAppender(make_unique<CloudundancyLogFileAppender>())
   , _console(make_unique<Console>())
   , _fileSystem(make_unique<FileSystem>())
   // Mutable Components
   , _recursiveDirectoryIterator(make_unique<RecursiveDirectoryIterator>())
   , _stopwatch(make_unique<Stopwatch>())
{
}

CloudundancyFileCopier::~CloudundancyFileCopier()
{
}

void CloudundancyFileCopier::CopyFilesAndFoldersToMultipleDestinationFolders(const fs::path& cloudundancyIniFilePath) const
{
   const CloudundancyIni cloudundancyIni = _cloudundancyIniFileReader->ReadIniFile(cloudundancyIniFilePath);

   _console->WriteLines(cloudundancyIni.iniFileLines);

   _recursiveDirectoryIterator->SetFileSubpathsToNotCopy(cloudundancyIni.fileSubpathsToNotCopy);
   _memberForEacher_CopyEachFileOrFolderToFolder->CallConstMemberFunctionForEachElement(
      cloudundancyIni.destinationFolderPaths,
      &CloudundancyFileCopier::CopyFilesAndFoldersToDestinationFolder, this, cloudundancyIni);
}

// Private Functions

void CloudundancyFileCopier::CopyFilesAndFoldersToDestinationFolder(
   const fs::path& destinationFolderPath, const CloudundancyIni& cloudundancyIni) const
{
   _cloudundancyLogFileAppender->AppendTextToCloudundancyLogFileInFolder(
      destinationFolderPath, "Cloudundancy backup started");

   _stopwatch->Start();
   _memberForEacher_CopyFileOrFolderToFolder->CallConstMemberFunctionForEachElement(
      cloudundancyIni.cloudundancyIniCopyInstructions,
      &CloudundancyFileCopier::CopyFileOrFolderToFolder, this, destinationFolderPath);
   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   const string folderBackedUpMessage = String::Concat(
      "[Cloudundancy]   FolderBackupResult: Successfully copied [SourceFilesAndFolders] to ", destinationFolderPath.string(), '\n',
      "[Cloudundancy] FolderBackupDuration: ", elapsedSeconds, " seconds\n");
   _console->WriteLine(folderBackedUpMessage);

   const string cloudundancyBackupSuccessfulMessage =
      String::Concat("Cloudundancy backup successful in ", elapsedSeconds, " seconds");
   _cloudundancyLogFileAppender->AppendTextToCloudundancyLogFileInFolder(
      destinationFolderPath, cloudundancyBackupSuccessfulMessage);
}

void CloudundancyFileCopier::CopyFileOrFolderToFolder(
   const CloudundancyIniCopyInstruction& cloudundancyIniCopyInstruction,
   const fs::path& destinationFolderPath) const
{
   const char lastPathChar = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath.string().back();
   const bool sourcePathIsAFile = lastPathChar != '/' && lastPathChar != '\\';
   if (sourcePathIsAFile)
   {
      _memberCaller_CopyFileFunctions->ConstCall(
         &CloudundancyFileCopier::TryCopyFileToFolder,
         this, cloudundancyIniCopyInstruction, destinationFolderPath);
   }
   else
   {
      _memberCaller_CopyFileFunctions->ConstCall(
         &CloudundancyFileCopier::CopyNonIgnoredFilesInAndBelowFolderToFolder,
         this, cloudundancyIniCopyInstruction, destinationFolderPath);
   }
}

void CloudundancyFileCopier::CopyNestedFileToFolder(
   const fs::path& sourceFilePath,
   const CloudundancyIniCopyInstruction& cloudundancyIniCopyInstruction,
   const fs::path& destinationFolderPath) const
{
   const fs::path sourceFilePathRelativeToSourceFolderPath = _call_String_ReplaceFirst(
      sourceFilePath.string(), cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath.string(), "");
   fs::path destinationFilePath;
   if (cloudundancyIniCopyInstruction.relativeDestinationFolderPath == ".")
   {
      destinationFilePath =
         destinationFolderPath /
         sourceFilePathRelativeToSourceFolderPath;
   }
   else
   {
      destinationFilePath =
         destinationFolderPath /
         cloudundancyIniCopyInstruction.relativeDestinationFolderPath /
         sourceFilePathRelativeToSourceFolderPath;
   }
   _memberCaller_TryCopyFile->ConstCall(&CloudundancyFileCopier::TryCopyFile, this, sourceFilePath, destinationFilePath);
}

void CloudundancyFileCopier::CopyNonIgnoredFilesInAndBelowFolderToFolder(
   const CloudundancyIniCopyInstruction& cloudundancyIniCopyInstruction,
   const fs::path& destinationFolderPath) const
{
   _recursiveDirectoryIterator->InitializeIteratorAtFolderPath(cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath);
   while (true)
   {
      const fs::path nonIgnoredSourceFilePath = _recursiveDirectoryIterator->NextNonIgnoredFilePath();
      if (nonIgnoredSourceFilePath == fs::path())
      {
         break;
      }
      _memberCaller_CopyNestedFileToFolder->ConstCall(
         &CloudundancyFileCopier::CopyNestedFileToFolder,
         this, nonIgnoredSourceFilePath, cloudundancyIniCopyInstruction, destinationFolderPath);
   }
}

void CloudundancyFileCopier::TryCopyFile(const fs::path& sourceFilePath, const fs::path& destinationFilePath) const
{
   const string copyingFileMessage = String::Concat(
      "Copying ", sourceFilePath.string(), '\n',
      "     to ", destinationFilePath.string(), ". ");
   _console->Write(copyingFileMessage);
   FileCopyResult fileCopyResult;
   const bool sourceFileSizeIsGreaterThanOrEqualTo2GB = _fileSystem->IsFileSizeGreaterThanOrEqualTo2GB(sourceFilePath);
   if (sourceFileSizeIsGreaterThanOrEqualTo2GB)
   {
      fileCopyResult = _fileSystem->TryCopyFileWithStdFilesystemCopyFile(sourceFilePath, destinationFilePath);
   }
   else
   {
      fileCopyResult = _fileSystem->TryCopyFile(sourceFilePath, destinationFilePath);
   }
   _memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailed->CallConstMemberFunction(
      &CloudundancyFileCopier::WriteCopiedMessageOrExitWithCode1IfCopyFailed, this, fileCopyResult);
}

void CloudundancyFileCopier::TryCopyFileToFolder(
   const CloudundancyIniCopyInstruction& cloudundancyIniCopyInstruction,
   const fs::path& destinationFolderPath) const
{
   const fs::path& sourceFilePath = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath;
   const fs::path sourceFileName = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath.filename();
   fs::path destinationFilePath;
   if (cloudundancyIniCopyInstruction.relativeDestinationFolderPath == ".")
   {
      destinationFilePath = destinationFolderPath / sourceFileName;
   }
   else
   {
      destinationFilePath = destinationFolderPath / cloudundancyIniCopyInstruction.relativeDestinationFolderPath / sourceFileName;
   }
   _memberCaller_TryCopyFile->ConstCall(&CloudundancyFileCopier::TryCopyFile, this, sourceFilePath, destinationFilePath);
}

void CloudundancyFileCopier::WriteCopiedMessageOrExitWithCode1IfCopyFailed(const FileCopyResult& fileCopyResult) const
{
   const string durationInMilliseconds = to_string(fileCopyResult.durationInMilliseconds);
   if (fileCopyResult.copySucceeded)
   {
      const string copiedMessage = String::Concat("Copied [", durationInMilliseconds, "ms]\n");
      _console->WriteLineColor(copiedMessage, Color::Green);
   }
   else
   {
      const string copyFailedMessage = String::Concat(
         "Copy failed [", durationInMilliseconds, "ms]: ", fileCopyResult.copyFailureReason, '\n');
      _console->WriteLineColor(copyFailedMessage, Color::Red);
      _call_exit(1);
   }
}
