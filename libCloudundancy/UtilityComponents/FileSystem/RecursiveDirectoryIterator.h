#pragma once
struct CloudundancyIni;
namespace Utils
{
   template<
      typename TransformedContainerType,
      typename SourceContainerType,
      typename TransformFunctionType,
      typename ExtraArgType>
   class OneExtraArgTransformer;
}
class RecursiveDirectoryIteratorTests;
class RecursiveDirectoryIteratorIntegrationTests;

namespace Utils
{
   class RecursiveDirectoryIterator
   {
      friend class ::RecursiveDirectoryIteratorTests;
      friend class ::RecursiveDirectoryIteratorIntegrationTests;
   private:
      // Function Pointers
      using FilesystemRemoveOverloadFunctionType = bool(*)(const fs::path&);
      function<bool(const fs::path&)> _call_fs_remove;
      // Function Callers
      using OneExtraArgTransformerType = OneExtraArgTransformer<
         vector<AbsoluteFilePathToRelativeDestinationFolderPath>,
         vector<CloudundancyIniCopyInstruction>,
         AbsoluteFilePathToRelativeDestinationFolderPath(*)(size_t, const CloudundancyIniCopyInstruction&, const vector<string>&),
         const vector<string>&>;
      unique_ptr<const OneExtraArgTransformerType> _oneExtraArgTransformer;

      // Mutable Fields
      fs::recursive_directory_iterator _recursiveDirectoryIterator;
      vector<string> _fileSubpathsToIgnore;
   public:
      RecursiveDirectoryIterator() noexcept;
      virtual ~RecursiveDirectoryIterator();
      virtual void SetFileSubpathsToIgnore(const vector<string>& fileSubpathsToIgnore);
      virtual void InitializeIteratorAtFolderPath(const fs::path& folderPath);
      virtual fs::path NextNonIgnoredFilePath();
      virtual void RecursivelyDeleteAllFilesExceptIgnoredFileSubpaths();
   private:
      static bool FilePathCaseInsensitiveContainsAnySubstring(const fs::path& filePath, const vector<string>& filePathIgnoreSubstrings);
   };
}
