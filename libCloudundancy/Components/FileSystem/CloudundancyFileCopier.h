#pragma once
class CloudundancyIniFileReader;
class CloudundancyLogFileWriter;
class FileSystem;

class CloudundancyFileCopier
{
   friend class CloudundancyFileCopierTests;
private:
   // Function Pointers
   function<void(int)> _call_exit;
   function<string(const string&, const string&, const string&)> _call_String_ReplaceFirst;
   function<string(const exception*)> _call_Type_GetExceptionClassNameAndMessage;

   // Function Callers
   using _caller_CopyFileFunctionsType = VoidTwoArgMemberFunctionCaller<
      CloudundancyFileCopier, const CloudundancyIniCopyInstruction&, const fs::path&>;
   unique_ptr<const _caller_CopyFileFunctionsType> _memberCaller_CopyFileFunctions;

   using _memberCaller_CopyNestedFileToFolderType = VoidThreeArgMemberFunctionCaller<
      CloudundancyFileCopier, const fs::path&, const CloudundancyIniCopyInstruction&, const fs::path&>;
   unique_ptr<const _memberCaller_CopyNestedFileToFolderType> _memberCaller_CopyNestedFileToFolder;

   using _memberCaller_TryCopyFileType = NonVoidTwoArgMemberFunctionCaller<
      FileCopyResult, CloudundancyFileCopier, const fs::path&, const fs::path&>;
   unique_ptr<const _memberCaller_TryCopyFileType> _memberCaller_TryCopyFile;

   using _memberForEacher_CopyEachFileOrFolderToFolderType = OneExtraArgMemberFunctionForEacher<
      CloudundancyFileCopier, fs::path, const CloudundancyIni&>;
   unique_ptr<const _memberForEacher_CopyEachFileOrFolderToFolderType> _memberForEacher_CopyEachFileOrFolderToFolder;

   using _memberForEacher_CopyFileOrFolderToFolderType = OneExtraArgMemberFunctionForEacher<
      CloudundancyFileCopier, CloudundancyIniCopyInstruction, const fs::path&>;
   unique_ptr<const _memberForEacher_CopyFileOrFolderToFolderType> _memberForEacher_CopyFileOrFolderToFolder;

   using _memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedType = VoidTwoArgMemberFunctionCaller<
      CloudundancyFileCopier, const FileCopyResult&, const fs::path&>;
   unique_ptr<const _memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailedType> _memberCaller_WriteCopiedMessageOrExitWithCode1IfCopyFailed;

   // Constant Components
   unique_ptr<const CloudundancyIniFileReader> _cloudundancyIniFileReader;
   unique_ptr<const CloudundancyLogFileWriter> _cloudundancyLogFileWriter;
   unique_ptr<const Console> _console;
   unique_ptr<const FileSystem> _fileSystem;
   unique_ptr<const TryCatchCaller<CloudundancyFileCopier, const pair<fs::path, CloudundancyIni>&>> _tryCatchCaller;

   // Mutable Components
   unique_ptr<RecursiveDirectoryIterator> _recursiveDirectoryIterator;
   unique_ptr<Stopwatch> _stopwatch;
public:
   CloudundancyFileCopier() noexcept;
   virtual ~CloudundancyFileCopier();
   virtual void CopyFilesAndFoldersToMultipleDestinationFolders(
      const fs::path& cloudundancyIniFilePath, bool deleteDestinationFoldersFirst) const;
private:
   void CopyFilesAndFoldersToDestinationFolder(
      const fs::path& destinationFolderPath, const CloudundancyIni& cloudundancyIni) const;
   void DoCopyFilesAndFoldersToDestinationFolder(
      const pair<fs::path, CloudundancyIni>& destinationFolderPath_cloudundancyIni) const;
   void ExceptionHandlerForDoCopyFilesAndFoldersToDestinationFolder(
      const exception& ex, const pair<fs::path, CloudundancyIni>& destinationFolderPath_cloudundancyIni) const;

   void CopyFileOrFolderToFolder(
      const CloudundancyIniCopyInstruction& cloudundancyIniCopyInstruction,
      const fs::path& destinationFolderPath) const;
   void CopyNestedFileToFolder(
      const fs::path& sourceFilePath,
      const CloudundancyIniCopyInstruction& cloudundancyIniCopyInstruction,
      const fs::path& destinationFolderPath) const;
   void CopyNonIgnoredFilesInAndBelowFolderToFolder(
      const CloudundancyIniCopyInstruction& cloudundancyIniCopyInstruction,
      const fs::path& destinationFolderPath) const;
   void TryCopyFileToFolder(
      const CloudundancyIniCopyInstruction& cloudundancyIniCopyInstruction,
      const fs::path& destinationFolderPath) const;
   FileCopyResult TryCopyFile(const fs::path& sourceFilePath, const fs::path& destinationFilePath) const;
   void WriteCopiedMessageOrExitWithCode1IfCopyFailed(
      const FileCopyResult& fileCopyResult, const fs::path& destinationFolderPath) const;
};
