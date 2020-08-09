#pragma once
struct AbsoluteFileOrFolderPathToRelativeFolderPath;

struct AbsoluteFilePathToRelativeFolderPath
{
   fs::path absoluteSourceFilePath;
   fs::path relativeDestinationFolderPath;

   static AbsoluteFilePathToRelativeFolderPath FromCloudundancyIniCopyInstruction(
      size_t elementIndex,
      const AbsoluteFileOrFolderPathToRelativeFolderPath& cloudundancyIniCopyInstruction,
      const vector<string>& fileSubpathsToNotCopy);
};
