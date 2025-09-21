#pragma once
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

      // Mutable Fields
      fs::recursive_directory_iterator _recursiveDirectoryIterator;
      vector<string> _fileSubpathsToIgnore;
   public:
      RecursiveDirectoryIterator() noexcept;
      virtual ~RecursiveDirectoryIterator();
      virtual void SetFileSubpathsToIgnore(const vector<string>& fileSubpathsToIgnore);
      virtual void InitializeIteratorAtFolderPath(const fs::path& folderPath);
      virtual fs::path NextNonIgnoredFilePath();
   private:
      static bool FilePathContainsAnySubstring(const fs::path& filePath, const vector<string>& filePathIgnoreSubstrings);
   };
}
