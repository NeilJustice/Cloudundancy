#pragma once
struct AbsoluteFileOrFolderPathToRelativeFolderPath;
class Console;
struct CloudundancyArgs;
struct CloudundancyIni;
class CloudundancyIniFileReader;
template<typename T, typename ClassType, typename ConstMemberFunctionType, typename ExtraArgType>
class OneExtraArgMemberFunctionForEacher;
class FileSystem;
class RecursiveDirectoryIterator;
class Stopwatch;
template<typename ClassType, typename Arg1Type>
class VoidOneArgMemberFunctionCaller;
template<typename ClassType, typename Arg1Type, typename Arg2Type>
class VoidTwoArgMemberFunctionCaller;
template<typename ClassType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
class VoidThreeArgMemberFunctionCaller;
class Watch;

class CloudundancyFileCopier
{
   friend class CloudundancyFileCopierTests;
private:
   // Function Callers
   function<string(const string&, const string&, const string&)> _call_String_ReplaceFirst;

   using OneExtraArgMemberFunctionForEacherOfCopyInstructionsType = OneExtraArgMemberFunctionForEacher<
      fs::path,
      void(CloudundancyFileCopier::*)(const fs::path&, const CloudundancyIni&) const,
      CloudundancyFileCopier, const CloudundancyIni&>;
   unique_ptr<const OneExtraArgMemberFunctionForEacherOfCopyInstructionsType> _caller_CopyEachFileOrFolderToFolder;

   using VoidTwoArgMemberFunctionCallerType = VoidTwoArgMemberFunctionCaller<
      CloudundancyFileCopier, const AbsoluteFileOrFolderPathToRelativeFolderPath&, const fs::path&>;
   unique_ptr<const VoidTwoArgMemberFunctionCallerType> _caller_CopyFileFunctions;

   using OneExtraArgMemberFunctionForEacherOfDestinationFolderPathsType = OneExtraArgMemberFunctionForEacher<
      AbsoluteFileOrFolderPathToRelativeFolderPath,
      void(CloudundancyFileCopier::*)(const AbsoluteFileOrFolderPathToRelativeFolderPath&, const fs::path&) const,
      CloudundancyFileCopier,
      const fs::path&>;
   unique_ptr<const OneExtraArgMemberFunctionForEacherOfDestinationFolderPathsType> _caller_CopyFileOrFolderToFolder;

   using CallerType_CopyNestedFileToFolder = VoidThreeArgMemberFunctionCaller<
      CloudundancyFileCopier, const fs::path&, const AbsoluteFileOrFolderPathToRelativeFolderPath&, const fs::path&>;
   unique_ptr<const CallerType_CopyNestedFileToFolder> _caller_CopyNestedFileToFolder;

   using VoidTryCopyFileCallerType = VoidTwoArgMemberFunctionCaller<
      CloudundancyFileCopier, const fs::path&, const fs::path&>;
   unique_ptr<const VoidTryCopyFileCallerType> _caller_TryCopyFile;

   using _caller_WriteCopiedOrCopyFailedMessageType = VoidOneArgMemberFunctionCaller<
      CloudundancyFileCopier, const FileCopyResult&>;
   unique_ptr<const _caller_WriteCopiedOrCopyFailedMessageType> _caller_WriteCopiedOrCopyFailedMessage;

   // Constant Components
   unique_ptr<const CloudundancyIniFileReader> _cloudundancyIniFileReader;
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
      const AbsoluteFileOrFolderPathToRelativeFolderPath& cloudundancyIniCopyInstruction,
      const fs::path& destinationFolderPath) const;
   void CopyNestedFileToFolder(
      const fs::path& sourceFilePath,
      const AbsoluteFileOrFolderPathToRelativeFolderPath& cloudundancyIniCopyInstruction,
      const fs::path& destinationFolderPath) const;
   void CopyNonIgnoredFilesInAndBelowFolderToFolder(
      const AbsoluteFileOrFolderPathToRelativeFolderPath& cloudundancyIniCopyInstruction,
      const fs::path& destinationFolderPath) const;
   void TryCopyFile(const fs::path& sourceFilePath, const fs::path& destinationFilePath) const;
   void TryCopyFileToFolder(
      const AbsoluteFileOrFolderPathToRelativeFolderPath& cloudundancyIniCopyInstruction,
      const fs::path& destinationFolderPath) const;
   void WriteCopiedOrCopyFailedMessage(const FileCopyResult& fileCopyResult) const;
};
