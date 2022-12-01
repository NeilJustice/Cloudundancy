#include "pch.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyFileCopier.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyFileSystem.h"
#include "libCloudundancy/Components/FileSystem/CloudundancyLogFileWriter.h"
#include "libCloudundancy/Components/IniFile/CloudundancyIniFileReader.h"

CloudundancyFileCopier::CloudundancyFileCopier() noexcept
   // Function Pointers
   : _call_quick_exit(quick_exit)
   , _call_String_ReplaceFirst(Utils::String::ReplaceFirst)
   , _call_Type_GetExceptionClassNameAndMessage(Type::GetExceptionClassNameAndMessage)
   // Function Callers
   , _caller_CopyFileToFileFunctions(make_unique<_caller_CopyFileToFileFunctionsType>())
   , _caller_CopyNestedFileToFolder(make_unique<_caller_CopyNestedFileToFolderType>())
   , _caller_CopyFileToFile(make_unique<_caller_CopyFileToFileType>())
   , _caller_WriteCopiedMessageOrExitWithCode1IfCopyFailed(make_unique<_caller_WriteCopiedMessageOrExitWithCode1IfCopyFailedType>())
   , _forEacher_CopyEachFileOrFolderToFolder(make_unique<_forEacher_CopyEachFileOrFolderToFolderType>())
   , _forEacher_CopyFileOrFolderToFolder(make_unique<_forEacher_CopyFileOrFolderToFolderType>())
   // Constant Components
   , _cloudundancyFileSystem(make_unique<CloudundancyFileSystem>())
   , _cloudundancyIniFileReader(make_unique<CloudundancyIniFileReader>())
   , _cloudundancyLogFileWriter(make_unique<CloudundancyLogFileWriter>())
   , _console(make_unique<Utils::Console>())
   , _fileSystem(make_unique<Utils::FileSystem>())
   , _tryCatchCaller(make_unique<Utils::TryCatchCaller<CloudundancyFileCopier, const pair<fs::path, CloudundancyIni>&>>())
   // Mutable Components
   , _recursiveDirectoryIterator(make_unique<Utils::RecursiveDirectoryIterator>())
   , _stopwatch(make_unique<Utils::Stopwatch>())
{
}

CloudundancyFileCopier::~CloudundancyFileCopier()
{
}

void CloudundancyFileCopier::CopyFilteredFilesAndFoldersToDestinationFolders(
   const fs::path& iniFilePath, bool deleteDestinationFoldersFirst) const
{
   const CloudundancyIni cloudundancyIni = _cloudundancyIniFileReader->ReadIniFile(iniFilePath);
   if (deleteDestinationFoldersFirst)
   {
      _console->WriteLine("[Cloudundancy] Deleting [DestinationFolders] first because --delete-destination-folders-first is specified");
      _cloudundancyFileSystem->DeleteMultipleFolderContentsExceptForFile(cloudundancyIni.destinationFolderPaths, "Cloudundancy.log");
   }
   const string copyingMessage = Utils::String::ConcatStrings(
      "[Cloudundancy] Copying [SourceFilesAndFolders] to [DestinationFolders] as listed in ", iniFilePath.string(), ":\n");
   _console->WriteLineColor(copyingMessage, Color::Teal);

   _console->WriteLines(cloudundancyIni.iniFileLines);

   _recursiveDirectoryIterator->SetFileSubpathsToIgnore(cloudundancyIni.fileSubpathsToIgnore);
   _forEacher_CopyEachFileOrFolderToFolder->CallConstMemberFunctionWithEachElement(
      cloudundancyIni.destinationFolderPaths,
      &CloudundancyFileCopier::CopyFilteredFilesAndFoldersToDestinationFolder, this, cloudundancyIni);
}

// Private Functions

