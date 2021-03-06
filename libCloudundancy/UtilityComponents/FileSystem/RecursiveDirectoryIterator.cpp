#include "pch.h"
#include "libCloudundancy/UtilityComponents/FileSystem/RecursiveDirectoryIterator.h"

RecursiveDirectoryIterator::RecursiveDirectoryIterator() noexcept
   // Function Pointers
   : _call_fs_remove(static_cast<FilesystemRemoveOverloadFunctionType>(fs::remove))
   // Function Callers
   , _oneExtraArgTransformer(make_unique<OneExtraArgTransformerType>())
{
}

RecursiveDirectoryIterator::~RecursiveDirectoryIterator()
{
}

void RecursiveDirectoryIterator::SetFileSubpathsToIgnore(const vector<string>& fileSubpathsToNotCopy)
{
   _fileSubpathsToNotCopy = fileSubpathsToNotCopy;
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
      const bool filePathIsIgnored = FilePathCaseInsensitiveContainsAnySubstring(nextFilePath, _fileSubpathsToNotCopy);
      if (filePathIsIgnored)
      {
         continue;
      }
      return nextFilePath;
   }
}

void RecursiveDirectoryIterator::RecursivelyDeleteAllFilesExceptIgnoredFileSubpaths()
{
   while (true)
   {
      const fs::path nextNonIgnoredFilePath = NextNonIgnoredFilePath();
      if (nextNonIgnoredFilePath == fs::path())
      {
         break;
      }
      _call_fs_remove(nextNonIgnoredFilePath);
   }
}

// Private Functions

bool RecursiveDirectoryIterator::FilePathCaseInsensitiveContainsAnySubstring(const fs::path& filePath, const vector<string>& filePathIgnoreSubstrings)
{
   if (filePathIgnoreSubstrings.empty())
   {
      return false;
   }
   const string filePathAsString = filePath.string();
   const bool doIgnoreFilePath = std::any_of(
      filePathIgnoreSubstrings.cbegin(), filePathIgnoreSubstrings.cend(), [&](const string& ignoredFilePathSubstring)
      {
         if (String::CaseInsensitiveContains(filePathAsString, ignoredFilePathSubstring))
         {
            return true;
         }
         return false;
      });
   return doIgnoreFilePath;
}
