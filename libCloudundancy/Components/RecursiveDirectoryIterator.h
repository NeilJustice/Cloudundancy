#pragma once
#include "libCloudundancy/ValueTypes/FileCopyInstruction.h"
#include "libCloudundancy/ValueTypes/AbsoluteFilePathToRelativeFolderPath.h"
#include "libCloudundancy/ValueTypes/AbsoluteFileOrFolderPathToRelativeFolderPath.h"
struct CloudundancyIni;
template<
   typename TransformedContainerType,
   typename SourceContainerType,
   typename TransformFunctionType,
   typename ExtraArgType>
class OneExtraArgTransformer;

class RecursiveDirectoryIterator
{
   friend class RecursiveDirectoryIteratorIntegrationTests;
private:
   // Function Callers
   using OneExtraArgTransformerType = OneExtraArgTransformer<
      vector<AbsoluteFilePathToRelativeFolderPath>,
      vector<AbsoluteFileOrFolderPathToRelativeFolderPath>,
      AbsoluteFilePathToRelativeFolderPath(*)(size_t, const AbsoluteFileOrFolderPathToRelativeFolderPath&, const vector<string>&),
      const vector<string>&>;
   unique_ptr<const OneExtraArgTransformerType> _oneExtraArgTransformer;

   // Mutable Fields
   fs::recursive_directory_iterator _recursiveDirectoryIterator;
   vector<string> _fileSubpathsToNotCopy;
public:
   RecursiveDirectoryIterator() noexcept;
   virtual ~RecursiveDirectoryIterator();
   virtual void SetFileSubpathsToNotCopy(const vector<string>& fileSubpathsToNotCopy);
   virtual void InitializeIteratorAtFolderPath(const fs::path& folderPath);
   virtual fs::path NextNonIgnoredFilePath();
private:
   static bool FilePathCaseInsensitiveContainsAnySubstring(
      const fs::path& filePath, const vector<string>& substrings);
};