void CloudundancyFileCopier::CopyFilteredFilesAndFoldersToDestinationFolder(
   const fs::path& destinationFolderPath, const CloudundancyIni& cloudundancyIni) const
{
   const pair<fs::path, CloudundancyIni> destinationFolderPath_cloudundancyIni = make_pair(destinationFolderPath, cloudundancyIni);
   _tryCatchCaller->TryCatchCallConstMemberFunction(
      this, &CloudundancyFileCopier::DoCopyFilteredFilesAndFoldersToDestinationFolder,
      destinationFolderPath_cloudundancyIni,
      &CloudundancyFileCopier::ExceptionHandlerForDoCopyFilteredFilesAndFoldersToDestinationFolder);
}

void CloudundancyFileCopier::DoCopyFilteredFilesAndFoldersToDestinationFolder(
   const pair<fs::path, CloudundancyIni>& destinationFolderPath_cloudundancyIni) const
{
   const fs::path& destinationFolderPath = destinationFolderPath_cloudundancyIni.first;
   const CloudundancyIni& cloudundancyIni = destinationFolderPath_cloudundancyIni.second;

   const string copyingMessage = Utils::String::ConcatStrings(
      "\n[Cloudundancy] Copying [SourceFilesAndFolders] to destination folder ", destinationFolderPath.string(), ":\n");
   _console->WriteLineColor(copyingMessage, Color::Teal);
   _cloudundancyLogFileWriter->AppendTextToCloudundancyLogFileInFolder(destinationFolderPath, "Cloudundancy backup started");
   _stopwatch->Start();

   _forEacher_CopyFileOrFolderToFolder->CallConstMemberFunctionWithEachElement(
      cloudundancyIni.cloudundancyIniCopyInstructions,
      &CloudundancyFileCopier::CopyFileOrFolderToFolder, this, destinationFolderPath);

   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   const string folderBackupResultSuccessMessage = Utils::String::ConcatStrings(
      "[Cloudundancy]   FolderBackupResult: Successfully copied [SourceFilesAndFolders] to ", destinationFolderPath.string());
   _console->WriteLineColor(folderBackupResultSuccessMessage, Color::Green);

   const string folderBackupDurationMessage = Utils::String::ConcatStrings("[Cloudundancy] FolderBackupDuration: ", elapsedSeconds, " seconds");
   _console->WriteLine(folderBackupDurationMessage);

   const string cloudundancyBackupSuccessfulMessage = Utils::String::ConcatStrings("Cloudundancy backup successful in ", elapsedSeconds, " seconds");
   _cloudundancyLogFileWriter->AppendTextToCloudundancyLogFileInFolder(
      destinationFolderPath, cloudundancyBackupSuccessfulMessage);
}

void CloudundancyFileCopier::ExceptionHandlerForDoCopyFilteredFilesAndFoldersToDestinationFolder(
   const exception& ex, const pair<fs::path, CloudundancyIni>& destinationFolderPath_cloudundancyIni) const
{
   const fs::path& destinationFolderPath = destinationFolderPath_cloudundancyIni.first;
   const string exceptionClassNameAndMessage = _call_Type_GetExceptionClassNameAndMessage(&ex);
   const string errorMessage = Utils::String::ConcatStrings(
      "Exception thrown while copying files to destination folder ", destinationFolderPath.string(), ": ", exceptionClassNameAndMessage);
   _cloudundancyLogFileWriter->AppendTextToCloudundancyLogFileInFolder(destinationFolderPath, errorMessage);
   throw runtime_error(exceptionClassNameAndMessage);
}

