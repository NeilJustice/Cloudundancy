#include "pch.h"
#include "libCloudundancy/Components/Console/Console.h"
#include "libCloudundancy/Components/CloudundancyIniFileReader.h"
#include "libCloudundancy/Components/CloudundancyFileCopier.h"
#include "libCloudundancy/Components/FileSystem/FileSystem.h"
#include "libCloudundancy/Components/Function/Member/VoidThreeArgMemberFunctionCaller.h"
#include "libCloudundancy/Components/Function/Member/VoidTwoArgMemberFunctionCaller.h"
#include "libCloudundancy/Components/Iteration/ForEach/OneExtraArgMemberForEacher.h"
#include "libCloudundancy/Components/RecursiveDirectoryIterator.h"
#include "libCloudundancy/Components/Strings/StringUtil.h"
#include "libCloudundancy/Components/Time/Stopwatch.h"

CloudundancyFileCopier::CloudundancyFileCopier() noexcept
   // Constant Components
   : _cloudundancyIniFileReader(make_unique<CloudundancyIniFileReader>())
   , _console(make_unique<Console>())
   , _fileSystem(make_unique<FileSystem>())
   // Function Callers
   , _call_String_ReplaceFirst(String::ReplaceFirst)
   , _caller_CopyEachFileOrFolderToFolder(make_unique<OneExtraArgMemberForEacherOfCopyInstructionsType>())
   , _caller_CopyFileOrFolderToFolder(make_unique<OneExtraArgMemberForEacherOfDestinationFolderPathsType>())
   , _caller_CopyFileFunctions(make_unique<VoidTwoArgMemberFunctionCallerType>())
   , _caller_CopyNestedFileToFolder(make_unique<CallerType_CopyNestedFileToFolder>())
   , _caller_TryCopyFile(make_unique<VoidTryCopyFileCallerType>())
   // Mutable Components
   , _recursiveDirectoryIterator(make_unique<RecursiveDirectoryIterator>())
   , _stopwatch(make_unique<Stopwatch>())
{
}

CloudundancyFileCopier::~CloudundancyFileCopier()
{
}

void CloudundancyFileCopier::CopyFilesAndFoldersToMultipleFolders(const fs::path& cloudundancyIniFilePath) const
{
   const CloudundancyIni cloudundancyIni = _cloudundancyIniFileReader->ReadIniFile(cloudundancyIniFilePath);
   _recursiveDirectoryIterator->SetFileSubpathsToNotCopy(cloudundancyIni.fileSubpathsToNotCopy);
   _caller_CopyEachFileOrFolderToFolder->OneExtraArgMemberForEach(
      cloudundancyIni.destinationFolderPaths, this, &CloudundancyFileCopier::CopyFilesAndFoldersToSingleFolder, cloudundancyIni);
}

void CloudundancyFileCopier::DeleteFolder(const fs::path& folderPath) const
{
   _fileSystem->DeleteFolder(folderPath);
}

// Private Functions

void CloudundancyFileCopier::CopyFilesAndFoldersToSingleFolder(
   const fs::path& destinationFolderPath, const CloudundancyIni& cloudundancyIni) const
{
   _stopwatch->Start();
   _caller_CopyFileOrFolderToFolder->OneExtraArgMemberForEach(
      cloudundancyIni.absoluteFileOrFolderPathAndRelativeFolderPaths,
      this, &CloudundancyFileCopier::CopyFileOrFolderToFolder, destinationFolderPath);
   const string elapsedSeconds = _stopwatch->StopAndGetElapsedSeconds();
   const string folderBackedUpMessage =
      "[Cloudundancy]  FolderBackupResult: All files copied to " + destinationFolderPath.string() + "\n" +
      "[Cloudundancy]   FolderElapsedTime: " + elapsedSeconds + " seconds\n";
   _console->WriteLine(folderBackedUpMessage);
}

void CloudundancyFileCopier::CopyFileOrFolderToFolder(
   const AbsoluteFileOrFolderPathToRelativeFolderPath& cloudundancyIniCopyInstruction,
   const fs::path& destinationFolderPath) const
{
   const char lastPathChar = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath.string().back();
   const bool sourcePathIsAFile = lastPathChar != '/' && lastPathChar != '\\';
   if (sourcePathIsAFile)
   {
      _caller_CopyFileFunctions->ConstCall(
         this, &CloudundancyFileCopier::TryCopyFileToFolder, cloudundancyIniCopyInstruction, destinationFolderPath);
   }
   else
   {
      _caller_CopyFileFunctions->ConstCall(
         this, &CloudundancyFileCopier::CopyNonIgnoredFilesInAndBelowFolderToFolder, cloudundancyIniCopyInstruction, destinationFolderPath);
   }
}

void CloudundancyFileCopier::TryCopyFileToFolder(
   const AbsoluteFileOrFolderPathToRelativeFolderPath& cloudundancyIniCopyInstruction,
   const fs::path& destinationFolderPath) const
{
   const fs::path& sourceFilePath = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath;
   const fs::path destinationFilePath = [&]()
   {
      const fs::path sourceFileName = cloudundancyIniCopyInstruction.absoluteSourceFileOrFolderPath.filename();
      if (cloudundancyIniCopyInstruction.relativeDestinationFolderPath == ".")
      {
         const fs::path destinationFilePath = destinationFolderPath / sourceFileName;
         return destinationFilePath;
      }
      const fs::path destinationFilePath =
         destinationFolderPath / cloudundancyIniCopyInstruction.relativeDestinationFolderPath / sourceFileName;
      return destinationFilePath;
   }();
   _caller_TryCopyFile->ConstCall(this, &CloudundancyFileCopier::TryCopyFile, sourceFilePath, destinationFilePath);
}

void CloudundancyFileCopier::CopyNestedFileToFolder(
   const fs::path& sourceFilePath,
   const AbsoluteFileOrFolderPathToRelativeFolderPath& cloudundancyIniCopyInstruction,
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
   _caller_TryCopyFile->ConstCall(this, &CloudundancyFileCopier::TryCopyFile, sourceFilePath, destinationFilePath);
}

void CloudundancyFileCopier::CopyNonIgnoredFilesInAndBelowFolderToFolder(
   const AbsoluteFileOrFolderPathToRelativeFolderPath& cloudundancyIniCopyInstruction,
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
         this, &CloudundancyFileCopier::CopyNestedFileToFolder,
         nonIgnoredSourceFilePath, cloudundancyIniCopyInstruction, destinationFolderPath);
   }
}

void CloudundancyFileCopier::TryCopyFile(const fs::path& sourceFilePath, const fs::path& destinationFilePath) const
{
   const string copyingFileMessage = String::Concat(
      "Copying ", sourceFilePath.string(), "\n     to ", destinationFilePath.string(), ". ");
   _console->Write(copyingFileMessage);
   const FileCopyResult fileCopyResult = _fileSystem->TryCopyFile(sourceFilePath, destinationFilePath);
   const string durationInMilliseconds = to_string(fileCopyResult.durationInMilliseconds);
   if (fileCopyResult.copySucceeded)
   {
      _console->WriteLineColor("Copied [" + durationInMilliseconds + "ms]\n", Color::Green);
   }
   else
   {
      _console->WriteLineColor("Copy failed [" + durationInMilliseconds + "ms]\n", Color::Red);
   }
}
