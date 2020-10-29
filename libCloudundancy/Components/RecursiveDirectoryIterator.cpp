#include "pch.h"
#include "libCloudundancy/Components/Iteration/Transform/OneExtraArgTransformer.h"
#include "libCloudundancy/Components/RecursiveDirectoryIterator.h"

RecursiveDirectoryIterator::RecursiveDirectoryIterator() noexcept
   : _oneExtraArgTransformer(make_unique<OneExtraArgTransformerType>())
{
}

RecursiveDirectoryIterator::~RecursiveDirectoryIterator()
{
}

void RecursiveDirectoryIterator::SetFileSubpathsToNotCopy(const vector<string>& fileSubpathsToNotCopy)
{
   _fileSubpathsToNotCopy = fileSubpathsToNotCopy;
}

void RecursiveDirectoryIterator::InitializeIteratorAtFolderPath(const fs::path& folderPath)
{
   _recursiveDirectoryIterator = fs::recursive_directory_iterator(folderPath);
}

fs::path RecursiveDirectoryIterator::NextNonIgnoredFilePath()
{
   static const fs::recursive_directory_iterator zeroMoreFilesRemaining;
   while (true)
   {
      if (_recursiveDirectoryIterator == zeroMoreFilesRemaining)
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

// Private Functions

bool RecursiveDirectoryIterator::FilePathCaseInsensitiveContainsAnySubstring(
   const fs::path& filePath, const vector<string>& substrings)
{
   if (substrings.empty())
   {
      return false;
   }
   const string filePathAsString = filePath.string();
   const bool doIgnoreFilePath = std::any_of(
      cbegin(substrings), cend(substrings), [&](const string& ignoredSubstring)
      {
         if (String::CaseInsensitiveContains(filePathAsString, ignoredSubstring))
         {
            return true;
         }
         return false;
      });
   return doIgnoreFilePath;
}
