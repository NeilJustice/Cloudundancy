#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyFileCopier.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyLogFileWriter.h"
#include "libCloudundancy/Components/IniFile/CloudundancyIniFileReader.h"

CloudundancyFileCopier::CloudundancyFileCopier() noexcept
   // Function Pointers
   : _call_exit(exit)
   , _call_String_ReplaceFirst(String::ReplaceFirst)
   , _call_Type_GetExceptionClassNameAndMessage(Type::GetExceptionClassNameAndMessage)
   // Function Callers
   , _memberCaller_CopyFileFunctions(make_unique<_caller_CopyFileFunctionsType>())
   , _memberCaller_CopyNestedFileToFolder(make_unique<_memberCaller_CopyNestedFileToFolderType>())
   , _memberCaller_TryCopyFile(make_unique<_memberCaller_TryCopyFileType>())
   , _memberForEacher_CopyEachFileOrFolderToFolder(make_unique<_memberForEacher_CopyEachFileOrFolderToFolderType>())
   , _memberForEacher_CopyFileOrFolderToFolder(make_unique<_memberForEacher_CopyFileOrFolderToFolderType>())
   , _memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailed(make_unique<_memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedType>())
   // Constant Components
   , _cloudundancyIniFileReader(make_unique<CloudundancyIniFileReader>())
   , _cloudundancyLogFileWriter(make_unique<CloudundancyLogFileWriter>())
   , _console(make_unique<Console>())
   , _fileSystem(make_unique<FileSystem>())
   , _tryCatchCaller(make_unique<TryCatchCaller<CloudundancyFileCopier, const pair<fs::path, CloudundancyIni>&>>())
   // Mutable Components
   , _recursiveDirectoryIterator(make_unique<RecursiveDirectoryIterator>())
   , _stopwatch(make_unique<Stopwatch>())
{
}

CloudundancyFileCopier::~CloudundancyFileCopier()
{
}

void CloudundancyFileCopier::CopyFilesAndFoldersToMultipleDestinationFolders(
   const fs::path& iniFilePath, bool deleteDestinationFoldersFirst) const
{
   const CloudundancyIni cloudundancyIni = _cloudundancyIniFileReader->ReadIniFile(iniFilePath);
   if (deleteDestinationFoldersFirst)
   {
      _console->WriteLine("[Cloudundancy] Deleting [DestinationFolders] first because --delete-destination-folders-first is specified");
      _fileSystem->DeleteFoldersExceptForFile(cloudundancyIni.destinationFolderPaths, "Cloudundancy.log");
      _console->WriteLine("[Cloudundancy] Destination folders deleted");
   }
   const string copyingMessage = String::Concat(
      "[Cloudundancy] Copying [SourceFilesAndFolders] to [DestinationFolders] as listed in ", iniFilePath.string(), ":\n");
   _console->WriteLine(copyingMessage);
   _console->WriteLines(cloudundancyIni.iniFileLines);
   _recursiveDirectoryIterator->SetFileSubpathsToIgnore(cloudundancyIni.fileSubpathsToNotCopy);
   _memberForEacher_CopyEachFileOrFolderToFolder->CallConstMemberFunctionForEachElement(
      cloudundancyIni.destinationFolderPaths,
      &CloudundancyFileCopier::CopyFilesAndFoldersToDestinationFolder, this, cloudundancyIni);
}

// Private Functions

void CloudundancyFileCopier::CopyFilesAndFoldersToDestinationFolder(
   const fs::path& destinationFolderPath, const CloudundancyIni& cloudundancyIni) const
{
   const pair<fs::path, CloudundancyIni> destinationFolderPath_cloudundancyIni = make_pair(destinationFolderPath, cloudundancyIni);
   _tryCatchCaller->TryCatchCallConstMemberFunction(
      this, &CloudundancyFileCopier::DoCopyFilesAndFoldersToDestinationFolder,
      destinationFolderPath_cloudundancyIni,
      &CloudundancyFileCopier::ExceptionHandlerForDoCopyFilesAndFoldersToDestinationFolder);
}

