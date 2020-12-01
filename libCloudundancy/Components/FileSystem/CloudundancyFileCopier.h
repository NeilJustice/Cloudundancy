#pragma once
class Console;
class CloudundancyIniFileReader;
class CloudundancyLogFileAppender;
class FileSystem;
class RecursiveDirectoryIterator;
class Stopwatch;
class Watch;
struct CloudundancyArgs;
struct CloudundancyIni;
struct CloudundancyIniCopyInstruction;

template<typename ClassType, typename ElementType, typename ExtraArgType>
class OneExtraArgMemberFunctionForEacher;

template<typename ClassType, typename Arg1Type>
class VoidOneArgMemberFunctionCaller;

template<typename ClassType, typename Arg1Type, typename Arg2Type>
class VoidTwoArgMemberFunctionCaller;

template<typename ClassType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
class VoidThreeArgMemberFunctionCaller;

class CloudundancyFileCopier
{
   friend class CloudundancyFileCopierTests;
private:
   // Function Pointers
   function<void(int)> _call_exit;
   function<string(const string&, const string&, const string&)> _call_String_ReplaceFirst;

   // Function Callers
   using _caller_CopyFileFunctionsType = VoidTwoArgMemberFunctionCaller<
      CloudundancyFileCopier, const CloudundancyIniCopyInstruction&, const fs::path&>;
   unique_ptr<const _caller_CopyFileFunctionsType> _memberCaller_CopyFileFunctions;

   using _memberCaller_CopyNestedFileToFolderType = VoidThreeArgMemberFunctionCaller<
      CloudundancyFileCopier, const fs::path&, const CloudundancyIniCopyInstruction&, const fs::path&>;
   unique_ptr<const _memberCaller_CopyNestedFileToFolderType> _memberCaller_CopyNestedFileToFolder;

   using _memberCaller_TryCopyFileType = VoidTwoArgMemberFunctionCaller<
      CloudundancyFileCopier, const fs::path&, const fs::path&>;
   unique_ptr<const _memberCaller_TryCopyFileType> _memberCaller_TryCopyFile;

   using _memberForEacher_CopyEachFileOrFolderToFolderType = OneExtraArgMemberFunctionForEacher<
      CloudundancyFileCopier, fs::path, CloudundancyIni>;
   unique_ptr<const _memberForEacher_CopyEachFileOrFolderToFolderType> _memberForEacher_CopyEachFileOrFolderToFolder;

   using _memberForEacher_CopyFileOrFolderToFolderType = OneExtraArgMemberFunctionForEacher<
      CloudundancyFileCopier, CloudundancyIniCopyInstruction, fs::path>;
   unique_ptr<const _memberForEacher_CopyFileOrFolderToFolderType> _memberForEacher_CopyFileOrFolderToFolder;

   using _memberCaller_WriteCopiedOrCopyFailedMessageType = VoidOneArgMemberFunctionCaller<
      CloudundancyFileCopier, const FileCopyResult&>;
   unique_ptr<const _memberCaller_WriteCopiedOrCopyFailedMessageType> _memberCaller_WriteCopiedOrCopyFailedMessage;

   // Constant Components
   unique_ptr<const CloudundancyIniFileReader> _cloudundancyIniFileReader;
   unique_ptr<const CloudundancyLogFileAppender> _cloudundancyLogFileAppender;
   unique_ptr<const Console> _console;
   unique_ptr<const FileSystem> _fileSystem;

   // Mutable Components
   unique_ptr<RecursiveDirectoryIterator> _recursiveDirectoryIterator;
   unique_ptr<Stopwatch> _stopwatch;
public:
   CloudundancyFileCopier() noexcept;
   virtual ~CloudundancyFileCopier();
   virtual void CopyFilesAndFoldersToMultipleFolders(const fs::path& cloudundancyIniFilePath) const;
   virtual void DeleteFolder(const fs::path& folderPath) const;
private:
   void CopyFilesAndFoldersToSingleFolder(const fs::path& destinationFolderPath, const CloudundancyIni& cloudundancyIni) const;
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
   void TryCopyFile(const fs::path& sourceFilePath, const fs::path& destinationFilePath) const;
   void TryCopyFileToFolder(
      const CloudundancyIniCopyInstruction& cloudundancyIniCopyInstruction,
      const fs::path& destinationFolderPath) const;
   void WriteCopiedOrCopyFailedMessage(const FileCopyResult& fileCopyResult) const;
};
