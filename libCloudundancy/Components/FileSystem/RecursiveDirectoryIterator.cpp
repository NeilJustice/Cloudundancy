#include "pch.h"
#include "libCloudundancy/Components/FileSystem/RecursiveDirectoryIterator.h"

namespace Utils
{
   RecursiveDirectoryIterator::RecursiveDirectoryIterator() noexcept
      // Function Pointers
      : _call_fs_remove(static_cast<FilesystemRemoveOverloadFunctionType>(fs::remove))
   {
   }

   RecursiveDirectoryIterator::~RecursiveDirectoryIterator()
   {
   }

   void RecursiveDirectoryIterator::SetFileSubpathsToIgnore(const vector<string>& fileSubpathsToIgnore)
   {
      _fileSubpathsToIgnore = fileSubpathsToIgnore;
   }

   void RecursiveDirectoryIterator::InitializeIteratorAtFolderPath(const fs::path& folderPath)
   {
      _recursiveDirectoryIterator = fs::recursive_directory_iterator(folderPath);
   }

   fs::path RecursiveDirectoryIterator::NextNonIgnoredFilePath()
   {
      static const fs::recursive_directory_iterator zeroFilesRemaining{};
      while (true)
      {
         if (_recursiveDirectoryIterator == zeroFilesRemaining)
         {
            return fs::path();
         }
         const fs::directory_entry& nextDirectoryEntry = *_recursiveDirectoryIterator++;
         const fs::file_status directoryEntryStatus = nextDirectoryEntry.status();
         const fs::file_type sourceFileOrFolderType = directoryEntryStatus.type();
         if (sourceFileOrFolderType != fs::file_type::regular)
         {
            continue;
         }
         const fs::path& nextFilePath = nextDirectoryEntry.path();
         const bool filePathIsIgnored = FilePathContainsAnySubstring(nextFilePath, _fileSubpathsToIgnore);
         if (filePathIsIgnored)
         {
            continue;
         }
         return nextFilePath;
      }
   }

   // Private Functions

   bool RecursiveDirectoryIterator::FilePathContainsAnySubstring(const fs::path& filePath, const vector<string>& filePathIgnoreSubstrings)
   {
      if (filePathIgnoreSubstrings.empty())
      {
         return false;
      }
      const string filePathAsString = filePath.string();
      const bool doIgnoreFilePath = std::any_of(
         filePathIgnoreSubstrings.cbegin(), filePathIgnoreSubstrings.cend(), [&](const string& ignoredFilePathSubstring)
         {
            if (Utils::String::Contains(filePathAsString, ignoredFilePathSubstring))
            {
               return true;
            }
            return false;
         });
      return doIgnoreFilePath;
   }
}