void CloudundancyFileCopier::CopyFileOrFolderToFolder(
   const CloudundancyIniCopyInstruction& cloudundancyIniCopyInstruction,
   const fs::path& destinationFolderPath) const
{
   const char lastPathChar = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath.string().back();
   const bool sourcePathIsAFile = lastPathChar != '/' && lastPathChar != '\\';
   if (sourcePathIsAFile)
   {
      _caller_CopyFileToFileFunctions->CallConstMemberFunction(
         &CloudundancyFileCopier::CopyFileToFolder,
         this, cloudundancyIniCopyInstruction, destinationFolderPath);
   }
   else
   {
      _caller_CopyFileToFileFunctions->CallConstMemberFunction(
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
      destinationFilePath = destinationFolderPath / sourceFilePathRelativeToSourceFolderPath;
   }
   else
   {
      destinationFilePath =
         destinationFolderPath /
         cloudundancyIniCopyInstruction.relativeDestinationFolderPath /
         sourceFilePathRelativeToSourceFolderPath;
   }
   const Utils::FileCopyResult fileCopyResult = _caller_CopyFileToFile->CallConstMemberFunction(
      &CloudundancyFileCopier::CopyFileToFile, this, sourceFilePath, destinationFilePath);
   _caller_WriteCopiedMessageOrExitWithCode1IfCopyFailed->CallConstMemberFunction(
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
      _caller_CopyNestedFileToFolder->ConstCall(
         &CloudundancyFileCopier::CopyNestedFileToFolder,
         this, nonIgnoredSourceFilePath, cloudundancyIniCopyInstruction, destinationFolderPath);
   }
}

Utils::FileCopyResult CloudundancyFileCopier::CopyFileToFile(
   const fs::path& sourceFilePath, const fs::path& destinationFilePath) const
{
   const string copyingFileMessage = Utils::String::ConcatStrings(
      "Copying ", sourceFilePath.string(), "\n",
      "     to ", destinationFilePath.string(), ". ");
   _console->Write(copyingFileMessage);
   const bool sourceFileSizeIsGreaterThanOrEqualTo2GB = _cloudundancyFileSystem->FileSizeIsGreaterThanOrEqualTo2GB(sourceFilePath);
   if (sourceFileSizeIsGreaterThanOrEqualTo2GB)
   {
      Utils::FileCopyResult fileCopyResult = _fileSystem->CopyFileToFileLargerThan2GB(sourceFilePath, destinationFilePath);
      return fileCopyResult;
   }
   Utils::FileCopyResult fileCopyResult = _fileSystem->CopyFileToFile(sourceFilePath, destinationFilePath);
   return fileCopyResult;
}

void CloudundancyFileCopier::CopyFileToFolder(
   const CloudundancyIniCopyInstruction& cloudundancyIniCopyInstruction, const fs::path& destinationFolderPath) const
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
   const Utils::FileCopyResult fileCopyResult = _caller_CopyFileToFile->CallConstMemberFunction(
      &CloudundancyFileCopier::CopyFileToFile, this, sourceFilePath, destinationFilePath);
   _caller_WriteCopiedMessageOrExitWithCode1IfCopyFailed->CallConstMemberFunction(
      &CloudundancyFileCopier::WriteCopiedMessageOrExitWithCode1IfCopyFailed, this, fileCopyResult, destinationFolderPath);
}

void CloudundancyFileCopier::WriteCopiedMessageOrExitWithCode1IfCopyFailed(
   const Utils::FileCopyResult& fileCopyResult, const fs::path& destinationFolderPath) const
{
   const string durationInMilliseconds = to_string(fileCopyResult.durationInMilliseconds);
   if (fileCopyResult.copySucceeded)
   {
      const string copiedMessage = Utils::String::ConcatStrings("Copied [", durationInMilliseconds, "ms]\n");
      _console->WriteLineColor(copiedMessage, Color::Green);
   }
   else
   {
      const string copyFailedLogFileMessage = Utils::String::ConcatStrings("File copy failed: ",
         fileCopyResult.sourceFilePath.string(), " -> ", fileCopyResult.destinationFilePath.string(),
         ". Reason: ", fileCopyResult.copyFailureReason);
      _cloudundancyLogFileWriter->AppendTextToCloudundancyLogFileInFolder(destinationFolderPath, copyFailedLogFileMessage);

      const string copyFailedConsoleMessage = Utils::String::ConcatStrings(
         "Copy failed [", durationInMilliseconds, "ms]: ", fileCopyResult.copyFailureReason, "\n\n[Cloudundancy] ExitCode: 1");
      _console->WriteLineColor(copyFailedConsoleMessage, Color::Red);

      _call_quick_exit(1);
   }
}
