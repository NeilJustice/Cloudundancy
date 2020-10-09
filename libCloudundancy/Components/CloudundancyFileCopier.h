#pragma once
struct AbsoluteFileOrFolderPathToRelativeFolderPath;
class Console;
struct CloudundancyArgs;
struct CloudundancyIni;
class CloudundancyIniFileReader;
template<typename T, typename ClassType, typename ConstMemberFunctionType, typename ExtraArgType>
class OneExtraArgMemberForEacher;
class FileSystem;
class RecursiveDirectoryIterator;
class Stopwatch;
template<typename ClassType, typename Arg1Type, typename Arg2Type, typename Arg3Type>
class VoidThreeArgMemberFunctionCaller;
template<typename ClassType, typename Arg1Type, typename Arg2Type>
class VoidTwoArgMemberFunctionCaller;
class Watch;

class CloudundancyFileCopier
{
   friend class CloudundancyFileCopierTests;
private:
   // Constant Components
   unique_ptr<const CloudundancyIniFileReader> _cloudundancyIniFileReader;
   unique_ptr<const Console> _console;
   unique_ptr<const FileSystem> _fileSystem;

   // Function Callers
   function<string(const string&, const string&, const string&)> _call_String_ReplaceFirst;

   using OneExtraArgMemberForEacherOfCopyInstructionsType = const OneExtraArgMemberForEacher<
      fs::path, CloudundancyFileCopier,
      void(CloudundancyFileCopier::*)(const fs::path&, const CloudundancyIni&) const,
      const CloudundancyIni&>;
   unique_ptr<const OneExtraArgMemberForEacherOfCopyInstructionsType> _caller_CopyEachFileOrFolderToFolder;

   using OneExtraArgMemberForEacherOfDestinationFolderPathsType = const OneExtraArgMemberForEacher<
      AbsoluteFileOrFolderPathToRelativeFolderPath, CloudundancyFileCopier,
      void(CloudundancyFileCopier::*)(const AbsoluteFileOrFolderPathToRelativeFolderPath&, const fs::path&) const,
      const fs::path&>;
   unique_ptr<const OneExtraArgMemberForEacherOfDestinationFolderPathsType> _caller_CopyFileOrFolderToFolder;

   using VoidTwoArgMemberFunctionCallerType = const VoidTwoArgMemberFunctionCaller<
      CloudundancyFileCopier, const AbsoluteFileOrFolderPathToRelativeFolderPath&, const fs::path&>;
   unique_ptr<const VoidTwoArgMemberFunctionCallerType> _caller_CopyFileFunctions;

   using CallerType_CopyNestedFileToFolder = const VoidThreeArgMemberFunctionCaller<
      CloudundancyFileCopier, const fs::path&, const AbsoluteFileOrFolderPathToRelativeFolderPath&, const fs::path&>;
   unique_ptr<const CallerType_CopyNestedFileToFolder> _caller_CopyNestedFileToFolder;

   using VoidTryCopyFileCallerType = const VoidTwoArgMemberFunctionCaller<
      CloudundancyFileCopier, const fs::path&, const fs::path&>;
   unique_ptr<const VoidTryCopyFileCallerType> _caller_TryCopyFile;

   // Mutable Components
   unique_ptr<RecursiveDirectoryIterator> _recursiveDirectoryIterator;
   unique_ptr<Stopwatch> _stopwatch;
public:
   CloudundancyFileCopier() noexcept;
   virtual ~CloudundancyFileCopier();
   virtual void CopyFilesAndFoldersToMultipleFolders(const fs::path& cloudundancyIniFilePath) const;
   virtual void DeleteFolder(const fs::path& folderPath) const;
private:
   void CopyFilesAndFoldersToSingleFolder(
      const fs::path& destinationFolderPath, const CloudundancyIni& cloudundancyIni) const;

   void CopyFileOrFolderToFolder(
      const AbsoluteFileOrFolderPathToRelativeFolderPath& cloudundancyIniCopyInstruction, const fs::path& destinationFolderPath) const;

   void TryCopyFileToFolder(
      const AbsoluteFileOrFolderPathToRelativeFolderPath& cloudundancyIniCopyInstruction, const fs::path& destinationFolderPath) const;

   void CopyNestedFileToFolder(
      const fs::path& sourceFilePath,
      const AbsoluteFileOrFolderPathToRelativeFolderPath& cloudundancyIniCopyInstruction,
      const fs::path& destinationFolderPath) const;

   void CopyNonIgnoredFilesInAndBelowFolderToFolder(
      const AbsoluteFileOrFolderPathToRelativeFolderPath& cloudundancyIniCopyInstruction, const fs::path& destinationFolderPath) const;

   void TryCopyFile(const fs::path& sourceFilePath, const fs::path& destinationFilePath) const;
};