void CloudundancyFileCopier::DoCopyFilesAndFoldersToDestinationFolder(
   const pair<fs::path, CloudundancyIni>& destinationFolderPath_cloudundancyIni) const
{
   const fs::path& destinationFolderPath = destinationFolderPath_cloudundancyIni.first;
   const CloudundancyIni& cloudundancyIni = destinationFolderPath_cloudundancyIni.second;

   const string copyingMessage = String::Concat(
      "\n[Cloudundancy] Copying [SourceFilesAndFolders] to destination folder ", destinationFolderPath.string(), ":\n");
   _console->WriteLine(copyingMessage);
   _cloudundancyLogFileWriter->AppendTextToCloudundancyLogFileInFolder(destinationFolderPath, "Cloudundancy backup started");
   _stopwatch->Start();
   _memberForEacher_CopyFileOrFolderToFolder->CallConstMemberFunctionForEachElement(
      cloudundancyIni.cloudundancyIniCopyInstructions,
      &CloudundancyFileCopier::CopyFileOrFolderToFolder, this, destinationFolderPath);
   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   const string folderBackedUpMessage = String::Concat(
      "[Cloudundancy]   FolderBackupResult: Successfully copied [SourceFilesAndFolders] to ", destinationFolderPath.string(), '\n',
      "[Cloudundancy] FolderBackupDuration: ", elapsedSeconds, " seconds");
   _console->WriteLine(folderBackedUpMessage);
   const string cloudundancyBackupSuccessfulMessage =
      String::Concat("Cloudundancy backup successful in ", elapsedSeconds, " seconds");
   _cloudundancyLogFileWriter->AppendTextToCloudundancyLogFileInFolder(
      destinationFolderPath, cloudundancyBackupSuccessfulMessage);
}

void CloudundancyFileCopier::ExceptionHandlerForDoCopyFilesAndFoldersToDestinationFolder(
   const exception& ex, const pair<fs::path, CloudundancyIni>& destinationFolderPath_cloudundancyIni) const
{
   const fs::path& destinationFolderPath = destinationFolderPath_cloudundancyIni.first;
   const string exceptionClassNameAndMessage = _call_Type_GetExceptionClassNameAndMessage(&ex);
   const string errorMessage = String::Concat(
      "Error: Exception thrown while copying files to destination folder ",
      destinationFolderPath, ": ", exceptionClassNameAndMessage);
   _console->WriteLine(errorMessage);
   _cloudundancyLogFileWriter->AppendTextToCloudundancyLogFileInFolder(destinationFolderPath, errorMessage);
}

void CloudundancyFileCopier::CopyFileOrFolderToFolder(
   const CloudundancyIniCopyInstruction& cloudundancyIniCopyInstruction,
   const fs::path& destinationFolderPath) const
{
   const char lastPathChar = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath.string().back();
   const bool sourcePathIsAFile = lastPathChar != '/' && lastPathChar != '\\';
   if (sourcePathIsAFile)
   {
      _memberCaller_CopyFileFunctions->CallConstMemberFunction(
         &CloudundancyFileCopier::TryCopyFileToFolder,
         this, cloudundancyIniCopyInstruction, destinationFolderPath);
   }
   else
   {
      _memberCaller_CopyFileFunctions->CallConstMemberFunction(
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
   const FileCopyResult fileCopyResult = _memberCaller_TryCopyFile->CallConstMemberFunction(
      &CloudundancyFileCopier::TryCopyFile, this, sourceFilePath, destinationFilePath);
   _memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailed->CallConstMemberFunction(
      &CloudundancyFileCopier::WriteCopiedMessageOrExitWithCode1IfCopyFailed, this, fileCopyResult, destinationFolderPath);
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
   const FileCopyResult fileCopyResult = _memberCaller_TryCopyFile->CallConstMemberFunction(
      &CloudundancyFileCopier::TryCopyFile, this, sourceFilePath, destinationFilePath);
   _memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailed->CallConstMemberFunction(
      &CloudundancyFileCopier::WriteCopiedMessageOrExitWithCode1IfCopyFailed, this, fileCopyResult, destinationFolderPath);
}

FileCopyResult CloudundancyFileCopier::TryCopyFile(const fs::path& sourceFilePath, const fs::path& destinationFilePath) const
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
   return fileCopyResult;
}

void CloudundancyFileCopier::WriteCopiedMessageOrExitWithCode1IfCopyFailed(
   const FileCopyResult& fileCopyResult, const fs::path& destinationFolderPath) const
{
   const string durationInMilliseconds = to_string(fileCopyResult.durationInMilliseconds);
   if (fileCopyResult.copySucceeded)
   {
      const string copiedMessage = String::Concat("Copied [", durationInMilliseconds, "ms]\n");
      _console->WriteLineColor(copiedMessage, Color::Green);
   }
   else
   {
      const string copyFailedLogFileMessage = String::Concat("File copy failed: ",
         fileCopyResult.sourceFilePath.string(), " -> ", fileCopyResult.destinationFilePath.string(),
         ". Reason: ", fileCopyResult.copyFailureReason);
      _cloudundancyLogFileWriter->AppendTextToCloudundancyLogFileInFolder(destinationFolderPath, copyFailedLogFileMessage);

      const string copyFailedConsoleMessage = String::Concat(
         "Copy failed [", durationInMilliseconds, "ms]: ", fileCopyResult.copyFailureReason, '\n',
         '\n',
         "[Cloudundancy] ExitCode: 1");
      _console->WriteLineColor(copyFailedConsoleMessage, Color::Red);

      _call_exit(1);
   }
}
