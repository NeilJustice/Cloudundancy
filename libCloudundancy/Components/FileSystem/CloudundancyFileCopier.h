#pragma once
class CloudundancyFileSystem;
class CloudundancyIniFileReader;
class CloudundancyLogFileWriter;

class CloudundancyFileCopier
{
   friend class CloudundancyFileCopierTests;
private:
   // Function Pointers
   function<void(int)> _call_quick_exit;
   function<string(const string&, const string&, const string&)> _call_String_ReplaceFirst;
   function<string(const exception*)> _call_Type_GetExceptionClassNameAndMessage;

   // Function Callers
   using _caller_CopyFileToFileFunctionsType = Utils::VoidTwoArgMemberFunctionCaller<
      CloudundancyFileCopier, const CloudundancyIniCopyInstruction&, const fs::path&>;
   unique_ptr<const _caller_CopyFileToFileFunctionsType> _caller_CopyFileToFileFunctions;

   using _caller_CopyNestedFileToFolderType = Utils::VoidThreeArgMemberFunctionCaller<
      CloudundancyFileCopier, const fs::path&, const CloudundancyIniCopyInstruction&, const fs::path&>;
   unique_ptr<const _caller_CopyNestedFileToFolderType> _caller_CopyNestedFileToFolder;

   using _caller_CopyFileToFileType = Utils::NonVoidTwoArgMemberFunctionCaller<
      Utils::FileCopyResult, CloudundancyFileCopier, const fs::path&, const fs::path&>;
   unique_ptr<const _caller_CopyFileToFileType> _caller_CopyFileToFile;

   using _caller_WriteCopiedMessageOrExitWithCode1IfCopyFailedType = Utils::VoidTwoArgMemberFunctionCaller<
      CloudundancyFileCopier, const Utils::FileCopyResult&, const fs::path&>;
   unique_ptr<const _caller_WriteCopiedMessageOrExitWithCode1IfCopyFailedType> _caller_WriteCopiedMessageOrExitWithCode1IfCopyFailed;

   using _forEacher_CopyEachFileOrFolderToFolderType = Utils::TwoArgMemberFunctionForEacher<
      CloudundancyFileCopier, fs::path, const CloudundancyIni&>;
   unique_ptr<const _forEacher_CopyEachFileOrFolderToFolderType> _forEacher_CopyEachFileOrFolderToFolder;

   using _forEacher_CopyFileOrFolderToFolderType = Utils::TwoArgMemberFunctionForEacher<
      CloudundancyFileCopier, CloudundancyIniCopyInstruction, const fs::path&>;
   unique_ptr<const _forEacher_CopyFileOrFolderToFolderType> _forEacher_CopyFileOrFolderToFolder;

   // Constant Components
   unique_ptr<const CloudundancyFileSystem> _cloudundancyFileSystem;
   unique_ptr<const CloudundancyIniFileReader> _cloudundancyIniFileReader;
   unique_ptr<const CloudundancyLogFileWriter> _cloudundancyLogFileWriter;
   unique_ptr<const Utils::Console> _console;
   unique_ptr<const Utils::FileSystem> _fileSystem;
   unique_ptr<const Utils::TryCatchCaller<CloudundancyFileCopier, const pair<fs::path, CloudundancyIni>&>> _tryCatchCaller;

   // Mutable Components
   unique_ptr<Utils::RecursiveDirectoryIterator> _recursiveDirectoryIterator;
   unique_ptr<Utils::Stopwatch> _stopwatch;
public:
   CloudundancyFileCopier() noexcept;
   virtual ~CloudundancyFileCopier();
   virtual void CopyFilteredFilesAndFoldersToDestinationFolders(
      const fs::path& cloudundancyIniFilePath, bool deleteDestinationFoldersFirst) const;
private:
   void CopyFilteredFilesAndFoldersToDestinationFolder(
      const fs::path& destinationFolderPath, const CloudundancyIni& cloudundancyIni) const;

   void DoCopyFilteredFilesAndFoldersToDestinationFolder(
      const pair<fs::path, CloudundancyIni>& destinationFolderPath_cloudundancyIni) const;

   void ExceptionHandlerForDoCopyFilteredFilesAndFoldersToDestinationFolder(
      const exception& ex, const pair<fs::path, CloudundancyIni>& destinationFolderPath_cloudundancyIni) const;

   void CopyFileOrFolderToFolder(
      const CloudundancyIniCopyInstruction& cloudundancyIniCopyInstruction, const fs::path& destinationFolderPath) const;

   void CopyNestedFileToFolder(
      const fs::path& sourceFilePath,
      const CloudundancyIniCopyInstruction& cloudundancyIniCopyInstruction,
      const fs::path& destinationFolderPath) const;

   void CopyNonIgnoredFilesInAndBelowFolderToFolder(
      const CloudundancyIniCopyInstruction& cloudundancyIniCopyInstruction, const fs::path& destinationFolderPath) const;

   Utils::FileCopyResult CopyFileToFile(
      const fs::path& sourceFilePath, const fs::path& destinationFilePath) const;

   void CopyFileToFolder(
      const CloudundancyIniCopyInstruction& cloudundancyIniCopyInstruction, const fs::path& destinationFolderPath) const;

   void WriteCopiedMessageOrExitWithCode1IfCopyFailed(
      const Utils::FileCopyResult& fileCopyResult, const fs::path& destinationFolderPath) const;
};
